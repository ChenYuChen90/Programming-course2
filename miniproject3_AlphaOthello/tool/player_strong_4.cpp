#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <map>
#include <sstream>
#include <cassert>
#define max(a, b) (a>b ?a: b)
#define min(a,b) (a<b ?a : b)

struct Point
{
    int x, y;
    Point() : Point(0, 0) {}
    Point(int x, int y) : x(x), y(y) {}
    bool operator==(const Point &rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }
    bool operator!=(const Point &rhs) const
    {
        return !operator==(rhs);
    }
    Point operator+(const Point &rhs) const
    {
        return Point(x + rhs.x, y + rhs.y);
    }
    Point operator-(const Point &rhs) const
    {
        return Point(x - rhs.x, y - rhs.y);
    }
};

class OthelloBoard
{
public:
    enum SPOT_STATE
    {
        EMPTY = 0,
        BLACK = 1,
        WHITE = 2
    };
    static const int SIZE = 8;
    const std::array<Point, 8> directions{{Point(-1, -1), Point(-1, 0), Point(-1, 1),
                                           Point(0, -1), /*{0, 0}, */ Point(0, 1),
                                           Point(1, -1), Point(1, 0), Point(1, 1)}};
    std::array<std::array<int, SIZE>, SIZE> board;
    std::vector<Point> next_valid_spots;
    std::array<int, 3> disc_count;
    int cur_player;
    bool done;
    int winner;

private:
    int get_next_player(int player) const
    {
        return 3 - player;
    }
    bool is_spot_on_board(Point p) const
    {
        return 0 <= p.x && p.x < SIZE && 0 <= p.y && p.y < SIZE;
    }
    int get_disc(Point p) const
    {
        return board[p.x][p.y];
    }
    void set_disc(Point p, int disc)
    {
        board[p.x][p.y] = disc;
    }
    bool is_disc_at(Point p, int disc) const
    {
        if (!is_spot_on_board(p))
            return false;
        if (get_disc(p) != disc)
            return false;
        return true;
    }
    bool is_spot_valid(Point center) const
    {
        if (get_disc(center) != EMPTY)
            return false;
        for (Point dir : directions)
        {
            // Move along the direction while testing.
            Point p = center + dir;
            if (!is_disc_at(p, get_next_player(cur_player)))
                continue;
            p = p + dir;
            while (is_spot_on_board(p) && get_disc(p) != EMPTY)
            {
                if (is_disc_at(p, cur_player))
                    return true;
                p = p + dir;
            }
        }
        return false;
    }
    void flip_discs(Point center)
    {
        for (Point dir : directions)
        {
            // Move along the direction while testing.
            Point p = center + dir;
            if (!is_disc_at(p, get_next_player(cur_player)))
                continue;
            std::vector<Point> discs({p});
            p = p + dir;
            while (is_spot_on_board(p) && get_disc(p) != EMPTY)
            {
                if (is_disc_at(p, cur_player))
                {
                    for (Point s : discs)
                    {
                        set_disc(s, cur_player);
                    }
                    disc_count[cur_player] += discs.size();
                    disc_count[get_next_player(cur_player)] -= discs.size();
                    break;
                }
                discs.push_back(p);
                p = p + dir;
            }
        }
    }

public:
    OthelloBoard()
    {
        reset();
    }
    OthelloBoard(const OthelloBoard& to_copy){
        for(int i=0; i<SIZE; i++)
            for(int j=0; j<SIZE; j++)
                board[i][j] = to_copy.board[i][j];
        cur_player = to_copy.cur_player;
        disc_count[EMPTY] = to_copy.disc_count[EMPTY];
        disc_count[BLACK] = to_copy.disc_count[BLACK];
        disc_count[WHITE] = to_copy.disc_count[WHITE];
        next_valid_spots = to_copy.get_valid_spots();
        done = to_copy.done;
        winner = to_copy.winner;
    }
    void reset()
    {
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                board[i][j] = EMPTY;
            }
        }
        board[3][4] = board[4][3] = BLACK;
        board[3][3] = board[4][4] = WHITE;
        cur_player = BLACK;
        disc_count[EMPTY] = 8 * 8 - 4;
        disc_count[BLACK] = 2;
        disc_count[WHITE] = 2;
        next_valid_spots = get_valid_spots();
        done = false;
        winner = -1;
    }
    std::vector<Point> get_valid_spots() const
    {
        std::vector<Point> valid_spots;
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
            {
                Point p = Point(i, j);
                if (board[i][j] != EMPTY)
                    continue;
                if (is_spot_valid(p))
                    valid_spots.push_back(p);
            }
        }
        return valid_spots;
    }
    bool put_disc(Point p)
    {
        if (!is_spot_valid(p))
        {
            winner = get_next_player(cur_player);
            done = true;
            return false;
        }
        set_disc(p, cur_player);
        disc_count[cur_player]++;
        disc_count[EMPTY]--;
        flip_discs(p);
        // Give control to the other player.
        cur_player = get_next_player(cur_player);
        next_valid_spots = get_valid_spots();
        // Check Win
        if (next_valid_spots.size() == 0)
        {
            cur_player = get_next_player(cur_player);
            next_valid_spots = get_valid_spots();
            if (next_valid_spots.size() == 0)
            {
                // Game ends
                done = true;
                int white_discs = disc_count[WHITE];
                int black_discs = disc_count[BLACK];
                if (white_discs == black_discs)
                    winner = EMPTY;
                else if (black_discs > white_discs)
                    winner = BLACK;
                else
                    winner = WHITE;
            }
        }
        return true;
    }
    std::string encode_player(int state)
    {
        if (state == BLACK)
            return "O";
        if (state == WHITE)
            return "X";
        return "Draw";
    }
    std::string encode_spot(int x, int y)
    {
        if (is_spot_valid(Point(x, y)))
            return ".";
        if (board[x][y] == BLACK)
            return "O";
        if (board[x][y] == WHITE)
            return "X";
        return " ";
    }
    std::string encode_output(bool fail = false)
    {
        int i, j;
        std::stringstream ss;
        ss << "Timestep #" << (8 * 8 - 4 - disc_count[EMPTY] + 1) << "\n";
        ss << "O: " << disc_count[BLACK] << "; X: " << disc_count[WHITE] << "\n";
        if (fail)
        {
            ss << "Winner is " << encode_player(winner) << " (Opponent performed invalid move)\n";
        }
        else if (next_valid_spots.size() > 0)
        {
            ss << encode_player(cur_player) << "'s turn\n";
        }
        else
        {
            ss << "Winner is " << encode_player(winner) << "\n";
        }
        ss << "+---------------+\n";
        for (i = 0; i < SIZE; i++)
        {
            ss << "|";
            for (j = 0; j < SIZE - 1; j++)
            {
                ss << encode_spot(i, j) << " ";
            }
            ss << encode_spot(i, j) << "|\n";
        }
        ss << "+---------------+\n";
        ss << next_valid_spots.size() << " valid moves: {";
        if (next_valid_spots.size() > 0)
        {
            Point p = next_valid_spots[0];
            ss << "(" << p.x << "," << p.y << ")";
        }
        for (size_t i = 1; i < next_valid_spots.size(); i++)
        {
            Point p = next_valid_spots[i];
            ss << ", (" << p.x << "," << p.y << ")";
        }
        ss << "}\n";
        ss << "=================\n";
        return ss.str();
    }
    std::string encode_state()
    {
        int i, j;
        std::stringstream ss;
        ss << cur_player << "\n";
        for (i = 0; i < SIZE; i++)
        {
            for (j = 0; j < SIZE - 1; j++)
            {
                ss << board[i][j] << " ";
            }
            ss << board[i][j] << "\n";
        }
        ss << next_valid_spots.size() << "\n";
        for (size_t i = 0; i < next_valid_spots.size(); i++)
        {
            Point p = next_valid_spots[i];
            ss << p.x << " " << p.y << "\n";
        }
        return ss.str();
    }
};

