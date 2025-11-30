#include "concert.h"
#include <vector>
#include <array>
#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(NULL);
    int A,B,C,D;
    std::cin >> A >> B >> C >> D;
    std::vector<int> X(D), Y(D);
    for (int i=0; i<D; i++){
        std::cin >> X[i] >> Y[i];
    }
    auto [a, b, c] = Concert(A, B, C, D,std::move(X), std::move(Y));

    std::cout << a << "\n" << b << "\n" << c << "\n";
    return 0;
}
