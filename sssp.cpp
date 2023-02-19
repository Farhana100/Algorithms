#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#define inf 1000000000
#define MAX 2000 //maximum number of nodes

using namespace std;


fstream fin, fout;

class Graph
{
    int n_vert;
    int n_edges;
    vector<int> *E;
    vector<int> *W;
    bool is_undirected;
    int* dist;
    int* parent;
    int* visited;
    void print_path(int t);
public:
    Graph(bool is_undirected);
    void setnVertices(int n);
    bool addEdge(int u, int v, int w);
    int getOutDegree(int u);
    void printGraph();
    void dijkstra( int source, int destination);
    void bellmanFord(int  source, int destination);
    ~Graph();
};

Graph::Graph(bool is_undirected = true)
{
    this->is_undirected = is_undirected;
    n_vert = 0;
    n_edges = 0;
    dist = nullptr;
    parent = nullptr;
    visited = nullptr;
}

void Graph::setnVertices(int n)
{
    if(n_vert != 0){
        delete E;
    }
    n_vert = n;
    E = new vector<int>[n+1];
    W = new vector<int>[n+1];
    dist = new int[n+1];
    parent = new int[n+1];
    visited = new int[n+1];
}

int Graph::getOutDegree(int u)
{
    return E[u].size() ;
}

bool Graph::addEdge(int u, int v, int w)
{
    if(u < 0 || u >= n_vert) return false;
    if(v < 0 || v >= n_vert) return false;
    E[u].push_back(v);
    W[u].push_back(w);
    if(is_undirected){
        E[v].push_back(u);
        W[v].push_back(w);
    }
    n_edges++;
    return true;
}

void Graph::printGraph()
{
    for(int i = 0; i < n_vert; i++){
        cout << "Vertex " << i << ":\t";
        for(int j = 0; j < E[i].size(); j++){
            cout << E[i][j] << ' ';
        }cout << endl;
    }
}


void Graph::dijkstra( int source, int destination)
{
    int i, j, k;

    for(i = 0; i< n_vert; i++){
        dist[i] = inf;
        visited[i] = 0;
        parent[i] = -1;
    }

    priority_queue <pair <int , int> > pq;

    pq.push(make_pair(0, source));
    dist[source] = 0;

    while(!pq.empty())
    {
        int t = pq.top().second;
        pq.pop();
        if(visited[t]) continue;
        int sz = E[t].size();
        for(i = 0 ; i < sz; i++){
            if(visited[E[t][i]]) continue;
            if(dist[E[t][i]] > dist[t] + abs(W[t][i])){
                dist[E[t][i]] = dist[t] + abs(W[t][i]);
                parent[E[t][i]] = t;
                pq.push(make_pair(-dist[E[t][i]], E[t][i]));
            }
        }
        visited[t] = 1;
    }

    if(dist[destination] == inf){
        fout << "Not reachable" << endl;return;
    }

    fout << dist[destination] << endl;

    print_path(destination);
    fout << endl;

}

void Graph::print_path(int t)
{
    if(t == -1){
        return;
    }
    print_path(parent[t]);
    if(parent[t] != -1){
        fout << " -> " ;
    }
    fout << t;
}


void Graph::bellmanFord(int  source, int destination)
{
    int i, j, k;

    for(i = 0; i <= n_vert; i++){
        dist[i] = inf;
        parent[i] = -1;
    }

    dist[source] = 0;
    for(k = 0; k < n_vert; k++){
        for(i = 0; i < n_vert ;i++){
            for(j = 0; j < E[i].size(); j++){
                if(dist[E[i][j]] > dist[i] + W[i][j]){
                    dist[E[i][j]] = dist[i] + W[i][j];
                    parent[E[i][j]] = i;
                }
            }
        }

    }
    for(i = 0; i < n_vert ;i++){
        for(j = 0; j < E[i].size(); j++){
            if(dist[E[i][j]] > dist[i] + W[i][j]){
                fout << "Negative cycle detected\n" ;return;
            }
        }
    }


    if(dist[destination] == inf){
        fout << "Not reachable" << endl;return;
    }

    fout << dist[destination] << endl;
    print_path(destination); cout << endl;

}

Graph::~Graph()
{
    delete E;
}

int main ()
{
    fin.open("input.txt");
    fout.open("output.txt", std::ofstream::out | std::ofstream::trunc);

    long long int i, m, u, v, w, n;
    Graph G(false);

    fin >> n;
    fin >> m;

    G.setnVertices(n);

    for(i = 0; i < m; i++){
        fin >> u >> v >> w;
        G.addEdge(u, v, w);
    }

    fin >> u >> v;


    fout << "Bellman Ford Algorithm:" << endl;
    G.bellmanFord(u, v);
    fout << endl;
    fout << "Dijkstra Algorithm:" << endl;
    G.dijkstra(u, v);

}