int importance[8][8] = {
    500, -25, 10, 5, 5, 10, -25, 500,
    -25, -50, -5, 1, 1, -5, -50, -25,
    10, -5, 2, 2, 2, 2, -5, 10,
    5, 1, 2, -3, -3, 2, 1, 5,
    5, 1, 2, -3, -3, 2, 1, 5,
    10, -5, 2, 2, 2, 2, -5, 10,
    -25, -50, -5, 1, 1, -5, -50, -25,
    500 , -25, 10, 5, 5, 10, -25, 500,
};

int player;
const int SIZE = 8;
std::array<std::array<int, SIZE>, SIZE> board;
std::vector<Point> next_valid_spots;

void read_board(std::ifstream& fin) {
    fin >> player;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fin >> board[i][j];
        }
    }
}

bool is_corner(Point p){
    if(p.x == 0 || p.x == 7){
        if(p.y == 0 || p.y == 7)
            return true;
    }
    return false;
}

bool is_buffer(Point p){
    if(p.x == 0 || p.x == 7){
        if(p.y == 1 || p.y == 6)
            return true;
    }
    else if(p.x == 1 || p.x == 6){
        if(p.y == 1 || p.y == 7)
            return true;
    }
    return false;
}
Point closest_corner(Point p){
    if(p.x + p.y == 1)       // 左上
        return Point(0,0);
    else if(p.x + p.y == 13) // 右下
        return Point(7,7);
    else if(p.x < p.y)       // 左下
        return Point(0,7);
    else                     // 右上
        return Point(7,0); 
}
int count_stability(OthelloBoard &cur){ // 這裡只考慮最外圍相連的棋子
    int stability = 0;
    int A_row = 0, H_row = 0, A_column = 0, H_column = 0;
    if(cur.board[0][0] == cur.cur_player){
        for(int j=1; j<SIZE && cur.board[0][j] == cur.cur_player; j++){ // 直排
             stability++;
             if(j == 7) A_column = 1; // 第ㄧ直排都為我方棋子
        }
        for(int j=1; j<SIZE && cur.board[j][0] == cur.cur_player; j++){ // 橫排
            stability++;
            if(j == 7) A_row = 1; // 第ㄧ橫排都為我方棋子
         }
    }
    if(cur.board[0][7] == cur.cur_player){
        for(int j=6; j>0 && cur.board[0][j] == cur.cur_player && !A_column; j--){ // 直排
             stability++;
        }
        for(int j=1; j<SIZE && cur.board[j][7] == cur.cur_player; j++){ // 橫排
            stability++;
            if(j == 7) H_row = 1; // 最下方橫排都為我方棋子
        }
    }
    if(cur.board[7][0] == cur.cur_player){
        for(int j=1; j<SIZE && cur.board[7][j] == cur.cur_player; j++){ // 直排
             stability++;
             if(j == 7) H_column = 1; // 最右直排都為我方棋子
        }
        for(int j=6; j>=0 && cur.board[j][7] == cur.cur_player && !A_row; j--){ // 橫排
            stability++;
        }
    }
    if(cur.board[7][7] == cur.cur_player){
        for(int j=6; j>=0 && cur.board[7][j] == cur.cur_player && !H_column; j--){ // 直排
             stability++;
        }
        for(int j=6; j>=0 && cur.board[j][7] == cur.cur_player && !H_row; j--){ // 橫排
            stability++;
        }
    }
    return stability;
}
int set_value(OthelloBoard &cur){
    int value = 0;
    //Point p;
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            if(cur.board[i][j] == player){
                value += importance[i][j];
                if(is_buffer(Point(i,j))){ // 已佔據角落，且目前可下的位置跑到buffer
                    Point corner = closest_corner(Point(i,j));
                    if(cur.board[corner.x][corner.y] == player) value += 50;
                }
            }
            else if(cur.board[i][j] == (3-player)) // 對手的棋
                value -= importance[i][j];
        }
    }
    int active_pw = cur.next_valid_spots.size(); // 行動力(可以下的點的總和)
    int stability = count_stability(cur);
    value += active_pw * 10 + stability * 3;
    return value;
}

