#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e10;
ll c[1001], f[1001];
vector<vector<pair<ll, ll>>> graph;
bool visited[501];
ll res = 0;
ll n;

ll cap(int j) {
    return j > 0 ? (c[j] - f[j]) : (f[-j]);
}

void update(int j, int val) {
    if(j > 0) f[j] += val;
    else f[-j] -= val;
}

int path(ll s, ll t) {
    fill(visited, visited + 501, 0);
    queue<int> q;
    q.push(s);
    vector<pair<int, int>> prev(n+1);
    prev[s] = {s, 0};
    while(!q.empty()) {
        int node = q.front();
        q.pop();
        visited[node] = true;
        for(auto [u, e] : graph[node]) {
            if(!prev[u].first && cap(e) > 0) {
                prev[u] = {node, e};
                q.push(u);
            }
        }
    }
    if(!prev[t].first) return 0;
    ll x = INF;
    ll next = t;
    vector<int> fPath;
    while(next != s) {
        fPath.push_back(prev[next].second);
        x = min(x, cap(prev[next].second));
        next = prev[next].first;
    }
    for(int e : fPath) update(e, x);
    res += x;
    return x;
}

int main() {
    std::ios_base::sync_with_stdio(0); cin.tie(NULL);
    ll m;
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