#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ll t;
    cin >> t;
    for (ll k = 0; k < t; k++)
    {
        ll m = 0;
        ll n;
        cin >> n;
        vector<ll> a;
        priority_queue<ll> q;
        for(ll i=0;i<n; i++){
            cin >> a[i];
            q.push(a[i]);
        }
        vector<vector<ll>> b(n, vector<ll>);
        vector<vector<ll>> c(n, vector<ll>);
        vector<vector<ll>> d(n, vector<ll>);

        b[n-1].push_back(a[n-1]);
        c[n-1].push_back(a[n-1]);
        // d[n-1].push_back(a[n-1]);
        m = a[n-1];

        for(ll i=n-2; i>=0; i--){
            if(a[i] >= m){
                d[i] = a[i+1];
                m = a[i];
            } else{
                if(a[i] > d[i+1].front()){
                    d[i] = d[i+1];
                    d[i].push_back(a[i]);
                } else{
                    d[i] = d[i+1];
                }
            }

            c[i] = b[i+1];
            c[i].push_back(a[i]);
            
            if(a[i] < d[i+1].front()){
                b[i] = b[i+1];
            } else{
                b[i] = b[i+1];
                b[i].push_back(a[i]);
            }


        }
    }
}