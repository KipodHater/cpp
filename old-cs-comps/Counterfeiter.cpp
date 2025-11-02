#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e10;
ll sum;
vector<string> a, b;

void fillWith(ll x1, ll x2, ll y1, ll y2, char n){
    for(ll i1=x1; i1<= x2; i1++){
        for(ll j1 = y1; j1 <= y2; j1++){
            b[i1].at(j1) = n;
        }
    }
}

pair<ll, pair<ll, ll>> calc(ll i1, ll i2, ll j1, ll j2){
    if(i1 == i2){
        ll z;
        if(a[i1].at(j1) == '0') z = 0;
        else z = 1;
        return {0, {1 - z, z}};
    }
    pair<ll, pair<ll, ll>> m;
    ll d = INF;
    ll I, J;
    pair<ll, ll> w;

    pair<ll, pair<ll, ll>> a1, a2, a3, a0;
    a0 = calc(i1, (i1+i2)/2, j1, (j1+j2)/2);
    a1 = calc((i1+i2)/2 + 1, i2, j1, (j1+j2)/2);
    a2 = calc((i1+i2)/2 + 1, i2, (j1+j2)/2 + 1, j2);
    a3 = calc(i1, (i1+i2)/2, (j1+j2)/2 + 1, j2);
    vector<pair<ll, pair<ll, ll>>> g = {a0, a1, a2, a3};
    ll e = a0.second.first + a0.second.second;
    for(ll i=0; i<4; i++){
        for(ll j=0; j<4; j++){
            if(j == i) continue;
            set<ll> f = {0, 1, 2, 3};
            ll temp = 0;

            f.erase(i);
            f.erase(j);

            temp += e - g[i].second.first;
            temp += e - g[j].second.second;

            ll zeros = a0.second.first + a1.second.first + a2.second.first + a3.second.first;
            ll ones = a0.second.second + a1.second.second + a2.second.second + a3.second.second;
            
            for(ll u: f) temp += g[u].first;

            if(temp < d){
                d = temp;
                m = {temp, {zeros, ones}};
                w = {i, j};
            }
        }
    }
    switch(w.first){
        case 0: fillWith(i1, (i1+i2)/2, j1, (j1+j2)/2, '0'); break;
        case 1: fillWith((i1+i2)/2 + 1, i2, j1, (j1+j2)/2, '0'); break;
        case 2: fillWith((i1+i2)/2 + 1, i2, (j1+j2)/2 + 1, j2, '0'); break;
        case 3: fillWith(i1, (i1+i2)/2, (j1+j2)/2 + 1, j2, '0'); break;
    }
    switch(w.second){
        case 0: fillWith(i1, (i1+i2)/2, j1, (j1+j2)/2, '1'); break;
        case 1: fillWith((i1+i2)/2 + 1, i2, j1, (j1+j2)/2, '1'); break;
        case 2: fillWith((i1+i2)/2 + 1, i2, (j1+j2)/2 + 1, j2, '1'); break;
        case 3: fillWith(i1, (i1+i2)/2, (j1+j2)/2 + 1, j2, '1'); break;
    }
    return m;
}

std::vector<std::string> fake(int N, std::vector<std::string> A) {
    a = A;
    b = A;

    pair<ll, pair<ll, ll>> r = calc(0, A.size()-1, 0, A.size()-1);
    return b;
}

// int main(){
//     ios_base::sync_with_stdio(false); cin.tie(0);
//     int N;
//     cin >> N;
//     vector<string> A(N);
//     for (auto &s : A) {
//         cin >> s;
//     }
//     auto B = fake(N, A);
//     for (auto &s : B) {
//         cout << s << '\n';
//     }
//     return 0;
// }