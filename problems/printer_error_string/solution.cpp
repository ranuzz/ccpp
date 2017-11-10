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

class Printer
{
public:
    static std::string printerError(const std::string &s)
    {
        int len = s.size();
        int error = 0;
        for (int i = 0; i < len; i++) {
            if (s[i] > 'm') {
                error++;
            }
        }
        char buffer[1000];
        sprintf(buffer, "%d/%d", error, len);
        return buffer;
    }

    static std::string printerError_ideal(const std::string &s)
    {
        auto const denom = s.length();
        auto numerator = 0;
        numerator = std::count_if(s.cbegin(), s.cend(), [](char c) { return c > 'm';});
        return std::to_string(numerator) + "/" + std::to_string(denom);
    }
};

int main()
{
    Printer p = Printer();
    std::cout << p.printerError("aaabbaabbm") << std::endl;
    std::cout << p.printerError_ideal("aaabbaabbm") << std::endl;
    return 0;
}

