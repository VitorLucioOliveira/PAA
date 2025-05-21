#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int LCS(const string& str1, const string& str2) {
    int n = str1.size();
    int m = str2.size();

    vector<vector<int>> lcs (n+1, vector<int>(m + 1, 0));

    for(int i = 1; i<= n; i++){ //percorre todo o array pulando a primeira linha e coluna
        for(int j = 1; j<= n; j++){
            if(str1[i-1] == str2[j-1])
            {
                lcs[i][j] = lcs[i-1][j-1] + 1;
            }
            else{
                lcs[i][j] = max(lcs[i][j-1], lcs[i-1][j]);
            }
        }
    }


    return lcs[n][m];
}


int main() {
    string x = "ABCDAF";
    string y = "ACBCF";

    int resultado = LCS(x, y);
    cout << "Comprimento da maior subsequencia comum: " << resultado << endl;

    return 0;
}