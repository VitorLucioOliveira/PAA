#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    vector<int> L = {5, 15, -30, 10, -5, 40, 10};
    int max_total = L[0];
    int max_local = L[0];

    for (size_t i = 1; i < L.size(); i++)
    {
        max_local = max(L[i], max_local + L[i]);
        max_total = max(max_total, max_local);
    }
    

    printf("%i", max_total);
    

    return 0;
}