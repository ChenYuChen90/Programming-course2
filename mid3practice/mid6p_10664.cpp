#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <tuple>
#include <string>
using namespace std;

using State = vector<int>;

class Puzzle {
private:
    State _original;
    set<State> _explored;
public:
    Puzzle(State ori): _original(ori) {}
    void solve(){
        int ans = -1;
        State iniState = _original;
        queue<tuple<State, int>> tasks;
        _explored.insert(iniState);

        tasks.push(make_tuple(iniState, 1));

        if(found(iniState)) ans = 0;
        while(!tasks.empty() && ans == -1){
            // in c++11
            const auto curState = get<0>(tasks.front());
            const auto curStep = get<1>(tasks.front());
            // in c++17
            //const auto [curState, curStep] = tasks.front();
            tasks.pop();

            set<State> nextStates = extand(curState);
            for(auto ns:nextStates){
                if(_explored.find(ns) != _explored.end()) continue;
                if(found(ns)) {
                    ans = curStep;
                    break;
                } else {
                    _explored.insert(ns);
                    if(curStep < 14)
                        tasks.push(make_tuple(ns, curStep + 1));
                }
            }
        }

        if(ans != -1)
            cout << "You can solve it within " << ans << " steps." << endl;
        else
            cout << "You'd better skip this game." << endl;
    }
    set<State> extand(State s){
        static const vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        set<State> nextStates;

        int o_pos = 0;
        for(int i = 0; i < 9; i++){
            if(s[i] == 0) o_pos = i;
        }
        for(auto d:directions){
            State ns = s;
            int x = o_pos % 3 + d[0], y = o_pos / 3 + d[1];
            if((x >= 0 && x < 3 ) && (y >= 0 && y < 3)){
                swap(ns[o_pos], ns[x + 3 * y]);
                nextStates.insert(ns);
            }
        }

        return nextStates;
    }
    bool found(State s){
        static const State tar = {1, 2, 3, 4, 5, 6, 7, 8, 0};
        return tar == s;
    }
};
int main(){
    int T;
    cin >> T;

    while(T--){
        State original(9);
        for(int i = 0; i < 9; i++)
            cin >> original[i];
        
        Puzzle problem(original);
        problem.solve();
    }
    return 0;
}