#include<bits/stdc++.h>
using namespace std;

typedef long long ll;



int fingerprint(int N, int F, std::vector<int> P){
    priority_queue<pair<int, int>> q; 
    vector<int> city(N, 1);
    int f = F - N;
    for(int i=0; i<N; i++){
        q.push({P[i], i});
    }
    pair<int, int> cur;
    int positions;
    while(f>0){
        cur = q.top();
        city[cur.second] += 1;
        f -= 1;
        q.pop();
        positions = (int) ceil(1.0 * P[cur.second] / city[cur.second]);
        q.push({positions, cur.second});
    }

    return q.top().first;
}

// int main() {
//     ios_base::sync_with_stdio(false); cin.tie(NULL);
//     int N, F;
//     cin >> N >> F;
//     vector<int> P(N);
//     for (auto &e : P) {
//         cin >> e;
//     }
//     cout << fingerprint(N, F, move(P)) << "\n";
//     return 0;
// }
