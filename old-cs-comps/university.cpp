#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;

vector<int> University(int N, vector<pair<int, int>> G)
{
    vector<int> res(N, 0);
    vector<pair<int, int>> b(N);
    for (int i = 0; i < N; i++)
    {
        b[i].first = G[i].first;
        b[i].second = i;
    }
    sort(b.begin(), b.end());

    ll last = 0;
    for (int i = 0; i < N; i++)
    {
        if (G[b[i].second].second > last)
        {
            if (last <= G[b[i].second].first)
            {
                res[b[i].second] = G[b[i].second].second - G[b[i].second].first;
                last = G[b[i].second].second;
            }
            else
            {
                res[b[i].second] = G[b[i].second].second - last;
                last = G[b[i].second].second;
            }
        }
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N;
    cin >> N;
    vector<pair<int, int>> G(N);
    for (int i = 0; i < N; i++)
    {
        cin >> G[i].first >> G[i].second;
    }
    vector<int> ret = University(N, move(G));
    for (int i = 0; i < N; i++)
    {
        cout << ret[i] << "\n";
    }
    return 0;
}