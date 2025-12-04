#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> v;
vector<bool> visited;
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
    if(b.empty()) return 1;
    if(b.size() == 1) return b[0]+1;
    if((b.size() & 1) == 0) b.push_back(0);
    sort(b.begin(), b.end());
    int j = b.size()-1;
    int i = 0;
    int res = 1000000000;
    int l=0; int r = b.size();
    int m = (l+r)/2;
    bool flag = false;
    while(l<r) {
        m = (l+r)/2;
        while(i <= j) {
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
        else l = m;
    }
    
    return (res == 1000000000) ? -1 : (res+1);
}

int bfs(int a) {
    stack<int> s;
    int c = 1;
    s.push(a);
    int last;
    while(!s.empty()) {
        last = s.top();
        s.pop();
        int b = 0;
        visited[last] = true;
        c+= (v[last].size()+1)/2-1;
        for(int u : v[last]) {
            if(!visited[u]) {
                s.push(u);
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
    int t = bfs(0);
    int l = ceil(1.0 * (N-1) / t);
    int r = N;
    int m;
    visited.clear();
    visited.resize(N, false);
    int z = 1000000000;
    int x = N;
    while(l < r) {
        m = (l+r)/2;
        average = m;
        visited.clear();
        visited.resize(N, false);
        int g = rec(0);
        if(g == -1){
            l = m;
            continue;
        }
        if(g == z && x > m) x = m;
        else if(g < z) {
            z = g;
            x = m;
        }
        r = m;
    }
    if(t == 1) x = N;
    return {t,x};
}



int readInt(){
	int i;
	if(scanf("%d",&i)!=1){
		fprintf(stderr,"Error while reading input\n");
		exit(1);
	}
	return i;
}

int main(){
	 std::ios_base::sync_with_stdio(0);
    int N;
    N = readInt();
    vector<int> A(N-1);
	vector<int> B(N-1);

    for (int i = 0; i < N-1; ++i) {
	scanf("%d %d", &A[i], &B[i]);
    }

    pair<int, int> ans = LightItUp(N, A, B);
    printf("%d %d\n", ans.first, ans.second);
    return 0;
	
}
