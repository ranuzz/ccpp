#include <iostream>
#include <unordered_map>

using namespace std;

class fibonacci {

private:
    unordered_map<int, int> memo;
    int F1, F2;

public:

    int recursive(int n) {
        int f;
        if (n < 2) f = 1;
        else f = recursive(n-1) + recursive(n-2);
        return f;
    }

    int rec_memo(int n) {
        auto it = memo.find(n);
        if (it != memo.end()) {
            return memo[n];
        }
        int f;
        if (n < 2) f = 1;
        else f = recursive(n-1) + recursive(n-2);
        memo[n] = f;
        return f;
    }

    int bottomup(int n) {
        if (n < 2) return 1;
        
        F1 = 1;
        F2 = 1;
        int res;

        for (int i = 2; i <= n; i++) {
            res = F1 + F2;
            F2 = F1;
            F1 = res;
        }

        return res;
    }

};

int main() {
    fibonacci f;
    int test = 0;
    for (; test < 11; test++)
        cout << f.recursive(test) << "," << f.rec_memo(test) << "," << f.bottomup(test) << endl;
}
