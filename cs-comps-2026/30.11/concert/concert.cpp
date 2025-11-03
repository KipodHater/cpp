#include <bits/stdc++.h>
#include "concert.h"
using namespace std;
typedef long long ll;
ll n;
ll dfs(ll x, vector<vector<ll>> &V) {
    vector<bool> visited(n, false);
    stack<ll> s;
    s.push(x);
    ll last;
    ll c = 0;
    while(!s.empty()) {
        last = s.top();
        s.pop();
        if(!visited[last]) {
            c++;
            for(ll i : V[last]) s.push(i);
        }
        visited[last] = true;
    }
    return c;
}

std::array<int, 3> Concert(int A, int B, int C, int D, std::vector<int> X, std::vector<int> Y){
    n = C;
    vector<vector<ll>> v(C);
    vector<vector<ll>> u(C);
    
    for(ll i=0; i<D; i++) {
        v[X[i]].push_back(Y[i]);
        u[Y[i]].push_back(X[i]);
    }

    vector<ll> up(C);
    vector<ll> down(C);

    for(ll i=0; i<C; i++) {
        up[i] = dfs(i, u);
        down[i] = dfs(i, v);
    }

    ll a=0;
    ll b=0;
    ll c=0;

    for(ll i=0; i<C; i++) {
        if(C - down[i] < A) a++;
        if(C - down[i] < B) b++;
        if(C - up[i] < C-B) c++;
    }
    return {a, b, c};
}