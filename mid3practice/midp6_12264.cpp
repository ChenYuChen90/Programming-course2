#include <iostream>
#include <queue>
#include <deque>
using namespace std;

int main(){
    int n;
    string cmd;
    cin >> n;
    deque<queue<int>> npk;
    while(n--){
        cin >> cmd;
        if(cmd == "ENQUEUE"){
            int x;
            cin >> x;
            bool newcountry = true;
            for(auto it = npk.rbegin(); it != npk.rend(); it++){
                if(it->front() % 3 == x % 3){
                    it->push(x);
                    newcountry = false;
                    break;
                }
            }
            if(newcountry){
                queue<int> country;
                country.push(x);
                npk.push_back(country);
            }
        } else if (cmd == "DEQUEUE"){
            if(!npk.empty()){
                cout << npk.begin()->front() << endl;
                npk.begin()->pop();
                if(npk.begin()->empty()) npk.pop_front();
            }
        }
    }
}