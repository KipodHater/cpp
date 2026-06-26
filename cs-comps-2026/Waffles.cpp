#include<bits/stdc++.h>
using namespace std;


int main() {
    srand(85); // time(0)
    int r = rand();
    if (r >= (2147483647 / 50) * 3) cout << 5;
    else cout << "Waffles";
}