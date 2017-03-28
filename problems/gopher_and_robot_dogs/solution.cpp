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

typedef struct pos {
    int x;
    int y;
    float speed;
} position;

typedef struct hol {
    int x;
    int y;
    float distance;
    float slope;
    float slope_x;
    float cons;
} hole;

float getDistance(int x1, int y1, int x2, int y2) {
    float dist = 0.0;
    dist += (x1 - x2) * (x1- x2);
    dist += (y1 - y2) * (y1 - y2);
    dist = sqrt(dist);
    return dist;
}

int main()
{
    position dog, gopher;
    cin >> dog.x >> dog.y >> dog.speed;
    cin >> gopher.x >> gopher.y >> gopher.speed;
    int total_holes;
    cin >> total_holes;
    vector<hole> holes(total_holes);
    int closest_hole = 0;
    float min_dis = numeric_limits<float>::max();
    for (int i = 0; i < total_holes; i++) {
        cin >> holes[i].x >> holes[i].y;
        float dist = 0.0;
        dist += (holes[i].x - gopher.x)*(holes[i].x - gopher.x);
        dist += (holes[i].y - gopher.y)*(holes[i].y - gopher.y);
        holes[i].distance = sqrt(dist);
        float dog_dis = getDistance(dog.x, dog.y, holes[i].x, holes[i].y);
        float slope = (gopher.y - holes[i].y);
        float slope_x = (gopher.x - holes[i].x);
        float cons = 0.0;
        int flag = 1;
        if (slope != 0) {
            if (slope_x != 0) {
                slope = slope / slope_x;
                cons = holes[i].y - ((slope)*holes[i].x);
                if ((dog.y - (slope*dog.x) - cons) == 0.0) {
                    flag = 0;
                }
            } else {
                if (dog.x == holes[i].x) {
                    if (dog_dis <= holes[i].distance) {
                        flag = 0;
                    }
                }
            }
        } else {
            if (dog.y == holes[i].y) {
                if (dog_dis <= holes[i].distance) {
                    flag = 0;
                }
            }
        }
        holes[i].slope = slope;
        holes[i].slope_x = slope_x;
        holes[i].cons = cons;
        if ((holes[i].distance < min_dis) && flag) {
            min_dis = holes[i].distance;
            closest_hole = i;
        }
    }
    cout << holes[closest_hole].x << "," << holes[closest_hole].y << endl;

    // solving equation
    // (x-x1)^2 + (y-y1)^2 = (Gspeed/Dspeed)^2 ((x-x2)^2 + (y-y2)^2)
    // x1,y1 : gopher location
    // x2,y2 : dog location
    // y = slope(x) + cons
    // final
    // x^2(Q + Q (slope^2)) + x(2*slope*cons*Q + A + B*slope) + B*cons + P + Q*(slope^2) = 0

    float slope_x = holes[closest_hole].slope_x;
    float slope = holes[closest_hole].slope;
    float cons = holes[closest_hole].cons;
    if (slope_x == 0) {
        cout << "can not handle slope_x == 0, YET!!" << endl;
        return 0;
    }
    float K = (gopher.speed * gopher.speed) / (dog.speed * dog.speed);
    float Q = 1 - K;
    float P = (gopher.x * gopher.x) - (K * (dog.x * dog.x)) + (gopher.y * gopher.y) - (K*(dog.y * dog.y));
    float A = 2 * (K*(dog.x) - gopher.x);
    float B = 2 * (K*(dog.y) - gopher.y);
    float a = Q + Q*(slope*slope);
    float b = 2*slope*cons*Q + A + B*slope;
    float c = B*cons + P + Q*(cons*cons);
    float Z = sqrt((b*b) - (4*a*c));
    float root_a = (-b + Z) / (2*a);
    float root_b = (-b - Z) / (2*a);
    float a_y = slope*root_a + cons;
    float b_y = slope*root_b + cons;
    cout << "x : " << root_a << "," << " y : " << a_y << endl;
    cout << "x : " << root_b << "," << " y : " << b_y << endl;
    return 0;
}

