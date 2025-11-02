#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;

int main(){
    ll n, y;
    cin >> n;
    y = n;
    string s;
    cin >> s;
    vll a (26, 0);
    vector<queue<ll>> b(26);
    vector<bool> c(n, true);
    for(ll i=0; i<n; i++) {
        a[s.at(i)-97]++;
        b[s.at(i)-97].push(i);
    }
    for(ll u: a){
        if(u > n/2){
            cout << "no";
            return 0;
        }
    }
    ll m, k;
    m= 0;
    k=0;
    string ans = "";
    for(ll i=0; i<n; i++){
        ans.push_back(1);
    }
    for(ll j=0; j<26; j++){
        if(a[j] > m){
            m = a[j];
            k = j;
        }
    }
    ll last = k;
    ll ind = b[k].front();
    b[k].pop();
    for(ll i=0; i<n-1; i++){
        m = 0;
        k = -1;
        for(ll j=0; j<26; j++){
            if((b[j].size() > m || (0<b[j].size() && ind == j)) && j!= last ){
                m = b[j].size();
                k = j;
            }
        }
        if(0<b[ind].size() && ind!= last){
            m= b[ind].size();
            k = ind;
        }
        ans.at(b[k].front()) = last+97;
        b[k].pop();
        last = k;
    }
    ans.at(ind) = last+97;
    cout << ans;
}