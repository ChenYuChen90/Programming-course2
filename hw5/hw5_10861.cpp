#include <iostream>
#include <stack>
#include <string>

using namespace std;
int main(){
    int N;
    cin >> N;
    cin.ignore();
    for(int i = 1; i <= N; i++){
        stack<char> p;
        string str;
        bool check = true;
        getline(cin, str);
        for(auto c : str){
            if(c == '}' || c == ']' || c == '>' || c == ')'){
                if(p.empty()){
                    check = false;
                    break;
                } else if (c == '}') {
                    if(p.top() != '{'){
                        check = false;
                        break;
                    }
                } else if (c == ']') {
                    if(p.top() != '['){
                        check = false;
                        break;
                    }
                } else if (c == '>') {
                    if(p.top() != '<'){
                        check = false;
                        break;
                    }
                } else if (c == ')') {
                    if(p.top() != '('){
                        check = false;
                        break;
                    }
                }
                p.pop();
            } else if (c == '{' || c == '[' || c == '<' || c == '('){
                p.push(c);
            }
        }
        if(!p.empty()) check = false;
        cout << "Case " << i << ": ";
        if(check)
            cout << "Yes";
        else
            cout << "No";
        cout << endl;
    }
}