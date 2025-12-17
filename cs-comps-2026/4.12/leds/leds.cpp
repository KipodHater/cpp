#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> v;
vector<bool> visited;
const int INF = 1e9;
int average = 0;

int rec(int a) {
    visited[a] = true;
    vector<int> b;
    for(int u:v[a]) {
        if(!visited[u]) {
            int r = rec(u);
            if(r == -1) return -1;
            b.push_back(r);
        }
    }
    if((b.size()% 2) == 0) b.push_back(0);
    sort(b.begin(), b.end());
    int j = b.size()-1;
    int i = 0;
    int res = INF;
    int l=0; int r = b.size();
    int m = (l+r)/2;
    bool flag = false;
    while(l<r) {
        j = b.size()-1;
        i=0;
        flag = false;
        m = (l+r)/2;
        if(b[m]>average) return -1;
        if(i == m) i++;
        if(j == m) j--;
        while(i < j) {
            if(b[i]+b[j] > average) {
                flag = true;
                break;
            }
            i++; j--;
            if(i == m) i++;
            if(j == m) j--;
        }
        if(!flag) {
            r = m;
            res = min(res, b[m]);
        }
        else l = m+1;
    }

    return (res == INF) ? -1 : (res+1);
}

int bfs(int a) {
    queue<int> s;
    int c = 1;
    s.push(a);
    int last;
    while(!s.empty()) {
        last = s.front();
        s.pop();
        visited[last] = true;
        c+= (v[last].size()-1)/2;
        for(int u : v[last]) {
            if(!visited[u]) {
                s.push(u);
                visited[u] = true;
            }
        }
    }
    return c;
}

pair<int, int> LightItUp(int N, vector<int> A, vector<int> B){
    v.resize(N);
    visited.resize(N, false);
    for(int i=0; i<N-1; i++) {
        v[A[i]-1].push_back(B[i]-1);
        v[B[i]-1].push_back(A[i]-1);
    }
    int l = 1;
    int r = N;
    int m;
    int x = N;
    int start = -1;
    for(int i=0; i<N; i++) {
        if(v[i].size() == 1) {
            start = i;
            break;
        }
    }
    int t = bfs(start);
    while(l < r) {
        m = (l+r)/2;
        average = m;
        visited.clear();
        visited.resize(N, false);
        int g = rec(start);
        if(g == -1){
            l = m+1;
            continue;
        }
        x = m;
        r = m;
    }
    return {t,x};
}



// int readInt(){
// 	int i;
// 	if(scanf("%d",&i)!=1){
// 		fprintf(stderr,"Error while reading input\n");
// 		exit(1);
// 	}
// 	return i;
// }

// int main(){
// 	 std::ios_base::sync_with_stdio(0);
//     int N;
//     N = readInt();
//     vector<int> A(N-1);
// 	vector<int> B(N-1);

//     for (int i = 0; i < N-1; ++i) {
// 	scanf("%d %d", &A[i], &B[i]);
//     }

//     pair<int, int> ans = LightItUp(N, A, B);
//     printf("%d %d\n", ans.first, ans.second);
//     return 0;
	
// }
