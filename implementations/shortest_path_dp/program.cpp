#include <iostream>
#include <algorithm>
#include <list>
#include <unordered_map>
 
using namespace std;

// non-directed weighted graph
class graph {

public:
    vector< vector<int> > matrix;
    graph(int v, int d) {
        vertex = v;
        density = d;
        initGraph(v);
        genGraph();
    }
    int vertex;
    int density;
    void initGraph(int v) {
        matrix.clear();
        for (int i = 0; i < v; i++) {
            vector<int> v1;
            for (int j = 0; j < v ;j++) {
                v1.push_back(0);
            }
            matrix.push_back(v1);
        }      
    }

    void genGraph() {
        srand(time(0));
        for (int i = 0; i < vertex; i++) {
            for (int j = 0; j < vertex; j++) {
                int prob = (rand() %100) +1;
                if (prob < density) {
                    matrix[i][j] = matrix[j][i] = prob;
                }
            }
        }
    }
    
    void printGraph() {
        for (int i = 0; i < vertex; i++) {
            for (int j = 0; j < vertex; j++) {
                cout << matrix[i][j];
                if (j < vertex-1) cout <<" - ";
            }
            cout << endl;
        }
    }
    
};

unordered_map<int, int> memo;

int spath_dp(class graph *g, int source, int destination)
{
   if (source == destination) {
        return 0;
   } 
    auto it1 = memo.find(destination);
    if (it1 != memo.end())
        return (*it1).second;
    int v = g->vertex;
    int min = 0xFFFFFF;
    int path;

    for (int i = 0; i < v; i++) {
        if (g->matrix[destination][i]) {
            auto it = memo.find(i);
            if (it != memo.end()) {
                cout << "hit" << endl;
                path = (*it).second;
            } else {
                 memo.insert({i, -1});
                 path = spath_dp(g, source, i) + g->matrix[destination][i]; 
                    memo[i] = path;
            }
            if ((path != -1) && (path < min)) {
                min = path;
            }
        }
    }
    if (min == 0xFFFFFF) return -1;
    else return min;
}

int main()
{
    int vertex = 10;
    int density = 50;
    class graph g(vertex, density);
    g.printGraph();
    cout << endl;
    cout << endl;
    int shortestpath  = spath_dp(&g, 0, 9);
    cout << "path length : " << shortestpath << endl;
}
