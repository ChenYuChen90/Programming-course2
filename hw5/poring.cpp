#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <list>
#include <iterator>
#include <string>
#include <sstream>
using namespace std;

using Jug = vector<int>;        // Jug {5,3}
using State = vector<int>;      
using Path = list<State>;       //list<vector<int>>
using Paths = set<Path>;        //set<list<vector<int>>>


iostream& operator<<(ostream& os, State s){
    cout << "(";
    for(auto v:s)
        cout << v << ",";
    cout << ")";
}

class Pouring{
private:
    Jug _capacities;        // {3, 5, 7}
    Paths _paths;           //目前拓展的path
    Paths _solutions;       //找出的path
    set<State> _explored;   //已經走過的state
    
    State Empty(int idx, State s){
        s[idx] = 0;
        return s;
    }
    State Fill(int idx, State s){
        s[idx] = _capacities[idx];
        return s;
    }
    State Pour(int from, int to, State s){
        int diff = _capacities[to] - s[to];
        if(s[from] > diff){
            s[from] = s[from] - diff;
            s[to] = _capacities[to];
        } else {
            s[to] = s[to] + diff;
            s[from] = 0;
        }
        return s;
    }
    set<State> extend(State s){
        set<State> SS;
        for (int i = 0; i < _capacities.size(); ++i) {
            SS.insert(Empty(i, s));
            SS.insert(Fill(i, s));
            for (int j = 0; j < _capacities.size(); ++j) {
                if (i !=j )
                    SS.insert(Pour(i, j, s));
                }
        }
        return SS;
    }
public:
    Pouring(Jug jugs): _capacities{jugs}  {
        for(auto c : _capacities)
            cout << c << " ";
        cout << endl;
    }
    bool found(int target, State s){
        for(auto v : s)
            if(v == target) return true;
        return false;
    }
    void solve(int target, int steps){
        
        //using Jug = vector<int>;        // Jug {5,3}
        //using State = vector<int>;      
        //using Path = list<State>;       //list<vector<int>>
        //using Paths = set<Path>;        //set<list<vector<int>>>

        State ini(_capacities.size());
        Path path;
        path.push_back(ini);
        _paths.insert(path);
        
        while (steps > 0) {
            Paths newPaths;
            for (auto p : _paths){      // p : list<State>
                _explored.insert(p.back());
                auto newStates = extend(p.back());
                for (auto ns : newStates) {
                    if (found(target, ns)){
                        Path np = p;
                        np.push_back(ns);
                        _solutions.insert(np);
                    } else {
                        auto search = _explored.find(ns);
                        if(search == _explored.end()){
                            Path np = p;
                            np.push_back(ns);
                            newPaths.insert(np);
                        }
                    }
                }
            }
            _paths = newPaths;
            --steps;
        }
    }
    void show() {
        for(auto p: _solutions){
            for(auto s: p){
                cout << s << "->";
            }
            cout << endl;
        }
    }
};//end class Pouring
int main(){
    Pouring problem { Jug{5, 3}};
    problem.solve(4, 10);
    problem.show();
}