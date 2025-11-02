#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    string s; cin >> s;
    vector<ll> hysto(26, 0);
    for(ll i=0; i<s.size;i++) hysto[s.at(i)-97]++;

    ll flag = 0;
    for(ll i:hysto) {
        if(i%2) flag++;
    }
}