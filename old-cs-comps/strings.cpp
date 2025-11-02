#include<bits/stdc++.h>
using namespace std;

vector<pair<char, int>> sortedArr;
vector<pair<char, int>> unsortedArr;
int cur, curs, n;
void build(string &st){
    sortedArr.resize(n);
    unsortedArr.resize(n);
    for(int i=0; i<n; i++){
        sortedArr[i].first = st.at(i);
        sortedArr[i].second = -i;
        unsortedArr[i].first = st.at(i);
        unsortedArr[i].second = 0;
    }
    sort(sortedArr.begin(), sortedArr.end());

    // int l = 0;
    // int r = 0;
    // for(char i='a'; i<='z'; i++){
    // }
    for(int i = 0; i<n; i++){
        sortedArr[i].second = -sortedArr[i].second;
        unsortedArr[sortedArr[i].second].second = i;
    }
    cur = n-1;
    curs = 0;
}
char removeTop(){
    char c = unsortedArr[cur].first;
    unsortedArr[cur].first = '~';
    sortedArr[unsortedArr[cur].second].first = '~';
    while(unsortedArr[cur].first == '~'){
        cur--;
        if(cur<0) return c;
    }
    while(sortedArr[curs].first == '~') {
        curs++;
        if(curs > n-1) return c;
    }
    return c;
}
char deleteMin(){
    char c = sortedArr[curs].first;
    sortedArr[curs].first = '~';
    unsortedArr[sortedArr[curs].second].first = '~';
    while(unsortedArr[cur].first == '~'){
        cur--;
        if(cur<0) return c;
    }
    while(sortedArr[curs].first == '~') {
        curs++;
        if(curs > n-1) return c;
    }
    return c;
}

pair<bool, string> prettiest_tower(int N, string cubes){
    n = N;
    build(cubes);
    string rami, dani;

    while(cur>=0 && curs < n){
        rami.push_back(removeTop());
        dani.push_back(deleteMin());
    }
    for(int i = 0; i<N/2; i++){ 
        if(dani.at(i) < rami.at(i)) return {true, dani};
        if(dani.at(i) > rami.at(i)) return {false, dani};
    }
    return {false, dani};
}

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     int n;
//     string cubes;
//     cin >> n >> cubes;

//     pair<bool, string> ans = prettiest_tower(n, cubes);
//     if (ans.first) cout << "True" << endl;
//     else cout << "False" << endl;

//     cout << ans.second;
//     return 0;
// }