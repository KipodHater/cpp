#include<bits/stdc++.h>
using namespace std;
typedef int ll;
typedef vector<int> vl;

std::vector<int>find_cool_numbers(int X){
    vl c;
    for(ll i=2; i<X/2; i++) {
        // find how big
        ll r;
        for(r=1; r<X; r*=i);
        r/=i;
        ll l = 1;
        bool flag = false;
        bool d = false;
        while(r > l) {
            ll a = (X/l) % (i);
            ll b = (X % (r*i)) / r;
            if(a != 0) d = true;
            if(b != 0) d = true;
            if(a != b) {
                flag = true;
                break;
            }
            l *= i;
            r /= i;
        }
        if(flag || !d) continue;
        c.push_back(i);
    }
    c.push_back(X-1);
	return c;
}

// int main()
// {
// 	std::ios::sync_with_stdio(0);
// 	std::cin.tie(0);
// 	int X;
// 	std::cin>>X;
// 	auto t=find_cool_numbers(X);
// 	for(int i:t)std::cout<<i<<"\n";
// 	return 0;
// }