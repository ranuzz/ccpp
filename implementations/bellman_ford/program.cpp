#include <iostream>
#include <algorithm>
#include <list>
 
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

class edge {
public:
    edge(int ui, int vi, int wi) {
        u = ui;
        v = vi;
        w = wi;
    }
    int u;
    int v;
    int w;
};

int main()
{
    int vertex = 10;
    int density = 50;
    class graph g(vertex, density);
    g.printGraph();
    cout << endl;
    cout << endl;
    
    int dist[vertex];
    int pred[vertex];
    int source = 0;

    list<int> vertices;
    for (int i = 0; i < vertex; i++) {
        vertices.push_back(i);
        dist[i] = 0xFFFFFF;
        pred[i] = -1;
    }
    dist[source] = 0;

    list<edge> E;
    for (int i = 0; i < vertex; i++) {
        for (int j = i+1; j < vertex; j++) {
            if (g.matrix[i][j] != 0) {
                class edge e(i, j, g.matrix[i][j]);
                E.push_back(e);
            }
        }
    }

    for (int i = 0; i < vertex; i++) {
        for (auto it = E.begin(); it != E.end(); ++it) {
            class edge e = *it;
            if ((dist[e.u] + e.w) < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
                pred[e.v] = e.u;
            }
        }
    }
    
    for (auto it = E.begin(); it != E.end(); ++it) {
        class edge e = *it;
        if ((dist[e.u] + e.w) < dist[e.v]) {
            cout << "graph has negative weight cycles" << endl;
            return 0;
        }
    }

    for (int i = 0; i < vertex; i++) {
        cout << "[" << i << "] : distance : " << dist[i] << endl;
    }
    
}
