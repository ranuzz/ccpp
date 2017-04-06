// Dijkstra algorithm and a small program 
// to randomly generate graphs for testing 
// the graph algorithm

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <climits>
#include <vector>
#include <list>
#include <cassert>

using namespace std;

int **alloc_graph(int vertex)
{
	int **graph = NULL;
	graph = new int*[vertex];
	if (graph == NULL) {
		return NULL;
	}

	for (int i = 0; i < vertex; i++) {
		graph[i] = new int[vertex];
		if (graph[i] == NULL) {
			for (int j = 0; j < vertex; j++) {
				if (graph[j] != NULL) {
					delete[] graph[j];
					graph[j] = NULL;
				}
			}
			delete[] graph;
			return NULL;
		}
	}

	return graph;
}

void free_graph(int **graph, int vertex)
{
	for (int i = 0; i < vertex; i++) {
		if (graph[i] != NULL) {
			delete[] graph[i];
			graph[i] = NULL;
		}
	}
	delete[] graph;
}

void generate_graph(int **graph, int vertex, int density)
{
	srand(time(0));

	for (int i = 0; i < vertex; i++) {
		for (int j = 0; j < vertex; j++) {
			if (i == j) {
				graph[i][j] = 0;
			} else {
				int prob = (rand() %100) + 1;
				if (prob < density) {
					graph[i][j] = graph[j][i] = 1;
				}
			}
		}
	}
}

void print_graph(int **graph, int vertex)
{
	for (int i = 0; i < vertex; i++) {
		for (int j = 0; j  < vertex; j++) {
			cout << graph[i][j];
			if (j != vertex-1)
				cout << "  -  ";
		}
		cout << endl;
	}
}

class vtex {
public:
	int index;
	int dist;
	int prev;
	vtex *next;
	vtex *prevv;

	vtex(int i, int d, int p) {
		index = i;
		dist = d;
		prev = p;
		next = prevv  = NULL;
	}
};

inline void insert_vertex(vtex* &v, vtex* &head)
{
	if (head == NULL) {
		head = v;
	} else {
		vtex *tmp = head;
		while (tmp->next) {
			if (tmp->dist >= v->dist) {
				if (tmp == head) {
					assert(tmp->prevv == NULL);
					head = v;
				}
				v->next = tmp;
				if (tmp->prevv) {
					tmp->prevv->next = v;
				}
				v->prevv = tmp->prevv;
				tmp->prevv = v;
				break;
			}
			tmp = tmp->next;
		}
		if (v->next == NULL) {
			tmp->next = v;
			v->prevv = tmp;
		}
	}
}

void find_path(int **graph, int source, int destination, int vertex)
{

	vector<vtex*> alloc_q;
	vtex *head = NULL;
	vtex *v = NULL;

	for (int i = 0; i < vertex; i++) {
		if (i != source) {
			v = new vtex(i, INT_MAX, -1);
		} else {
			v = new vtex(source, 0, -1);
		}
		alloc_q.push_back(v);
		insert_vertex(v, head);
	}


	while (head != NULL) {
		vtex *v = head;
		head = head->next;
		v->next = v->prevv = NULL;
		if (head != NULL) head->prevv = NULL;
		for (int i = 0; i < vertex; i++) {
			vtex *uv = alloc_q[i];
			if ((graph[v->index][i] != 0) && (uv->prevv != NULL)) {
				int alt_dist = v->dist + graph[v->index][i];
				if (alt_dist < uv->dist) {
					uv->dist = alt_dist;
					uv->prev = v->index;
					//remove from q
					vtex *rmv = uv;
					if (rmv->prevv) rmv->prevv->next = rmv->next;
					if (rmv->next) rmv->next->prevv = rmv->prevv;
					rmv->prevv = rmv->next = NULL;
					//reinsert in order
					vtex *tmp = head;
					assert(head != NULL);
					while (tmp->next) {
						if (tmp->dist >= rmv->dist) {
							if (tmp == head) {
								assert(tmp->prevv == NULL);
								head = rmv;
							}
							rmv->next = tmp;
							if (tmp->prevv) {
								tmp->prevv->next = rmv;
							}
							rmv->prevv = tmp->prevv;
							tmp->prevv = rmv;
							break;
						}
						tmp = tmp->next;
					}
					if (rmv->next == NULL) {
						tmp->next =rmv;
						rmv->prevv = tmp;
					}
				}
			}
		}
	}


	vector<vtex*> path;
	vtex *vv = alloc_q[destination];
	int dist = vv->dist;
	
	int counter = 0;
	while (vv->prev != -1) {
		path.push_back(vv);
		vv = alloc_q[vv->prev];
		if (++counter > (vertex+10)) {
			cout << "This is not a connected Graph !!" << endl;
			return;
		}
	}

	cout << "distance is : " << dist << endl;

	for (int i = 0 ; i < path.size(); i++) {
		cout << "[" << path[i]->index << "]" << " <- ";
	}
	cout << "[" << alloc_q[source]->index << "]" <<endl;

}

int main(int argc, char **argv)
{
	int vertex = 10;
	int density = 50;

	int source  = 0;
	int destination = 8;

	if (argc == 5) {
		vertex = (int) strtol(argv[1], NULL, 10);
		density = (int) strtol(argv[2], NULL, 10);
		source = (int) strtol(argv[3], NULL, 10);
		destination = (int) strtol(argv[4], NULL, 10);
	}
	cout << "number of vertices : " << vertex << endl;
	cout << "Graph density : " << density << endl;

	cout << endl;

	int **graph = alloc_graph(vertex);
	if (graph == NULL) {
		cout << "allcation failure " << endl;
		exit(0);
	}
	generate_graph(graph, vertex, density);
	print_graph(graph, vertex);

	cout << endl;
	cout << "Finding path ["<<source << "] -> [" << destination <<"]" << endl;
	find_path(graph, source, destination, vertex);

	free_graph(graph, vertex);
}
