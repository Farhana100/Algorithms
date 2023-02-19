#include <bits/stdc++.h>

using namespace std;
int l[100][100], route[100][100];

void backTrack(string s1, string s2, string s, int i, int j)
{
    if(route[i][j] == 0){
        int len = s.length();
        for(int k = len-1; k >= 0; k--){
            cout << s[k];
        }
        cout << endl;
        return;
    }


    if(route[i][j] == 1){
        backTrack(s1, s2, s, i, j-1);
    }
    else if(route[i][j] == 3){
        backTrack(s1, s2, s, i-1, j);
    }
    else if(route[i][j] == 2){
        s.push_back(s1[i-1]);
        backTrack(s1, s2, s, i-1, j-1);
    }
    else if(route[i][j] == 4){
        backTrack(s1, s2, s, i, j-1);
        backTrack(s1, s2, s, i-1, j);
    }


}

int main()
{
    string s1, s2;
    int i, j, m, n;

    cin >> s1 >> s2;
    m = s1.length();
    n = s2.length();

    ///not visited = 0
    ///diagonally visited = 2
    ///from left = 1
    ///from above = 3
    ///from both = 4

    for(i = 1; i <= m; i++){
        for(j = 1; j <= n; j++){
            if(s1[i-1] == s2[j-1]){
                ///diagonally
                l[i][j] = l[i-1][j-1] + 1;
                route[i][j] = 2;
            }
            else if(l[i][j-1] < l[i-1][j]){
                ///from above
                l[i][j] = l[i-1][j];
                route[i][j] = 3;
            }
            else if(l[i][j-1] > l[i-1][j]){
                ///from left
                l[i][j] = l[i][j-1];
                route[i][j] = 1;
            }
            else if(l[i][j-1] == l[i-1][j]){
                ///from both
                l[i][j] = l[i][j-1];
                route[i][j] = 4;
            }
        }
    }
    cout << endl;

    ///cout << "Length of LCS: " << l[m][n] << endl << endl;

    string s;

    ///cout << "All possible LCS: " << endl;


    backTrack(s1, s2, s, m, n);

    return 0;
}
