#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

int main()
{
    int t;
    cin >> t;
    for (int w = 0; w < t; w++)
    {
        bool cont = true;
        int n, a, b, res;
        res = 0;
        cin >> n >> a >> b;
        vector<vi> c(n, vi(n, -1));
        vector<vi> exce(n, vi(n, false)); 
        for (int i = 0; i < n; i++)
        {
            string s;
            cin >> s;
            for (int j = 0; j < n; j++)
            {
                if (s.at(j) == 'W')
                    c[i][j] = 0;
                else if (s.at(j) == 'G')
                    c[i][j] = 1;
                else if (s.at(j) == 'B')
                    c[i][j] = 2;
            }
        }
        for (int i = n - 1; i >= 0 && cont; i--)
        {
            for (int j = n - 1; j >= 0 && cont; j--)
            {
                if (c[i][j] == 2)
                {
                    if (i - b >= 0 && j - a >= 0)
                    {
                        if (c[i - b][j - a] > 0 && !exce[i-b][j-a])
                        {
                            res++;
                            c[i - b][j - a]--;
                            c[i][j]--;
                            if(c[i - b][j - a] == 1) exce[i-b][j-a] = true; //not working properly?
                            if(c[i][j] != 0){
                            if(i + b < n && j + a < n){
                                if(c[i+b][j+a] == 1){ // && !exce[i+b][j+a]
                                    res++;
                                    c[i+b][j+a]--;
                                    c[i][j]--;
                                }else{
                                    res++;
                                    c[i][j]--;
                                } 
                            } else{
                                res++;
                                c[i][j]--;
                            }
                            }
                        } else cont = false;
                    } else cont = false;
                }
            }
        }
        if(cont == false){
            cout << -1 << endl;
            continue;
        }
        for(int i=n-1; i>=0; i--){
            for(int j=n-1;j>=0;j--){
                if(c[i][j] == 1){
                    if (i - b >= 0 && j - a >= 0){
                        if (c[i - b][j - a] == 1 && !exce[i-b][j-a]){ 
                            res++;
                            c[i][j]--;
                            c[i - b][j - a]--;
                        } else if(!exce[i][j]){
                            res++;
                            c[i][j]--;
                        } else cont = false;
                    } else if(!exce[i][j]){
                        res++;
                        c[i][j]--;
                    } else cont = false;
                }
            }
        }
        if(cont) cout << res << endl;
        else cout << -1 << endl;
    }
}