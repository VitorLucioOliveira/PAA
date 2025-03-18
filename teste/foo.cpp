#include <iostream>
#include <cmath>

using namespace std;

int count = 0;

int foo(int n) {
    count++;
    if (n <= 1) {
        return 1;
    }
    return foo(n / 4) + foo(n / 4);
}

int main() {
    int n = 10000;  // Agora n é inteiro
    cout << (2 * static_cast<int>(sqrt(n)) - 1) << endl;
    foo(n);
    cout << count << endl;
    return 0;
}
