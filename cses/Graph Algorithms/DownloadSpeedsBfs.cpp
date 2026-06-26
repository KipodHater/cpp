#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e10;
ll c[1001], f[1001];
vector<vector<pair<ll, ll>>> graph;
bool visited[501];
ll res = 0;

ll cap(int j) {
    return j > 0 ? (c[j] - f[j]) : (f[-j]);
}

void update(int j, int val) {
    if(j > 0) f[j] += val;
    else f[-j] -= val;
}

int itr(ll d, ll target, ll minVal) {
    queue<pair<ll, ll>> q;
    q.push({d, INF});
    pair<ll, ll> last;

    while(q.size()) {
        last = q.front();
        q.pop();
        if(last.first == target) return minVal;
        visited[last.first] = true;
        
    }
    
    visited[d] = 1;
    for(auto u:graph[d]) {
        ll r = cap(u.second);
        if(!r || visited[u.first]) continue;
        ll x = itr(u.first, target, min(r, minVal));
        if(x>0) {
        update(u.second, x);
        return x;
        }
    }
    return 0;
}

int path(ll s, ll t) {
    fill(visited, visited + 501, 0);
    ll x = itr(s, t, INF);
    res += x;
    return x;
}

int main() {
    std::ios_base::sync_with_stdio(0); cin.tie(NULL);
    ll n, m;
    cin >> n >> m;
    graph.resize(n+1);
    ll a, b;
    for(ll i=1; i<=m; i++) {
        cin >> a >> b >> c[i];
        graph[a].push_back({b, i});
        graph[b].push_back({a, -i});
    }
    while(path(1, n));
    cout << res;
}