#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;
const ll INF = 1e18;

vll v;
struct Node
{
    ll r, l, m;
    ll minimum = INF;
    Node *lp = nullptr;
    Node *rp = nullptr;

    Node(ll left, ll right)
    {
        l = left;
        r = right ;
        m = (l + r) / 2;
        if (l == r-1)
            return;
        else
        {
            lp = new Node(l, m);
            rp = new Node(m, r);
        }
    }
    void update(ll k, ll u)
    {
        if (k < l || k >= r)
            return;
        if (k == l && k == r - 1)
        {
            minimum = u;
            return;
        }
        lp->update(k, u);
        rp->update(k, u);
        
        pull();
    }
    void pull()
    {
        minimum = min(lp->minimum, rp->minimum);
    }
    ll query(ll tl, ll tr)
    {
        if (tl >= r || tr < l)
            return INF;
        if (tl <= l && tr >= r - 1)
            return minimum;
        return min(lp->query(tl, tr), rp->query(tl, tr));
    }
};

int main()
{
    ll n, q, b, c, d;
    cin >> n >> q;
    v.resize(n);
    Node *seg;
    seg = new Node(0, n);
    for (ll i = 0; i < n; i++){
        cin >> v[i];
        seg->update(i, v[i]);
    }

    

    for (ll i = 0; i < q; i++)
    {
        cin >> b >> c >> d;
        if (b == 2)
            cout << seg->query(c-1, d-1) << endl;
        else if (b == 1)
            seg->update(c-1, d);
    }
}