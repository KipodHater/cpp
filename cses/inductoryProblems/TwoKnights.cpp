#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ll sum = 6;
    ll k;
    cin >> k;
    if(k>0) 
    cout << 0 << "\n";

    for(ll i=2; i<=k; i++){
        cout << i*i*(i*i-1) /2- 4 * (i-2) * (i-1) << "\n";
    }
}