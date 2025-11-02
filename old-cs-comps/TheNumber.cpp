#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

long long Decipher(int N, std::vector<int> V){
	multiset<ll> s;

    ll a[N];
    ll b[N];
    // vector<ll> b(N, 0);

    for(ll i=0; i<N; i++){
        s.insert(V[i]);
        a[i] = distance(s.find(V[i]), s.end()) - s.count(V[i]);
    }
    s.clear();
    for(ll i=N-1; i>=0; i--){
        s.insert(V[i]);
        b[i] = distance(s.begin(), s.find(V[i]));
    }
    ll sum =0;
    for(ll i=0; i<N; i++){
        sum += a[i]*b[i];
    }
    return sum;
}

// int main(){
//     std::ios_base::sync_with_stdio(false); std::cin.tie(NULL);
//     int N;
//     std::cin >> N;

//     std::vector<int> V(N);

//     for (int i = 0; i < N; i++) {
//         std::cin >> V[i];
//     }

//     std::cout<< Decipher(N, V) <<"\n";

//     return 0;
// }