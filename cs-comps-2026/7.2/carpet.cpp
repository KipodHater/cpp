#include<bits/stdc++.h>
using namespace std;

struct Node {
    int x = 0;
    int l, r, m;
    Node *lp = nullptr;
    Node *rp = nullptr;

    Node(int l, int r):l(l),r(r) {
        m = (l+r) / 2;
        if(l == r-1) return ;
        lp = new Node(l, m);
        rp = new Node(m, r);
    }

    void pull() {
        
    }
};

int place_carpets(int N, int M, int D, std::vector<int> X, std::vector<int> V) {
    // TODO: implement this function.
    return 0;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M, D;
    std::cin >> N >> M >> D;
    std::vector<int> X(N), V(N);
    for (int i = 0; i < N; i++) {
        std::cin >> X[i] >> V[i];
    }

    int result = place_carpets(N, M, D, X, V);
    std::cout << result << "\n";
    return 0;
}
