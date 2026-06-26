#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> a;
vector<int> visited;
int n, m, d, e;
vector<set<int>> v;
set<int> s;

void dsu(int b, int val) {
    visited[b] = true;
    a[b] = val;
    for(auto i:v[b]) {
        if(!visited[i]) dsu(i, val);
    }
}

void init(int N, int M, int Q, vector<int> A, vector<int> B){
    e = 0;
    n = N; m = M;
    v.resize(n);
    a.resize(N, -1);
    visited.resize(N, false);
    for(int i=0; i<M; i++) {
        v[A[i]].insert(B[i]);
        v[B[i]].insert(A[i]);
    }
    for(int i=0; i<n; i++) {
        if(!visited[i]) {
            dsu(i, e);
            e++;
        }
    }
    for(int i=0; i<e; i++) s.insert(i);
    d = e;
    return;
}

int query(int C, int D){
    s.erase(a[C]);
    int f = a[C];
    v[C].erase(D);
    v[D].erase(C);
    visited.clear();
    visited.resize(n, false);
    dsu(C, e);
    s.insert(e);
    e++;
    for(int i=0; i<n; i++) {
        if(a[i] == f) s.insert(f);
    }
    return s.size();
}
// int main(){
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
//     int n,m,q;
//     cin >> n >> m >> q;
//     vector<int> A,B;
//     for (int i=0;i<m;i++){
//         int a,b;
//         cin >> a >> b;
//         A.push_back(a);
//         B.push_back(b);
//     }
//     init(n,m,q,std::move(A),std::move(B));
//     for (int i=0;i<q;i++) {
//         int a,b;
//         cin >> a >> b;
//         cout << query(a,b) << "\n";
//     }
// }