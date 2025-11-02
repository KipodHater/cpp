#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ll t;
    cin >> t;
    while(t--){
        ll x, y;
        cin >> y >> x;

        ll sum =0;
        sum += max(x-1, y-1) * max(x-1, y -1);

        if(x == y) sum += x;
        else if(x>y){
            if(x%2) sum += 2*x-y;
            else sum += y;
        } else{
            if(y%2-1) sum += 2*y - x;
            else sum += x;
        }
        cout << sum << "\n";
    }
}