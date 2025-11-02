#include <bits/stdc++.h>
using namespace std;

vector<int> Zombies(int N, int M, int A, int K, vector<pair<int,int>> T, vector<int> D, vector<int> B){
    vector<vector<int>> v(N, vector<int>);
    vector<vector<int>> l(N, vector<int>(N, -1));
    for(int i=0; i<M; i++){
        pair<int, int> u = T[i];
        v[u.first].push_back(u.second);
        v[u.second].push_back(u.first);
        l[u.first][u.second] = D[i];
        l[u.second][u.first] = D[i];
    }
    
}


int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    while(true){
        int N, M, A, K;
        cin >> N >> M >> A>> K;
        if (N == 0){
            break;
        }
        vector<pair<int,int>> T(M);
        vector<int> D(M);
        for (int i = 0; i < M; i++)
        {
          cin >> T[i].first >> T[i].second >> D[i];
        }
        vector<int> B(A);
        for (int i=0; i<A; i++){
            cin >> B[i];
        }
        vector<int> ret = Zombies(N, M, A, K, move(T), move(D),move(B));
        for (int i=0; i<A; i++){
            cout << ret[i] << "\n";
        }
        cout << "\n";
    }
    return 0;

}