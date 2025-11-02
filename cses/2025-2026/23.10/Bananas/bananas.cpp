#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int Bananas(int N){
    int m = log10(N) + 1;
    int y = m+2;
    vector<int> a(y, 0);
    int b = 0;
    int n = N;
    int h = N%10;
    vector<int> g(10);
    if(N%2 == 0 || N%5 == 0) return -1;
    for(ll i=0; i<10; i++) for(ll j=0; j<10; j++) if((h * j % 10) == i) g[i] = j;
    int res = 0;
    bool c = true;
    while(c) {
        int d = g[(11 - a[b]) % 10];
        // times
        int e = (d * N + a[b]) / 10;
        a[b] = 0;
        b = (b+1) % (y);
        res++;
        
        int f = b;
        while(e > 0) {
            a[f] += e%10;
            e /= 10;
            if(a[f] > 9) {
                int tens = a[f]/10;
                a[f] = a[f] %10;
                a[((f+1) % (y))] += tens;
            }
            f = (f+1) % (y);
        }
        if(a[f] > 9) {
            int tens = a[f]/10;
            a[f] = a[f] %10;
            a[((f+1) % (y))] += tens;
        }
        // if(a[(f+1) % (y)] > 9) {
        //         int tens = a[(f+1) % (y)]/10;
        //         a[(f+1) % (y)] = a[(f+1) % (y)] %10;
        //         a[((f+2) % (y))] += tens;
        //     }

        // f = b;
        // c = false;
        // bool x = false;
        // for(int i=0; i<y; i++) {
        //     if(a[f] != 1 && a[f] != 0) c = true;
        //     else if(a[f] == 0) x = true;

        //     if(x && a[f] != 0) c = true;
        //     f = (f+1) % (y);
        // }
        c = false;
        for(int i : a) if(i!= 0) c = true;
    }
    // int counter = 0;
    // for(int i = (y+b-1) % (y); i!=b; i = (y+i-1) % (y)) {
    //     if(a[i] == 0) counter++;
    // }
    return res;
    //  + m + 2 - counter;
}

// int main() {
//     std::ios_base::sync_with_stdio(false);
//     std::cin.tie(NULL);
//     int T, N;
//     std::cin >> T;
//     while (T--) {
//         std::cin >> N;
//         std::cout << Bananas(N) << '\n';
//     }
//     return 0;
// }