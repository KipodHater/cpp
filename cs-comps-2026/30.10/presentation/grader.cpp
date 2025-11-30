#include "presentation.h"
#include <iostream>
#include <vector>

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

	int N;
	std::cin >> N;
	std::vector<std::pair<int, int>>V(N);
	for (auto& p : V) std::cin >> p.first >> p.second;

	std::cout << presentation(N, std::move(V));

	return 0;
}