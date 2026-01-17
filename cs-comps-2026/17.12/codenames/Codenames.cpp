#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;

long long be_ronit(int N, int K, int C, int D, std::vector<int> A, std::vector<int> B){
    vl c;
    ll d = 0;
    d = B[B.size()-1] - A[0];
    d *= D;
    ll lastNum = 0;
    ll lastSum = 0;
    // d -=C;
    for(ll i=1; i<N; i++) {
        c.push_back(A[i] - B[i-1]);
    }
    sort(c.begin(), c.end());
    bool used = false;
    bool flag = false;
    while(c.size() >= K) {
        ll f = 0;
        ll r = c.size();
        ll l = r-K;
        for(ll i=l; i<r; i++) f += c[i];
        if(f*D > C) {
            d -= f*D - C;
            lastSum = f;
            lastNum = c[l];
            used = true;
        }
        else {
            flag = true;
            break;
        }
        for(ll i=l; i<r; i++) c.pop_back();
    }
    // if(c.size() == 0 || flag) d += C;// do something
    ll g = 0;
    ll r, l;
    if(!flag) {
        l = 0;
        r = c.size();
        // ll g = 0;
        // for(ll i=0; i<c.size(); i++) g += c[i];
        // used = true;
        // d -= g*D;
    } else {
        // ll f = 0;
        r = c.size();
        l = r-K + 1;
        // for(ll i=l; i<r; i++) f += c[i];
        // for(ll i=l; i<r; i++) c.pop_back();
        // if(f*D > C) {
        //     d -= f*D;
        //     used = true;
        // }
    }
    for(ll i=l; i<r; i++) g += c[i];
    if(used)
        if((lastSum) * D - C + g * D > (lastSum-lastNum) * D) {
            d -= g*D;
        } else d += (lastSum) * D - C - (lastSum-lastNum) * D;
    else d -= g*D;
    return d;
}
// int main(){
//     ios_base::sync_with_stdio(false);cin.tie(NULL);

//     int N,K,C,D;
//     cin >> N >> K >> C >> D;
//     vector<int> A(N), B(N);
//     for (int i=0;i<N;i++){
//         cin >> A[i] >> B[i];
//     }
//     cout << be_ronit(N,K,C,D,move(A),move(B)) << "\n";
// }