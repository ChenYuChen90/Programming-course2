#include <iostream>
#include <set>

using namespace std;

int main(){
    set<int> myset{};
    int N;
    string cmd;
    int num, l, r;
    
    cin >> N;
    while(N--){
        cin >> cmd;
        if(cmd == "insert"){
            cin >> num;
            myset.insert(num);
        } else if( cmd == "print") {
            if(!myset.empty()){
                for (set<int>::iterator it = myset.begin(); it != myset.end(); it++) {
                    if(it != myset.begin())
                        cout << " " << *it;
                    else
                        cout << *it;
                }
                cout << "\n";
            }
        } else if( cmd == "min") {
            if(!myset.empty()){
                set<int>::iterator it = myset.begin();
                cout << *it;
                cout << '\n';
            }
        } else if(cmd == "range_erase") {
            cin >> l >> r;
            if(!myset.empty()){
                myset.erase(myset.lower_bound(l), myset.upper_bound(r));
            }
        }
    }
    return 0;
}
