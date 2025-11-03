#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<long long> swamp(int N, int K, vector<int> A, int Q, vector<int> L, vector<int> R)
{
    vector<ll> res;
    vector<ll> c(N, 0);
    map<ll, ll> m;
    for(ll u:A){
        m[u]++;
    }

    for(pair<ll,ll> u:m) {
        for(ll i=0; i<N; i+= u.first) {
            c[i] += u.second;
        }
    }

    vector<ll> d(N, 0);
    d[0] = c[0];
    for(ll i=1; i<N; i++) {
        d[i] = c[i] + d[i-1];
    }
    for(ll i=0; i<Q; i++) {
        res.push_back(d[R[i]] - d[L[i]] + c[L[i]]);
    }
    return res;
}

// int main()
// {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
//     int N, K;
//     cin >> N >> K;
//     vector<int> A(K);
//     for (int i = 0; i < K; i++)
//     {
//         cin >> A[i];
//     }
//     int Q;
//     cin >> Q;
//     vector<int> L(Q), R(Q);
//     for (int i = 0; i < Q; i++)
//     {
//         cin >> L[i] >> R[i];
//     }
//     vector<long long> ret = swamp(N, K, move(A), Q, move(L), move(R));
//     for (int i = 0; i < Q; i++)
//     {
//         cout << ret[i] << "\n";
//     }
//     return 0;
// }