int minimax(OthelloBoard &board, int depth, int alpha, int beta, int cur_player){
    if(depth == 3 || board.done){
        int value = set_value(board);
        return value;
    }
    int best;
    if(board.cur_player == player){ // 我方
        best = INT_MIN;
        for(auto it=board.next_valid_spots.begin(); it!=board.next_valid_spots.end(); it++){
            OthelloBoard nxt = board;
            Point p = *it;
            nxt.put_disc(p);
            int tmp = minimax(nxt, depth+1, alpha, beta, cur_player);
            best = max(best, tmp);
            alpha = max(best, alpha);
            if(beta <= alpha){
                break;
            }
        }
    }
    else{
        best = INT_MAX;
        for(auto it=board.next_valid_spots.begin(); it!=board.next_valid_spots.end(); it++){
            OthelloBoard nxt = board;
            Point p = *it;
            nxt.put_disc(p);
            int tmp = minimax(nxt, depth+1, alpha, beta, 3-cur_player);
            best = min(best, tmp);
            beta = min(best, beta);
            if(beta <= alpha){
                break;
            }
        }
    }
    return best;
}

void read_valid_spots(std::ifstream& fin) {
    int n_valid_spots;
    fin >> n_valid_spots;
    int x, y;
    for (int i = 0; i < n_valid_spots; i++) {
        fin >> x >> y;
        next_valid_spots.push_back({x, y});
    }
}

void write_valid_spot(std::ofstream& fout) {
    //int n_valid_spots = next_valid_spots.size();
    //start to choose
    int cur_heuristic = 0;
    Point best;
    for(auto it=next_valid_spots.begin(); it!=next_valid_spots.end(); it++){
        OthelloBoard nxt;
        nxt.board = board;
        nxt.cur_player = player;
        Point p = *it;
        nxt.put_disc(p);
        int nxt_heuristic = minimax(nxt, 0, INT_MIN, INT_MAX, player);
        if(cur_heuristic < nxt_heuristic){
            cur_heuristic = nxt_heuristic;
            best = p;
        }
    }
    // Remember to flush the output to ensure the last action is written to file.
    fout << best.x << " " << best.y << std::endl;
    //fout << "VALUE: "<< cur_heuristic << std::endl;
    // Choose the spot.
    fout.flush();
}

int main(int, char** argv) {
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);
    read_board(fin);
    read_valid_spots(fin);
    write_valid_spot(fout);
    fin.close();
    fout.close();
    return 0;
}