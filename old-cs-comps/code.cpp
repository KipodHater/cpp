#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll MOD = 1e9 + 7;
const ll INF = 1e10;
using vll = vector<ll>;

vector<stack<int>> a;
vector<int> c;
int q;

int dfsLca(int e, int f){
    vector<bool> visited(q+1, false);
    stack<int> s;
    s.push(e);
    while(s.size()){
        int last = s.top();
        s.pop();
        visited[last] = true;
        if(c[last] != -1){
            s.push(c[last]);
        }
    }
    s.push(f);
    while(s.size()){
        int last = s.top(); s.pop();
        if(visited[last]){
            return last;
            break;
        } else{
            if(c[last] != -1){
                s.push(c[last]);
            }
        }
    }
    return -1;

}
void init(int Q){
    // TODO: implement this function
    a.resize(Q+1);
    c.resize(Q+1, -1);
    c[0] = -1;
    q = Q;
}

void Add_gene(int i, int x){
    // TODO: implement this function
    a[i] = a[x];
    a[i].push(i);
    c[i] = x;
}

int Remove_gene(int i, int x){
    // TODO: implement this function
    a[i] = a[x];
    int g = a[i].top();
    a[i].pop();
    c[i] = c[x];
    return g;
}


int Count_genes(int i, int x, int y){
    // TODO: implement this function
    a[i] = a[x];
    c[i] = x;
    // multiset<ll> s;
    int res = a[dfsLca(y, x)].size();
    return res;
}



int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int Q;
    cin >> Q;
    init(Q);
    for (int i = 1; i <= Q; i++){
        int x, y;
        char _type;
        cin >> _type >> x;
        if (_type == 'a'){
            Add_gene(i, x);
        } else if (_type == 'r'){
            cout << Remove_gene(i, x) << "\n";
        } else {
            cin >> y;
            cout << Count_genes(i, x, y) << "\n";
        }
    }
    return 0;
}
