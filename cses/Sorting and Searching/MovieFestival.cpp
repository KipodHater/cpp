#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    ll n; cin >> n;
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> q;
    for(ll i=0; i<n; i++){
        ll a,b; cin >> a >> b;
        q.push({b, a});
    }
    ll c=1;
    pair<ll, ll> last = q.top();
    q.pop();
    while(!q.empty()){
        pair<ll, ll> top = q.top();
        q.pop();
        if(top.second >= last.first){
            last = top;
            c++;
        }
    }
    cout << c;
}