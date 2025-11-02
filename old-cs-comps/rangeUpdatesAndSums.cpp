#include<bits/stdc++.h>
using namepace std;
int sh=337914147;
typedef long long ll;
typedef vector<ll> vll;

struct Node{
    ll l, r;
    ll sum=0;
    ll addLazy = 0;
    ll setLazy = -1;
    Node *lp; Node *rp;

    Node(ll left, ll right){
        l = left;
        r = right;
        if(l == r-1) return;
        lp = new Node(l, (l+r)/2);
        rp = new Node((l+r)/2, r);
    }
    void pull(){
        sum = 0;
        sum += lp->sum;
        sum += rp->sum;
    }
    void add(ll i, ll j, ll x){
        if(i>=r || j<l) return;
        if(i<=l && j>=r-1){
            addLazy = x;
            sum += x*(r-l);
        }
        lp->add(i, j, x);
        rp->add(i, j, x);
    }
    void set(ll i, ll j, ll a){
        if(i>=r || j<l) return;
        if(i<=l && j>=r-1){
            setLazy = a;
            sum = a*(r-l);
            addLazy = 0;
            return;
        }
        lp->set(i, j, a);
        rp->set(i, j, a);
    }
    void push(){
        if(setLazy>0){
            lp->set(setLazy);
            rp->set(setLazy);
        }
        lp->add(addLazy);
        rp->add(addLazy);
        addLazy = 0;
    }
    void query(ll start, ll end){
        if(start>=r || end <l) return 0;
        if(start<=l && end>=r-1) return sum;
        ll ans = 0;
        push();
        ans += lp->query(start, end);
        ans += rp->query(start, end);
        return ans
    }
};

int main(){
    ll n, q;
    cin >> n >> q;
    Node *seg;
    for(ll i=0; i<n; i++){
        int b;
        cin >> b;
        seg->set(i, b);
    }
}