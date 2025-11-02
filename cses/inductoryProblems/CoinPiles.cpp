#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ll k; cin >> k;
    while(k--){
        ll a,b; cin >> a >> b;
        if((a+b)%3 == 0 && (a+b)/3 <= a && (a+b)/3 <= b) cout << "YES\n";
        else cout << "NO\n";
    }
}