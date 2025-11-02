#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> B;
int l;
void reverse(int i, vector<int>& res) {
    res.push_back(i);
    for(int j = 0; j<B.size(); j++) {
        if(B[j] >= i && B[j] < i + l) B[j] = i + l - 1 - (B[j] - i);
    }
}

int makeRangeWithReverses(int N, int L, vector<int> A, vector<int>& res) {
    sort(A.begin(),A.end());
    B = A;
    l = L;
    int target = A[0]+1;
    int e = 1;
    if(L%2){
        ll odd = 0;
        for(ll i : A) odd += i%2;
        if(abs(N-2*odd) >= 2) return -1;
        // int target = 0;
        bool c = odd > N - odd;
        int d = 0;
        while((2*odd != N) && A[d] % 2 == (c ? 0:1)) d++;
        target = A[d]+1;
    if(d != 0) {
        target -= l-1;
        reverse(target-1, res);
        while(target-1 > 0) {
            target -= l-1;
            reverse(target-1, res);
            
        }
    }
    }
    int goal = target + L - 1;
    while(e<N) {
        // find next thing
        int cur;
        for(ll u:B) {
            if(u>target-1){
                if(L%2 == 0 || u%2 == (target)%2) {
                    cur = u;
                    break;
                }
            }
        }
        // go to goal
        while(cur >= goal + 1) {
            cur -= L - 1;
            reverse(cur, res);
        }
        while(cur != goal && cur < goal + 1) {
            // swap here to right place can take two steps
            if(L%2 == 0 && cur % 2 == goal % 2){
                reverse(target, res);
                cur = target + l - 1 - (cur - target);
            }
            else {
                reverse((cur + goal)/2 - L/2 + 1 - L%2, res);
                cur = goal;
            }
        }
        // go to the right place
        cur -= L-1;
        reverse(cur, res);

        target = cur + 1;
        goal = target + L - 1;
        e++;
    }
	return res.size();
}

// int main() {
// 	int N, L;
// 	scanf("%d%d", &N, &L);

// 	vector<int> A(N);
// 	for (int i = 0; i < N; i++) scanf("%d", &A[i]);

// 	vector<int> res;
// 	int ans = makeRangeWithReverses(N, L, A, res);

// 	printf("%d\n", ans);
// 	if (ans != -1) {
// 		for (int i : res) printf("%d ", i);
// 	}
// }