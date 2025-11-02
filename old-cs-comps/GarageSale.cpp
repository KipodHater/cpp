#include<bits/stdc++.h>
using namespace std;

vector<int> a,b;
vector<bool> visited;
int n,m;

// bool dfs(int j){
//     if(!visited[j]){
//         stack<int> s;

//     } else{
//         return false;
//     }
// }

bool garage_sale(int N, int M, std::vector<int> A, std::vector<int> B){
    n= N; m=M; a = A; b=B;

    visited.resize(N, false);

    vector<int> c (N, 0);
    for(int u:A){
        c[u]++;
    }
    for(int u:c){
        if(u != 1) return false;
    }
    vector<int> d (N, 0);
    for(int u:B){
        d[u]++;
    }
    for(int u:d){
        if(u != 1) return false;
    }
    // for(int i=0;i<N; i++){
    //     if(!visited[i]){
    //         if(!dfs(i)){
    //             return false;
    //         }
    //     }
    // }
    return true;
}

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);

//     int N, M;
//     cin >> N >> M;

//     std::vector<int> A(M), B(M);
//     for (int i = 0; i < M; ++i) {
//         cin >> A[i] >> B[i];
//     }

//     bool result = garage_sale(N, M, A, B);
//     cout << std::boolalpha << result;

//     return 0;
// }