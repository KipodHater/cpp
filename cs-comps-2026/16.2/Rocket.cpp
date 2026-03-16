#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e10;

// std::vector<std::array<int, 3>> replacements;
// int start_batteries[6];

// void init(int batteries[6]) {
// 	std::copy(batteries, batteries + 6, start_batteries);
// }

// void replace(int time, int old_battery, int new_battery) {
// 	replacements.push_back({ time, old_battery, new_battery });
// }

void init(int batteries[6]);
void replace(int time, int old_battery, int new_battery);


long long rocket_engine(int t, int n, std::vector<std::pair<int, int>> batteries) {
    ll x = 0;
    ll a = 0;

    priority_queue<pair<pair<ll, ll>, int>> q;
    for(ll i=0; i<n; i++) q.push({batteries[i], i});
    vector<pair<pair<ll, ll>, int>> b(6);
    for(ll i=0; i<6; i++) {
        b[i] = q.top();
        q.pop();
    }
    int c[6] = {b[0].second, b[1].second, b[2].second, b[3].second, b[4].second, b[5].second};
    init(c);
    
    while(a<t) {
        ll e = t;
        ll sum = 0;
        for(ll i=0; i<6; i++) {
            sum += b[i].first.first;
            if(b[i].first.second <= e) {
                e = b[i].first.second;
            }
        }
        e = min(e, t-a);
        for(ll i=0; i<6; i++) {
            b[i].first.second -= e;
        }
        if(e<0) 1/0;
        x += e * sum;
        a += e;

        if(a < t)
        for(ll i=0; i<6; i++) {
            if(b[i].first.second <= 0) {
                replace(a, b[i].second, q.top().second);
                b[i] = q.top();
                q.pop();
            }
        }
    }

    return x;
}



// int main() {
// 	std::ios_base::sync_with_stdio(false);
// 	std::cin.tie(NULL);

// 	int t, n;
// 	std::cin >> t >> n;
// 	std::vector<std::pair<int, int>> batteries(n);
// 	for (auto& b : batteries) 
// 		std::cin >> b.first >> b.second;
// 	long long dist = rocket_engine(t, n, std::move(batteries));

// 	std::cout << "start with these batteries: ";
// 	for (int i = 0; i < 5; i++) std::cout << start_batteries[i] << ' ';
// 	std::cout << start_batteries[5] << '\n';

// 	std::cout << "make " << replacements.size() << " replacements:\n";
// 	for (auto& rep : replacements) {
// 		std::cout << "at time " << rep[0] << " remove battery " << rep[1] << " and insert battery " << rep[2] << '\n';
// 	}

// 	std::cout << "total distance traveled is " << dist << '\n';
	
// 	return 0;
// }