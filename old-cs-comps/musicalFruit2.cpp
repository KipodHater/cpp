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
    vector<ll> b(26);
    b = a;
    vector<bool> c(n, true);
    for(ll i=0; i<n; i++) {
        a[s.at(i)-97]++;
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
    for(ll i=0; i<n; i++){
        k = 0;
        m = 0;
        for(ll j=0; j<26; j++){
            if((m < a[j] || (b[j] > b[k] && m == a[j])) && s.at(i)!= j+97){
                m = a[j];
                k = j;
            }
        }
        ans.at(i) = k+97; 
        a[k]--;
    }

    cout << ans;
}