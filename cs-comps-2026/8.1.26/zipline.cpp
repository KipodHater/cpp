#include<bits/stdc++.h>
using namespace std;


struct comp{
bool operator()(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) const {
    // calculat the slope

}
}

std::pair<int, int> safest_zipline(int N, std::vector<std::pair<int, int>> T) {
    set<pair<pair<int, int>, int>, customOperator>
    return {-1, -1};
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N;
    std::cin >> N;
    std::vector<std::pair<int, int>> T(N);
    for (int i = 0; i < N; ++i) {
        int d, h;
        std::cin >> d >> h;
        T[i] = {d, h};
    }

    std::pair<int, int> result = safest_zipline(N, T);
    std::cout << result.first << " " << result.second << "\n";

    return 0;
}