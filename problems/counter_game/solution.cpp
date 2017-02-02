#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

static inline int ispowtwo(unsigned long n) {
    unsigned long test = n & (n-1);
    return (test == 0);
}

static inline unsigned long getnext(unsigned long n) {
    unsigned long t = 1UL << 63;
    while ((n&t) == 0) {
        t = t >> 1;
    }
    return t;
}


int main()
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int T;
    cin >> T;
    unsigned long N;
    while (T--) {
        cin >> N;
                int count = 0;
        while (N != 1) {
                        count++;
            if (ispowtwo(N)) {
                N = N >> 1;
            } else {
                N -= getnext(N);
            }
        }
                if (count == 0) {
                        cout << "Richard" << endl;
                } else if ((count % 2) == 0) {
                        cout << "Richard" << endl;
                } else {
                        cout << "Louise" << endl;
                }
    }

    return 0;
}

