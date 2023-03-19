#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int a, n;
    bool police = false;
    string cmd;
    queue<int> country[3];
    deque<int> line;
    while(cin >> cmd){
        if(cmd == "ENQUEUE"){
            cin >> a;
            n = a % 3;
            if(police){
                if(!country[n].empty()) country[n].push(-1);
                country[n].push(a);
                line.push_back(n);
                continue;
            }
            country[n].push(a);
            if(find(line.begin(),line.end(),n) == line.end()) line.push_back(n);
        }
        else if (cmd == "DEQUEUE"){
            if(!line.empty()){
                n = line.front();
                cout << country[n].front() << "\n";
                country[n].pop();
                if(country[n].empty()) line.pop_front();
                else if(country[n].front() == -1){
                    line.pop_front();
                    country[n].pop();
                }
            }
        }
        else if(cmd == "POLICEWATCHING"){
            police = true;
        }
        else if(cmd == "DONUTSTIME"){
            police = false;
        }
    }
}