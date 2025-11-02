#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll n, k;
vector<ll> s;
vector<vector<ll>> v;
vector<bool> was_cen;

int dfs(ll node, ll parent){
    for(ll u:v[node]){
        if(u == parent) continue;
        s[node]+= dfs(u, node);
    }
    return s[node];
}

int findCentroid(ll node){
    for(ll u:v[node]){
        if(was_cen[u]) continue;
        if(s[u] > n/2){
            was_cen[node] = true;
            s[node] -= s[u];
            s[u]+= s[node];
            return findCentroid(u);
        }
    }
    return s[node];
}
int findPaths(ll a){
    
}

int main(){
    cin >> n >> k;
    s.resize(n+1, 0);
    v.resize(n+1);
    was_cen.resize(n+1, false);

    dfs(0, 1);
    
}