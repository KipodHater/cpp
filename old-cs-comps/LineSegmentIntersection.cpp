#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll sgn(ll n){
    return n<0? -1 : (n?1:0);
}
ll vec(ll x1, ll y1, ll x2, ll y2){
    return sgn((x1*y2) - (x2*y1));
}
bool points(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3){
    if(x1 != x2){
        return (x3>= x1&& x3 <= x2) || (x3<=x1 && x3>=x2);
    } else if(x1 == x2 && x1 == x3){
            return (y3>= y1&& y3 <= y2) || (y3<=y1 && y3>=y2);
    } else return false;
}
int main(){
    ll n;
    cin >> n;
    while(n--){
        ll x1, y1, x2, y2, x3, y3, x4, y4;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
        ll sgn1, sgn2, sgn3, sgn4;
        sgn1 = vec(x1 - x2, y1 - y2, x3 - x2, y3 - y2);
        sgn2 = vec(x1 - x2, y1 - y2, x4 - x2, y4 - y2);
        sgn3 = vec(x3 - x4, y3 - y4, x2 - x4, y2 - y4);
        sgn4 = vec(x3 - x4, y3 - y4, x1 - x4, y1 - y4);
        // if((sgn1* sgn2>0 || sgn3* sgn4>0)){
        //     cout << "NO\n";
        // } else if(sgn1 || sgn2 || sgn3 || sgn4){
        //     cout << "YES\n";
        if(sgn1 == 0 &&points(x1, y1, x2, y2, x3, y3)){
           cout << "YES\n"; continue;
                // else cout << "NO\n";
        } else if(sgn2 == 0 && points(x1, y1, x2, y2, x4, y4)){
            cout << "YES\n"; continue;
            // else cout << "NO\n";
        } else if(sgn3 == 0 && points(x3, y3, x4, y4, x2, y2)){
            cout << "YES\n"; continue;
                            // else cout << "NO\n";
            }else if(sgn4 == 0 && points(x3, y3, x4, y4, x1, y1)){
            cout << "YES\n"; continue;
                // else cout << "NO\n";
            }
            else if(sgn1*sgn2<0 && sgn3*sgn4<0){ cout << "YES\n"; continue;}
            cout << "NO\n";
                }
    }