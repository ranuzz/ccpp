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

string getHashKey(string s) {
    string sorted = s;
    sort(sorted.begin(), sorted.end());
    return sorted;
}

int main()
{
    unordered_map<string, string> map;
 
    string s;
    while (cin >> s) {
        if (s == "-") {
            break;
        }
        map[getHashKey(s)] = s;
    }
    while (cin >> s) {
        cout << "Looking for : " << s << endl;
        auto it = map.find(getHashKey(s));
        if (it == map.end()) {
            cout << "not found" << endl;
        } else {
            cout << it->first << " : " << it->second << endl;
        }
    }

    return 0;
}

