#include <iostream>
#include <queue>
using namespace std;

struct State {
    int lv, hp, mhp;
    int dist;
    State(int lv, int hp, int mhp, int dist = 0):lv(lv), hp(hp), mhp(mhp), dist(dist) {}
};

bool vis[20][310][410];

int main(){
    int L, hp, mhp, mdmg;
    int dmg[20], hl[20];
    cin >> L >> hp >> mhp >> mdmg;
    
    for(int i = 1; i <= L; i++)
        cin >> dmg[i] >> hl[i];

    for(int i = 1; i < 20; i++)
        for(int j = 1; j < 310; j++)
            for(int z = 1; z < 410; z++)
                vis[i][j][z] = false;

    queue<State> q;
    q.push(State(1, hp, mhp));

    while(!q.empty()){
        State s = q.front();
        q.pop();

        // stop stituation
        if(s.mhp <= 0)
            break;
        if(s.hp  <= 0)
            continue;

        // Caculate the next state
        if(vis[s.lv][s.hp][s.mhp] == true) continue;
        vis[s.lv][s.hp][s.mhp] = true;

        // lavel up
        if(s.lv < L){
            State ns_l(s.lv + 1, s.hp - mdmg, s.mhp, s.dist + 1);
            q.push(ns_l);
        }
        // attack
        State ns_a(s.lv, s.hp - mdmg, s.mhp - dmg[s.lv], s.dist + 1);
        q.push(ns_a);
        // heal
        if(s.hp + hl[s.lv] < hp){
            State ns_h(s.lv, s.hp - mdmg + hl[s.lv], s.mhp, s.dist + 1);
            q.push(ns_h);
        }
    }

    if(q.empty())
        cout << -1 << endl;
    else 
        cout << q.front().dist << endl;
    
    return 0;
}