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

typedef enum usereval {
    YES,
    HIGHER,
    LOWER,
    UNKNOWN
} uval;

uval getuval(string const& str) {
    if (str == "yes") return YES;
    if (str == "higher") return HIGHER;
    if (str == "lower") return LOWER;
    return UNKNOWN;
}



int main()
{
    srand(time(0));
    string s;
    int min = 1;
    int max = 100;

    cout << "Enter minimum : ";
    cin >> min;
    cout << "Enter maximum : ";
    cin >> max;

    min--;
    max++;

    int guess = (rand() % max);
    if (guess < min) guess = min;
    int count = 0;
    while (1) {
        cout << "are you thinking of : " << guess << endl;
        count++;
        cin >> s;
        switch (getuval(s)) {
            case YES:
                cout << "*****************************" << endl;
                cout << "answer is : " << guess << endl;
                cout << "guesses : " << count << endl;
                cout << "*****************************" << endl;
                return 0;
            case HIGHER:
                if (guess >= (max-1)) {
                    cout << "*****************************" << endl;
                    cout << "you are lying :( " << guess << endl;
                    cout << "*****************************" << endl;
                    return 0;
                }
                min = guess;
                guess += (max - guess) / 2;
                break;
            case LOWER:
                if (guess <= (min+1)) {
                    cout << "*****************************" << endl;
                    cout << "you are lying :( " << guess << endl;
                    cout << "*****************************" << endl;
                    return 0;
                }
                max = guess;
                guess -= (guess - min) / 2;
                break;
            case UNKNOWN:
            default:
                cout << "you entered : " << s << endl;
                cout << "accepted values : yes, higher, lower" << endl;
                break;
        }
    }
    
    return 0;
}

