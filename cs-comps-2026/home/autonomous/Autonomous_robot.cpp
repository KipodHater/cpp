#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000000+7;

vector<ll> visited;
vector<bool> circle;
vector<vector<ll>> v;
ll res, k;
vector<ll> starts;

ll power(ll a, ll b) {
    if(b == 0) return 0;
    if(b == 1) return a;
    ll c = power(a, b/2);
    return c * c * ((b&1) ? b : 1) % MOD;
}

pair<ll, ll> dfs(ll i, ll f, ll s) {
    visited[i] = s;
    if(v[i].size() == 0) {
        circle[i] = true;
        return {i, 1};
    }
    if(v[i].size() == 1 && f != i) {
        return {-1, -1};
    }
    if(v[i].size() == 2 && f != i) {
        if(v[i][0] == v[i][1]) return {-1, -1};
    }
    ll res = -1;
    pair<ll, ll> save;
    for(ll u : v[i]) {
        if(f == u) continue;
        if(visited[u] == s) {
            if(res == -1) {
                circle[i] = true;
                res = u;
            }
        }
        else if(visited[u] == 0) {
        save = dfs(u, i, s);
        if(save.first != -1)  {
            if(save.first != -2) circle[i] = true;
            if(save.first == i) {
                starts.push_back(i);
                if(res == -1) res = -2;
            }
            res = save.first;
        }
    }
    }
    return {res, -1};
}

int Autonomous_robot(int N, int K, vector<int> F){
    res = 1; k = K;
    vector<ll> c;
    v.resize(N);
    for(ll i = 0; i<N; i++) {
        if(F[i] == i) continue;
        v[i].push_back(F[i]);
        v[F[i]].push_back(i);
    }
    c.resize(N+1, 0);
    circle.resize(N, false);
    c[1] = K;
    c[2] = K * (K-1) % MOD;
    for(ll i=3; i<=N; i++) {
        c[i] =  (K * power(K-1, i - 1)  % MOD + MOD - c[i-1]) % MOD; // problem probably
    }
    visited.resize(N, 0);
    ll t = 0;
    // run dfs label circles
    for(ll i=0; i<N; i++) {
        if(visited[i] == 0) {
            t++;
            // run bfs thingy
            pair<ll, ll> a = dfs(i, i, t); // label circle problem
            if(a.first == -1) {
                circle[i] = true;
                starts.push_back(i);
            } else if (a.first != -1 && a.first != -2) {
                starts.push_back(a.first);
            }
        }
    }
    visited.clear();
    visited.resize(N, 0);
    for(auto u : starts) {
        if(visited[u]) continue;
        stack<ll> s;
        ll last;
        ll cs = 0;
        s.push(u);
        while(!s.empty()) {
            last = s.top();
            s.pop();
            visited[last] = 1;
            if(!circle[last]) res = res * (K-1) % MOD;
            else {
                cs++;
            }
            for(ll j : v[last]) {
                if(!visited[j]) {
                    s.push(j);
                    visited[j] = 1;
                }
            }
        }
        res = res * c[cs] % MOD;
    }
    return res % MOD;
}

// int main() {
//     ios_base::sync_with_stdio(false); cin.tie(NULL);
//     int N, K;
//     cin >> N >> K;
//     vector<int> F(N);
//     for (int i=0; i<N; i++){
//         int num;
//         cin >> num;
//         F[i] = num;
//     }

//     cout <<Autonomous_robot(N,K,move(F))<<"\n";
//     return 0;
// }