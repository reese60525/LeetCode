#include <cmath>
#include <iostream>
using namespace std;

void printPrime(long long num) {
    cout << num / 10000 << "/";
    cout << (num % 10000) / 1000 << (num % 1000) / 100 << "/";
    if (num % 100 < 10)
        cout << 0;
    cout << num % 100 << endl;
}

void findPrime(long long num, long long num_length) {
    long long temp = num % num_length;
    for (int i = 3; i < sqrt(temp) + 1; ++i) {
        if (temp % i == 0) {
            return;
        }
    }
    if (num_length < 100000000000) {
        return findPrime(num, num_length * 10);
    } else {
        printPrime(num);
    }
}

int main() {
    int days[] = {3, 7, 13, 17, 23, 27};
    for (long long i = 2000000; i <= 2999999; ++i) {
        for (int j = 1; j <= 12; ++j) {
            for (int k = 0; k < 6; ++k) {
                findPrime(i * 10000 + j * 100 + days[k], 100);
            }
        }
    }
    return 0;
}