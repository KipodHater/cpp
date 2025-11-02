#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll MOD = 1e9 + 7;
const ll INF = 1e10;
using vll = vector<ll>;

vector<pair<ll, pair<ll, ll>>> arr;
vector<ll> par;
vector<ll> sizes;

ll dsu(ll ver){
    if(par[ver] == ver) return ver;
    ver = dsu(par[ver]);
    return ver;
}

bool un(ll v, ll u){
    ll pv = dsu(v);
    ll pu = dsu(u);
    if(pv == pu) return false;

    if(sizes[pv] < sizes[pu]) swap(pv, pu);
    par[pu] = pv;
    sizes[pv] += sizes[pu];
    return true;
}

int main(){
    ll n, m, a, b, c, d;
    d = 0;
    cin >> n >> m;
    par.resize(n+1, 0);
    sizes.resize(m+1, 1);
    for(ll i=0; i<m; i++) {
        cin >> a >> b >> c;
        arr.push_back({c, {a, b}});
    }
    for(ll i=1; i<n+1; i++) par[i] = i;

    sort(arr.begin(), arr.end());

    ll ans = 0;
    for(pair<ll, pair<ll, ll>> i : arr){
        if(un(i.second.first, i.second.second)){
            ans += i.first;
            d++;
        }
    }
    if(d == n-1) cout << ans << endl;
    else cout << "IMPOSSIBLE" << endl;
}