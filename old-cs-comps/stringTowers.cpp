#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<long long> vll;

stack<pair<char, char>> s;

void build(string &st, int n){
    char m = st.at(0);
    for(ll i=0; i<n; i++){
        m = min(st.at(i), m);
        s.push({st.at(i), m});
    }
}
char deleteMax(){
    stack<pair<char, char>> b;
    char c = s.top().second;
    char d = c;
    while(d != s.top().first){
        b.push(s.top());
        s.pop();
    }
    s.pop();
    if(s.size()){
        c = s.top().second;
    } else c = 'z';

    while(!b.empty()){
        c = min(c, b.top().first);
        s.push({b.top().first, c});
        b.pop();
    }
    return d;
}

pair<bool, string> prettiest_tower(int N, string cubes){
    build(cubes, N);
    string rami, dani;

    while(!s.empty()){
        rami.push_back(s.top().first);
        s.pop();
        dani.push_back(deleteMax());
    }
    for(int i = 0; i<N/2; i++){
        if(dani.at(i) < rami.at(i)) return {true, dani};
        if(dani.at(i) > rami.at(i)) return {false, dani};
    }
    return {false, dani};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    string cubes;
    cin >> n >> cubes;

    pair<bool, string> ans = prettiest_tower(n, cubes);
    if (ans.first) cout << "True" << endl;
    else cout << "False" << endl;

    cout << ans.second;
    return 0;
}