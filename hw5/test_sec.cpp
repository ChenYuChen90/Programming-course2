#include <iostream>
#include <fstream>

#include <iostream>
#include <vector>
#include <list>
#include <set>

using std::vector;
using std::set;
using std::list;
using std::cout;
using std::endl;

// A state contains five components:
// The first two components denote the current numbers of
// missionaries and cannibals at the left bank of the river.
// The third and fourth components denote the current numbers
// of missionaries and cannibals at the right bank.
// The fifth component denotes the location of the boat:
// 1 means "left bank" and -1 means "right bank".
using State = vector<int>;
class Crossing
{
private:
    vector<int> _npeople;  // how many missionaries and cannibals
                           // we use vector<int> as a tuple (int, int)
                           // the first integer indicate the number of missionaries
                           // the second integer indicates the number of cannibals
    set<list<State>> _paths;  // trial paths in progress
    set<State> _explored;     // explored states
    set<list<State>> _solutions;
public:
    // specify the numbers of missionaries and cannibals
    Crossing(vector<int> np): _npeople {np} { }
    // the starting porint of your implementation
    void solve(){
        State iniState{_npeople};
        iniState.push_back(0);
        iniState.push_back(0);
        iniState.push_back(1);
        list<State> path;
        path.push_back(iniState);
        _paths.insert(path);

        int step = 100;
        while(step > 0){
            set<list<State>> newPaths;
            for(auto p:_paths){
                _explored.insert(p.back());
                auto newState = extend(p.back());
                for(auto ns:newState){
                    if(found(ns)){
                        auto np = p;
                        np.push_back(ns);
                        _solutions.insert(np);
                    } else {
                        auto search = _explored.find(ns);
                        if(search == _explored.end()){
                            auto np = p;
                            np.push_back(ns);
                            newPaths.insert(np);
                        }
                    }
                }
            }
            _paths = newPaths;
            --step;
        }
    }
    // extend to other possible states from a certain state
    set<State> extend(State s){
        set<State> newState;

        for(int m = 0; m <= 2; m++){
            for(int c = 0; c + m <= 2; c++){
                if(c + m >= 1){
                    State ss = Go(s, m, c);
                    if(valid(ss))
                        newState.insert(ss);
                }
            }
        }

        return newState;
    }
    // may use s[4] to indicate the direction of move
    State Go(State s, int missionary, int cannibal){
        s[0] -= s[4] * missionary;
        s[1] -= s[4] * cannibal;
        s[2] += s[4] * missionary;
        s[3] += s[4] * cannibal;
        s[4] = -s[4];
        return s;
    }
    // check the validity of a state
    bool valid(State s){
        if(s[0] < 0 || s[1] < 0 || s[2] < 0 || s[3] < 0) return false;
        if((s[0] < s[1] && s[0] != 0) || (s[2] < s[3] && s[2] != 0)) return false;
        return true;
    }
    // check if all people are at the right bank
    bool found(State s){
        if(s[0] == 0 && s[1] == 0 && s[4] == -1) return true;
        else return false;
    }
    void show_solutions() {
        for (auto path : _solutions) {
            for (auto s : path) {
                if (!s.empty()) {
                    cout << "(" << s[0] << ", " << s[1] << ")";
                    cout << "(" << s[2] << ", " << s[3] << ")";
                    if (s[4]==1) cout << " left\n";
                    else cout << " right\n";
                }
            }
            cout << "done" << endl;
        }
    }
};

using namespace std;

int main(int argc, char *argv[]) {
    int X, Y; //Number of missionaries and cannibals
    cin >> X >> Y;
    Crossing p({X, Y});
    p.solve();
    p.show_solutions();
}