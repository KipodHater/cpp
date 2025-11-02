#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int minimal_amount_of_changes(int N, int M, int T, std::vector<int> A, std::vector<int> B, std::vector<int> C) {
    priority_queue<pair<pair<ll, ll>, ll>, vector<pair<pair<ll, ll>, ll>>, greater<pair<pair<ll, ll>, ll>>> q;
    vector<vector<pair<ll, ll>>> v(N, vector<pair<ll, ll>>(0));
    for(ll i=0; i<M; i++){
        v[A[i]-1].push_back({B[i]-1, C[i]});
        v[B[i]-1].push_back({A[i]-1, -C[i]});
    }
    vector<vector<ll>> mins(N, vector<ll>(M + 1,T+1));
    // vector<ll> k(N, M);
    // mins[0][0] = 0;
    for(ll i=0; i<M+1; i++){
        mins[0][i] = 0;
    }
    // k[0] = 0;

    pair<pair<ll, ll>, ll> last = {{0,0}, 0};
    q.push(last);
    while(!q.empty()){
        last = q.top();
        q.pop();
        // if(mins[last.second] >= last.first.second) mins[last.second] = last.first.second;
        // else continue;
        for(pair<ll, ll> i : (v[last.second])){
            ll d = i.second<0 ? 1 : 0;
            if(mins[i.first][last.first.first + d] > abs(i.second) + mins[last.second][last.first.first] && last.first.first + d != M+1){
                mins[i.first][last.first.first + d] = abs(i.second) + mins[last.second][last.first.first];
                // k[i.first] = d+last.first.first;
                q.push({{d+last.first.first, abs(i.second) + mins[last.second][last.first.first]}, i.first});
            }
        }
        if(last.first.first > M) break;
        // if(mins[N-1] <= T) return last.first.first;
    }
    for(ll i=0; i<M+1; i++){
        if(mins[N-1][i] <= T) return i;
    }
    return -1;
}
// int main() {
//     std::ios_base::sync_with_stdio(false);
//     std::cin.tie(0);

//     int N, M, T;
//     std::cin >> N >> M >> T;

//     std::vector<int> A(M), B(M), C(M);
//     for (int i = 0; i < M; ++i) {
//         std::cin >> A[i] >> B[i] >> C[i];
//     }

//     int result = minimal_amount_of_changes(N, M, T, A, B, C);
//     std::cout << result << "\n";

//     return 0;
// }