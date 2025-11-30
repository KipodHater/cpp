#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ofstream file("C:\\Users\\doodi\\Documents\\Code(drip)\\cpp\\cs-comps-2026\\30.11\\celebration.txt");
int main() {
    for(ll i=0; i<5000; i++) file << "U";
    file << "R";
    for(ll i = 2; i<10001; i++) {
        for(ll j = 1; j<10000/i; j++) {
            file << "U";
        }
        file << "R";
    }
}