#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll sgn(ll n){ return n<0 ? -1 : (n?1:0); }
ll vec(ll x1, ll y1, ll x2, ll y2){
    return (x1 * y2) - (x2 * y1);
}
int main(){
    ll n;
    cin >> n;
    for(ll i=0; i<n; i++){
        int x1, x2, x3, y1, y2, y3;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        ll res = vec(x3 - x1, y3 - y1, x2 - x1, y2 - y1);
        if(res == 0) cout << "TOUCH\n";
        else if(res<0) cout << "LEFT\n";
        else cout << "RIGHT\n";
    }
}