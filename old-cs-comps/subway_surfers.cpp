#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    string s;
    cin >> s;
    ll n = s.size();
    vector<pair<ll, ll>> a (n+1);
    a[0].first = 0;
    a[0].second = 1;

    for(ll i=1; i<n+1; i++){
        if(s.at(i-1) == 'L'){
            a[i].second = a[i-1].second;
            a[i].first = min(a[i-1].first+1, a[i].second+1);
            a[i].second = min(a[i].first+1, a[i].second);
        } else if(s.at(i-1) == 'R'){
            a[i].first = a[i-1].first;
            a[i].second = min(a[i-1].second+1, a[i].first+1);
            a[i].first = min(a[i].second+1, a[i].first);
        } else{
            a[i].first = a[i-1].first+1;
            a[i].second = a[i-1].second+1;
            a[i].first = min(a[i].first, a[i].second+1);
            a[i].second = min(a[i].first+1, a[i].second);
        }
    }

    cout << a[n].first;
}