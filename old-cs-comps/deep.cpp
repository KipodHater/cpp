#include<bits/stdc++.h>
using namespace std;

vector<vector<double>> dp;
vector<vector<int>> dpVisits;
vector<vector<bool>> ex;
vector<double> ans;
int k, firstR;
bool streak = true;

void updateRes(vector<double> &matrix, int dpi, int offset, int curIndex, double dist, double minus, double startingLoc) {
    for(int i = 0; i < k; i++) {
        int indexForDP = (i + offset + k) % k;
        dp[curIndex][indexForDP] = matrix[indexForDP] + dp[dpi][i] + 1.0 * dpVisits[dpi][i] * (dist / 2 - minus);
        dpVisits[curIndex][indexForDP] += dpVisits[dpi][i];
        
        if(ex[dpi][i]) {
            if(streak) {
                dp[curIndex][indexForDP] += dist;
            } else {
                dp[curIndex][indexForDP] += (dist)/2.0;
            }
            ex[curIndex][indexForDP] = true;
        }
        
        ans[indexForDP] += dp[curIndex][indexForDP];
    }
}

std::vector<double> blindfolded(int N, int K, int L, std::vector<int> P, std::vector<int> G, std::vector<char> D) {
    k = K;
    dp.resize(N, vector<double>(K, 0));
    ans.resize(k, 0);
    dpVisits.resize(N, vector<int>(K, 0));
    ex.resize(N, vector<bool>(K, false));
    firstR = -1;

    for(int i = 0; i < N; i++) {
        if(D[i] == 'R') {
            ans[G[i]] += L - P[i];
            streak = false;
            if(firstR < 0) firstR = i;
        } else if(D[i] == 'L') {
            int curTeam = G[i];
            vector<double> resMatrix(K, 0);
            int j = i - 1;
            bool cont = true;
            double curLocation = P[i];
            
            if(j >= 0) {
                while(cont && j >= 0) {
                    if(D[j] == 'R') {
                        resMatrix[curTeam] += (curLocation - P[j]) / 2.0;
                        dpVisits[i][curTeam] += 1;
                        curTeam = (G[j] + curTeam) % K;
                        curLocation = (curLocation + P[j]) / 2.0;
                        streak = false;
                    } else if(D[j] == 'L') {
                        updateRes(resMatrix, j, curTeam - G[j], i, P[i] - P[j], P[i] - curLocation, P[i]);
                        cont = false;
                        j = -20;
                        break;
                    }
                    j--;
                    
                    if(j == -1) {
                        resMatrix[curTeam] += curLocation;
                        for(int u = 0; u < K; u++) ans[u] += resMatrix[u];
                        cont = false;
                        dp[i] = resMatrix;
                        ex[i][curTeam] = true;
                    }
                }
            } else {
                ex[i][G[i]] = true;
                dp[i][G[i]] = P[i];
                ans[G[i]] += P[i];
            }
        }
    }
    return ans;
}

// int main() {
//     ios_base::sync_with_stdio(false); cin.tie(NULL);
//     int N, K, L;
//     cin >> N >> K >> L;
//     vector<int> P(N), G(N);
//     vector<char> D(N);
//     for (int i = 0; i < N; i++) {
//         cin >> P[i] >> G[i] >> D[i];
//     }
//     vector<double> ret = blindfolded(N, K, L, P, G, D);
//     for (int i = 0; i < K; i++) {
//         cout << fixed << ret[i] << "\n";
//     }
//     return 0;
// }