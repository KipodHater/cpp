#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

std::array<int, 3> Concert(int A, int B, int C, int D, std::vector<int> X, std::vector<int> Y){
    vector<bool> e(C, true);
    vector<vector<ll>> v(C, vector<ll>(0));
    for(ll i=0; i<D; i++) v[X[i]].push_back(Y[i]);
    vector<ll> level(C, -1);
    for(ll i=0; i<D; i++) e[Y[i]] = false;

    for(ll i=0; i<C; i++){
        if(e[i]) {
            level[i] = 0;
            queue<ll> q;
            q.push(i);
            ll last;
            while(!q.empty()) {
                last = q.front();
                q.pop();
                for(ll u : v[last]) {
                    q.push(u);
                    level[u] = level[last]+1+ level[u];
                }
            }
        }
    }

    // if(A == C) return {C,C,0};
    // if(B== 0) return {0,0,C};


    vector<bool> e1(C, true);
    vector<vector<ll>> v1(C, vector<ll>(0));
    for(ll i=0; i<D; i++) v1[Y[i]].push_back(X[i]);
    vector<ll> level1(C, -1);
    for(ll i=0; i<D; i++) e1[X[i]] = false;

    for(ll i=0; i<C; i++){
        if(e1[i]) {
            level1[i] = 0;
            queue<ll> q;
            q.push(i);
            ll last;
            while(!q.empty()) {
                last = q.front();
                q.pop();
                for(ll u : v1[last]) {
                    q.push(u);
                    level1[u] = level1[last]+1+level1[u];
                }
            }
        }
    }
        int a = 0;
    int b = 0;
    // if(B == C) b = 
    // sort(level.begin(), level.end());
    for(ll i=0; i<C; i++) {
        if(A >= C-level1[i]) a++;
        if(B >= C-level1[i]) b++;
    }
    int c = 0;
    // bool flag = false;
    // for(ll i=level.size()-2; i>=0; i--) {
    //     thisLevel++;
    //     if(level[i+1] != level[i]){
    //         if(C-B >= level.size()-1 - i) c+=thisLevel;
    //         thisLevel = 0;
    //     }
    // }
    for(ll i=0; i<C; i++) {
        if(C-B < level[i]) c++;
    }
    return {a, b, c};
}
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(NULL);
    int A,B,C,D;
    std::cin >> A >> B >> C >> D;
    std::vector<int> X(D), Y(D);
    for (int i=0; i<D; i++){
        std::cin >> X[i] >> Y[i];
    }
    auto [a, b, c] = Concert(A, B, C, D,std::move(X), std::move(Y));

    std::cout << a << "\n" << b << "\n" << c << "\n";
    return 0;
}
