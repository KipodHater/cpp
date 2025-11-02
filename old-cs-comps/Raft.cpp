#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

long long raft(int N, std::vector<long long> T){
    sort(T.begin(), T.end());
    ll d = T[0]+ 2*T[1];
    ll res = 0;

    ll a, b; // a > b
    ll i = T.size() -1;
    while(i>2){
        a = T[i];
        b = T[i-1];
        i -= 2;
        if(a + d < 2 * T[0] + a + b){
            res += a + d;
        } else{
            res += 2 * T[0] + a + b;
        }
    }

    if(i == 2){
        res += T[0] + T[1] + T[2];
    } else if(i == 1){
        res += T[1];
    }
    return res;
}

// int main() {
//     ios_base::sync_with_stdio(false); cin.tie(NULL);
//     int N;
//     cin >> N;
//     vector<long long> T(N);
//     for (int i=0; i<N; i++){
//         cin >> T[i];
//     }
//     long long ret = raft(N, T);
//     cout <<ret<<"\n";
//     return 0;
// }