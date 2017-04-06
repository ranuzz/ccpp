#include <iostream>
#include <algorithm>
#include <list>
 
using namespace std;

// datastructure to hold one element of set 
// heaf keeps a chain of connected elements
class elem {
public:
    elem(int val) {
        data = val;
    }
    int data; // data kept in set (int for sample code)
    list<class elem *> nextelem; // next elem in same set
};

class disjointSet {

private:
    list<class elem *> set;

public:
    disjointSet() {
    }

    int makeSet(int a) {
        if (a < 0) {
            cout << "not a valid data : " << a << endl;
            return 1;
        }
        if (findSet(a) != NULL) {
            cout << "data already present : " << a << endl;
            return 1;
        }
        class elem *node = new elem(a);
        if (node == NULL) {
            cout << "allocation failure : " << a << endl;
            return 1;
        }
        set.push_back(node); 
        return 0;
    }

    class elem* findSet(int a) {
        auto set_it = find_if(set.begin(),
                              set.end(),
                              [a](const elem *node) {
                                    if (node->data == a) {
                                        return 1;
                                    } else {
                                        auto it = find_if(node->nextelem.begin(),
                                                          node->nextelem.end(),
                                                          [a](const elem *n) { return (n->data == a); });
                                        if (it != node->nextelem.end()) {
                                            return 1;
                                        }
                                    }
                                    return 0;
                               });
        if (set_it != set.end()) {
            return *set_it;
        }
        return NULL;
    }

    void unionSet(int a, int b) {
        class elem *ae, *be;
        ae = findSet(a);
        be = findSet(b);
        if ((ae == NULL) || (be == NULL)) {
            cout << "element not present in set " << endl;
            return;
        }
        if (ae == be) {
            cout << "already in the same set " << endl;
            return;
        }
        set.remove(be);
        auto it = ae->nextelem.end();
        ae->nextelem.splice(it, be->nextelem);
        ae->nextelem.push_back(be);
        return;
    }
    
    void printSet(void) {
        int inx = 0;
        for (auto it = set.begin(); it != set.end(); it++) {
            cout << "[" << ++inx << "] : ";
            cout << (*it)->data << " ";
            for (auto ite = (*it)->nextelem.begin(); ite != (*it)->nextelem.end(); ite++) {
                cout << (*ite)->data << " ";
            }
            cout << endl;
        }
    }

    void freeSet(void) {
        while (set.begin() != set.end()) {
            auto it = set.begin();
            while ((*it)->nextelem.begin() != (*it)->nextelem.end()) {
                auto ite = (*it)->nextelem.begin();
                (*it)->nextelem.erase((*it)->nextelem.begin());
                delete *ite;
            }
            set.erase(set.begin());
            delete *it;
        }
    }

};

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

bool compare_edge(const class edge& u, const class edge& v) {
    return (u.w < v.w);
}

int main()
{
    int vertex = 10;
    int density = 50;
    class graph g(vertex, density);
    g.printGraph();
    cout << endl;
    cout << endl;

    class disjointSet ds;
    for (int i = 0; i < vertex; i++) ds.makeSet(i);

    list<edge> E, A;
    for (int i = 0; i < vertex; i++) {
        for (int j = i+1; j < vertex; j++) {
            if (g.matrix[i][j] != 0) {
                class edge e(i, j, g.matrix[i][j]);
                E.push_back(e);
            }
        }
    }
    E.sort(compare_edge);
    for (auto it = E.begin(); it != E.end(); it++) {
        cout << (*it).u << " , " << (*it).v << " , " << (*it).w << endl; 
    }
    cout << endl;
    cout << endl;
    
    for (auto it = E.begin(); it != E.end(); it++) {
        int u = (*it).u;
        int v = (*it).v;
        if (ds.findSet(u) != ds.findSet(v)) {
            ds.unionSet(u,v);
            A.push_back(*it);
        }
    }
    for (auto it = A.begin(); it != A.end(); it++) {
        cout << (*it).u << " , " << (*it).v << " , " << (*it).w << endl; 
    }
    cout << endl;
}
