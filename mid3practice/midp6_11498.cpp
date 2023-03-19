#include <iostream>
#include <vector>
#include <set>
using namespace std;
int main(){
    int N;
    int root;
    
    while(cin >> N){
        if(N == 0) return 0;
        vector<set<int>> node(1005);
        int ans = 0;
        while(N--){
            int a, b;
            cin >> a >> b;
            node[a].insert(b);
            node[a].insert(0);
            node[b].insert(0);
        }
        cin >> root;
        for(auto n:node){
            if(n.size() == 1) ans++;
        }
        cout << ans << endl;
    }
    return 0;
}