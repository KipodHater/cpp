#include "bananas.h"
#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int T, N;
    std::cin >> T;
    while (T--) {
        std::cin >> N;
        std::cout << Bananas(N) << '\n';
    }
    return 0;
}