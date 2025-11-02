#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> a;

struct Seg{
    bool init;
    ll val, r, l, m;
    Seg* rp = nullptr;
    Seg* lp = nullptr;

    Seg(ll left, ll right){
        l = left;
        r = right;
        m = (l+r)/2;
        init = true;
        if(l == r-1) val = a[l];
        else init = false;
    }

    void expand(){
        rp = new Seg(m, r);
        lp = new Seg(l, m);
    }

    void pull(){
        if
    }

    void update()
}


int main(){

}