#include <bits/stdc++.h>
using namespace std;

int MinKnocks(int R, int M, std::vector<int> A, std::vector<int> B){
    vector<vector<int>> d(R, vector<int>(0));
    vector<vector<int>> e(R, vector<int>(0));

    for(int i=0; i<M; i++) {
        d[A[i]].push_back(B[i]);
        e[B[i]].push_back(A[i]);
    }

    int c = 0;
	vector<bool> visited(R, false);
    for(int i = 0; i<R; i++) {
        if(visited[i]) continue;

        stack<int> s;
        s.push(i);
        c++;
        while(!s.empty()) {
            int last = s.top();
            s.pop();
            visited[last] = true;
            for(int u : d[last]) {
                if(!visited[u]) s.push(u);
            }
            bool f = false;
            for(int u : e[last]) {
                if(!visited[u]) {
                    if(f) c++;
                    
                    s.push(u);
                }
            }
        }
    }
}

int main(){
	ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
	int T;
	cin >> T;
	while(T--){
		int R,M;
		cin>>R>>M;
		
		vector<int> A(M);
		vector<int> B(M);
		for (int i = 0; i < M; i++) {
			cin >> A[i] >> B[i]; 
		}	
		cout<<MinKnocks(R, M, A, B)<<"\n";
	}
	return 0;
}
