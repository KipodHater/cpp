#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;
typedef pair<ll, ll> pll;

ll n;
vector<vll> v;
vector<ll> s;
vector<bool> was_cen;

int dfs(ll node, ll parent){
    for(ll u:v[node]){
        // if(u == parent) continue;
        s[node]+= dfs(u, node);
    }
    return s[node];
}

int findCentroid(ll node){
    for(ll u:v[node]){
        if(was_cen[u])continue;
        if(s[u] > n/2){
            was_cen[node] = true;
            s[node] -= s[u];
            s[u]+=s[node];
            return findCentroid(u);
        }
    }
    return node;
}

int main(){

    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    v.resize(n+1);
    s.resize(n+1, 1);
    was_cen.resize(n+1, false);
    for(ll i=0; i<n-1; i++){
        ll e,f;
        cin >> e >> f;
        v[e].push_back(f);
        v[f].push_back(e);
    }
    dfs(1, -1);
    cout << findCentroid(1);

}
