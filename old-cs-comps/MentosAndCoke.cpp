#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;

int quickPow(int a, int b){
    if(b == 0) return 1;
    if(b == 1) return a;

    return quickPow(a*a, b/2) * (b%2? a : 1);
}

int get_max_cola_mentos(int N, std::vector<std::vector<std::pair<int, int> > > B) {
    int MAX_POS = quickPow(2, 11);
    int m = 0;
    for(int i=0; i<MAX_POS; i++){ // 2* 10^3
        int sum = 0;
        for(vector<pair<int, int>> u:B){
            int curSum = 0;
            for(pair<int, int> v : u){
                int c = (i >> abs(v.first)) & 1;
                if(c == 0) c = -1; else c = 1;
                if(v.first * c > 0) curSum += v.second;
                else curSum -= v.second;
            }
            if(curSum>0) sum += curSum;
        }
        m = max(m, sum);
    }
    return m;
}

// int main() {
//     ios_base::sync_with_stdio(false); cin.tie(0);
//     int N;
//     cin >> N;
//     vector<vector<pair<int, int> > > B(N);
//     for (auto &V : B) {
//         int n;
//         cin >> n;
//         V.resize(n);
//         for (auto &[t, c] : V) {
//             cin >> t >> c;
//         }
//     }
//     cout << get_max_cola_mentos(N, B);
//     return 0;
// }