#include <iostream>
#include <fstream>
#include <array>
#include <set>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>

#define INF_VALUE 1000000;

using namespace std;
const int SIZE = 8;

struct Point{
    int x, y;
	Point() : Point(0, 0) {}
	Point(int x, int y) : x(x), y(y) {}
	bool operator==(const Point& rhs) const {
		return x == rhs.x && y == rhs.y;
	}
	bool operator!=(const Point& rhs) const {
		return !operator==(rhs);
	}
	Point operator+(const Point& rhs) const {
		return Point(x + rhs.x, y + rhs.y);
	}
	Point operator-(const Point& rhs) const {
		return Point(x - rhs.x, y - rhs.y);
	}
};

class OthelloBoard
{
private:
    enum SPOT_STATE {
        EMPTY = 0,
        BLACK = 1,
        WHITE = 2
    };
    int cur_player;
    int player;
    // now board
    array<array<int, SIZE>, SIZE> board;
    // next_valid_spots
    vector<Point> next_valid_spots;
    // directions
    const std::array<Point, 8> directions{{
        Point(-1, -1), Point(-1, 0), Point(-1, 1),
        Point(0, -1), /*{0, 0}, */Point(0, 1),
        Point(1, -1), Point(1, 0), Point(1, 1)
    }};
    // state value
    int state_value[8][8] = {
        100,-50, 5, 3, 3, 5,-50, 100,
        -50,-50, 5, 1, 1, 5,-50, -50,
         5, 5, 5, 1, 1, 5, 5,  5,
         3, 0, 1, 3, 3, 1, 0,  3,
         3, 0, 1, 3, 3, 1, 0,  3,
         5, 5, 5, 1, 1, 5, 5,  5,
        -50,-50, 5, 1, 1, 5,-50, -50,
        100,-50, 5, 3, 3, 5,-50, 100,
    };
    // count dics
    array<int, 3> disc_count;
public:
    OthelloBoard() {}
    void read_board(std::ifstream &fin){
        fin >> player;
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE; j++){
                fin >> board[i][j];
            }
        }
    }
    void read_valid_spots(std::ifstream &fin){
        int n_valid_spots;
        fin >> n_valid_spots;
        int x, y;
        for (int i = 0; i < n_valid_spots; i++){
            fin >> x >> y;
            next_valid_spots.push_back({x, y});
        }
    }
    /*---------------OthelloBoard action-----------------------*/
    int get_disc(Point p, array<array<int, SIZE>, SIZE> tmp_board) const {
        return tmp_board[p.x][p.y];
    }
    void set_disc(Point p, int disc, array<array<int, SIZE>, SIZE> tmp_board) {
        tmp_board[p.x][p.y] = disc;
    }
    int get_next_player(int player) const {
        return 3 - player;
    }
    bool is_spot_on_board(Point p) const {
        return 0 <= p.x && p.x < SIZE && 0 <= p.y && p.y < SIZE;
    }
    bool is_disc_at(Point p, int disc, array<array<int, SIZE>, SIZE> tmp_board) const {
        if (!is_spot_on_board(p))
            return false;
        if (get_disc(p, tmp_board) != disc)
            return false;
        return true;
    }
    // 判斷這步棋能不能下
    bool is_spot_valid(Point center, array<array<int, SIZE>, SIZE> tmp_board) const {
        if (get_disc(center, tmp_board) != EMPTY)
            return false;
        for (Point dir: directions) {
            // Move along the direction while testing.
            Point p = center + dir;
            if (!is_disc_at(p, get_next_player(cur_player), tmp_board))
                continue;
            p = p + dir;
            while (is_spot_on_board(p) && get_disc(p, tmp_board) != EMPTY) {
                if (is_disc_at(p, cur_player, tmp_board))
                    return true;
                p = p + dir;
            }
        }
        return false;
    }
    // 下這步棋後對手可下的地方
    vector<Point> get_valid_spots(array<array<int, SIZE>, SIZE> tmp_board) const {
        std::vector<Point> valid_spots;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                Point p = Point(i, j);
                if (tmp_board[i][j] != EMPTY)
                    continue;
                if (is_spot_valid(p, tmp_board))
                    valid_spots.push_back(p);
            }
        }
        return valid_spots;
    }
    // 翻棋子
    array<array<int, SIZE>, SIZE> flip_discs(Point center, array<array<int, SIZE>, SIZE> tmp_board) {
        for (Point dir: directions) {
            // Move along the direction while testing.
            Point p = center + dir;
            if (!is_disc_at(p, get_next_player(cur_player), tmp_board))
                continue;
            vector<Point> discs({p});
            p = p + dir;
            while (is_spot_on_board(p) && get_disc(p, tmp_board) != EMPTY) {
                if (is_disc_at(p, cur_player, tmp_board)) {
                    for (Point s: discs) {
                        set_disc(s, cur_player, tmp_board);
                    }
                    disc_count[cur_player] += discs.size();
                    disc_count[get_next_player(cur_player)] -= discs.size();
                    break;
                }
                discs.push_back(p);
                p = p + dir;
            }
        }
        return tmp_board;
    }
    /*--------------------------AI-----------------------------*/
    // state value
    int evaluation(Point point){
        int spot_value = 0;
        // 落點位置分數
        spot_value += state_value[point.y][point.x];
        return spot_value;
    }
    // 下這步棋後對手能下哪裡
    vector<Point> get_valid_points(Point point, array<array<int, SIZE>, SIZE> tmp_board) {
        array<array<int, SIZE>, SIZE> new_board = flip_discs(point, tmp_board);
        return get_valid_spots(new_board);
    }
    // minimax recursion (point, depth, player is who true = player, false = opponent)
    int minimax(Point point, int depth, bool player_type, array<array<int, SIZE>, SIZE> tmp_board){
        if(depth == 0){
            return evaluation(point);
        }
        int best_value;
        if(player_type){
            best_value = -INF_VALUE;
            vector<Point> next_points = get_valid_points(point, tmp_board);
            for(auto np:next_points){
                best_value = max(best_value, minimax(np, depth - 1, false, tmp_board));
            }
            return best_value;
        } else {
            best_value = INF_VALUE;
            vector<Point> next_points = get_valid_points(point, tmp_board);
            for(auto np:next_points){
                best_value = min(best_value, minimax(np, depth - 1, true, tmp_board));
            }
            return best_value;
        }
    }
    void write_valid_spot(std::ofstream &fout){
        int n_valid_spots = next_valid_spots.size();
        int n_valid_spots_value[50] = {0};
        int max_value = -INF_VALUE;
        int choice_idx = 0;
        for(int i = 0; i < n_valid_spots; i++){
            n_valid_spots_value[i] = minimax(next_valid_spots[i], 3, true, board);
            if(max_value < n_valid_spots_value[i]){
                max_value = n_valid_spots_value[i];
                choice_idx = i;
            }
        }
        Point p = next_valid_spots[choice_idx];
        fout << p.x << " " << p.y << std::endl;
        fout.flush();
    }
};


int main(int, char **argv)
{
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);
    OthelloBoard play;
    play.read_board(fin);
    play.read_valid_spots(fin);
    play.write_valid_spot(fout);
    fin.close();
    fout.close();
    return 0;
}
