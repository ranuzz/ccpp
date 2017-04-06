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

int main()
{
    class disjointSet ds;
    ds.makeSet(1);
    ds.makeSet(2);
    ds.makeSet(3);
    ds.makeSet(1);
    ds.makeSet(1);

    ds.printSet();

    ds.unionSet(1,2);
    ds.printSet();
    ds.unionSet(1,2);
    ds.printSet();
    
    ds.unionSet(1,4);
    ds.freeSet();
    ds.printSet();
}
