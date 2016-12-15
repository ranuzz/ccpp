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
#include <vector>
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

const int n = 26;

int main(){
    vector<int> h(n);

    for(int h_i = 0;h_i < n;h_i++){
       cin >> h[h_i];
    }

    string word;
    cin >> word;

	int max_height = 0;

	for (string::iterator it = word.begin(); it != word.end(); ++it) {
		char ch = static_cast<char>(*it);
		int ascii = static_cast<int>(ch);
		ascii -= 97;
		if (h[ascii] > max_height) max_height = h[ascii];
	}

	int width = word.size();
	cout << (width*max_height) << endl;

    return 0;
}

