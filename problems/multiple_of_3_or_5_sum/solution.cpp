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

int solution(int number) 
{
  unsigned long sum = 0;
  while (--number){
    if (!(number % 3) || !(number %5)) {
      sum += number;
    }
  }
  return sum;
}

int solution_fast(int number) 
{
  unsigned long sum = 0;
  number--;
  int threes = number / 3;
  int fives = number / 5;
  int fifteens = number / 15;
  // run ap;
  // sum = (n/2) (2*first + (n-1)d)
  sum += (threes == 1) ? 3 : ((threes) * (3+ (threes*3))) / 2;
  sum += (fives == 1) ? 5 : ((fives) * (5+ (fives*5)))  / 2;
  sum -= (fifteens == 1) ? 15 : ((fifteens) * (15+ (fifteens*15))) / 2;
  return sum;
}

int main()
{
    int num = 1500;
    cout << solution(num) << endl;
    cout << solution_fast(num) << endl;
    return 0;
}

