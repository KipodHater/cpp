#include<bits/stdc++.h>
using namespace std;
typedef long long ll;


int main(){
    ll n;
    cin >> n;

    vector<int> visited(n + 1, 0);
    stack<pair<ll, ll>> b;

    vector<ll> a(n);
    for(ll i=0;i<n;i++){
        cin >> a[i];
    }
    for(ll i=n-1; i>=0; i--){
        visited[a[i]]++;
        if(visited[a[i]] == 2){
            b.push({i, a[i]});
        }
    }
    
    set<ll> s;
    ll res = 0;
    for(ll i=0; i<n && !b.empty(); i++){
        if(b.top().first == i){
            res+= s.size();
            if(s.count(b.top().second) == 1) res--;
            b.pop();
        }
        s.insert(a[i]);
    }

    cout << res;
}