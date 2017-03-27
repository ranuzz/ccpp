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

/* it is not required but I'm practicing so... */
typedef struct bearstuff {
    int weight;
    int temp;
}bs;

int girl_wt, girl_temp;

int main()
{
    vector<bs> v;
    cin >> girl_wt >> girl_temp;
    int w,t;
    while ( cin >> w >> t) {
        v.push_back({ w, t});
    }
    
    /* could have been done inline in previous while loop
     * doing it here to practice more cpp */
    auto elem = v.begin();
    do {
        elem = find_if(elem,
                        v.end(),
                        [](const bs& r) { return ((r.weight >= girl_wt) && (r.temp <= girl_temp)); });
    
        if (elem != v.end()) {
            cout << (*elem).weight << " " << (*elem).temp << endl;
            elem++;
        }
    } while (elem != v.end());

    
    return 0;
}

