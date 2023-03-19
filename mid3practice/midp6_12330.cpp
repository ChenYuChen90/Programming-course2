#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// G[i] is the neighbor towns of town i
vector<int> diamondTowns;
vector<int> G[100005];
int Dist[100005];

struct node {
    int id;
    int dist;
    node(int id, int l) {
        this->id = id;
        this->dist = l;
    }
};

int main() {
    int N, M, K;
    cin >> N >> M >> K;
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    for (int i = 0; i < K; i++) {
        int x;
        cin >> x;
        diamondTowns.push_back(x);
    }
    fill(Dist, Dist+100005, -1);

    queue<node> Q;
    for(int i = 0; i < K; i++){
        Q.push(node(diamondTowns[i], 0));
    }
    while(!Q.empty()){
        node curnode = Q.front();
        Q.pop();
        if(Dist[curnode.id] == -1){
            Dist[curnode.id] = curnode.dist;
        } else {
            continue;
        }
        for(auto near:G[curnode.id]){
            Q.push(node(near, curnode.dist + 1));
        }
    }

    // Output
    for (int i = 1; i <= N; i++) {
        cout << Dist[i] << '\n';
    }
    return 0;
}