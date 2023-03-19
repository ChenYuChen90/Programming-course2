#include <iostream>
#include <queue>

using namespace std;
int main(){
    queue<string> q;
    string cmd, name;
    while(cin >> cmd) {
        if(cmd == "Push"){
            cin >> name;
            q.push(name);
        } else if(cmd == "Front"){
            if(!q.empty()){
                cout << q.front() << endl;
            } else {
                cout << "empty" << endl;
            }
        } else if(cmd == "Pop"){
            if(!q.empty()){
                q.pop();
            }
        }
    }
}