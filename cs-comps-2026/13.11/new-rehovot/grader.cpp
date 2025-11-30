#include <iostream>
#include <vector>
#include "new_rehovot.h"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, Q;
    std::cin >> N >> Q;
    std::vector<int> H(N);
    for (int i = 0; i < N; i++) {
        std::cin >> H[i];
    }

    init(N, Q, H);

    for (int i = 0; i < Q; i++) {
        int L, R;
        std::cin >> L >> R;
        std::cout << build_new_rehovot(L, R) << "\n";
    }

    return 0;
}
