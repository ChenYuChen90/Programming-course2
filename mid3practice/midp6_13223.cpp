#include <queue>
#include <iostream>
#include <vector>
using namespace std;

struct comparator {
    bool operator()(pair<int, int> pa, pair<int, int> pb) {
        if(pa.first < pb.first) return true;
        if(pa.first > pb.first) return false;
        if(pa.second < pb.second) return true;
        return false;
    }
};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, L;
    cin >> N >> L;
    vector<int> A(1000005);
    priority_queue<pair<int, int>, vector<pair<int, int>>, comparator> Q;

    for(int i = 1, num, low_bound = 1; i <= N; i++){
        cin >> num;
        Q.push(make_pair(num, i));
        if(i >= L){
            cout << Q.top().first << " ";
            while(Q.top().second <= low_bound) Q.pop();
            low_bound++;
        }
    }
    cout << endl;
    return 0;
}