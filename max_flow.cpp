#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#define nullvalue -9999999
#define inf 10000000
#define fin cin
#define fout cout

using namespace std;

//fstream fin, fout;

class Edge
{
    int to;
    int from;
    int weight;
    int flow;

public:
    Edge()
    {
        to = from = weight = flow = -1;
    }
    Edge(int u, int v, int w)
    {
        from = u;
        to = v;
        weight = w;
        flow = 0;
    }

    void setVertex(int u, int v)
    {
        from = u;
        to = v;
    }
    void setWeight(int new_w){weight = new_w;}
    void setflow(int new_flow){flow = new_flow;}
    int getTo(){return to;}
    int getFrom(){return from;}
    int getWeight(){return weight;}
    int getflow(){return flow;}

    friend ostream& operator<<(ostream &out, const Edge& ed)
    {
        out << ed.to << '(' << ed.weight << ')';
        return out;
    }
    ~Edge(){};
};

class Graph
{
    vector <vector < Edge > >adj_list;
    int maxflow;
    int n;
    vector <int> dist;
    vector <int> visited;
    vector <int> parent;

public:
    Graph()
    {
        n = 0;
        maxflow = -1;
    }
    void setnVertices(int n);
    void printGraph();
    void printCurr_flow();
    bool isEdge(int u, int v);
    bool addEdge(int u, int v, int w);
    void removeEdge(int u, int v);
    Edge* searchEdge(int u, int v);
    int getWeight(int u, int v);
    int getMaxflow(int src, int sink);
    int flow_bfs(int src, int sink);

    ~Graph(){};
};

void Graph::setnVertices(int n)
{
    this->n = n;
    vector < vector < Edge > > l(n);
    adj_list = l;

    vector <int> vis(n, 0), p(n, -1), d(n, inf);
    visited = vis;
    dist = d;
    parent = p;
}

int Graph::getWeight(int u, int v)
{
    Edge *ed = searchEdge(u, v);
    if(ed == NULL) return nullvalue;
    return ed->getWeight();
}

bool Graph::isEdge(int u, int v)
{
    int sz = adj_list[u].size();

    for(int i = 0; i < sz; i++){
        if(adj_list[u][i].getTo() == v){
            return true;
        }
    }

    return false;
}

bool Graph::addEdge(int u, int v, int w)
{
    if(isEdge(u, v)) return false;

    Edge ed(u, v, w);

    adj_list[u].push_back(ed);

    return true;
}

void Graph::removeEdge(int u, int v)
{
    int sz = adj_list[u].size();
    int i;
    vector <Edge> temp;
    for( i = 0; i < sz; i++){
        if(adj_list[u][i].getTo() == v){
            continue;
        }
        temp.push_back(adj_list[u][i]);
    }

    adj_list[u] = temp;
}

Edge* Graph::searchEdge(int u, int v)
{
    int sz = adj_list[u].size();

    for(int i = 0; i < sz; i++){
        if(adj_list[u][i].getTo() == v){
            return &adj_list[u][i];
        }
    }

    return NULL;
}

void Graph::printGraph()
{
    fout << "Graph:" << endl;
    for(int i = 0; i < n; i++){
        fout << i << " : ";
        int sz = adj_list[i].size();
        for(int j = 0; j < sz; j++){
            fout << adj_list[i][j];
            if(j < sz-1)
            fout << ", ";
        }fout << endl;
    }
}

void Graph::printCurr_flow()
{
    fout << maxflow << endl;
    for(int i = 0; i < n; i++){
        int sz = adj_list[i].size();
        for(int j = 0; j < sz; j++){
            fout << i << ' ' << adj_list[i][j].getTo() << ' ' << adj_list[i][j].getflow() << '/' << adj_list[i][j].getWeight() << endl;
        }
    }
}

int Graph::flow_bfs(int src, int sink)
{
    for(int i = 0; i< n; i++){
        visited[i] = 0;
        dist[i] = inf;
        parent[i] = -1;
    }

    queue <int> q;
    visited[src] = 1;
    dist[src] = 0;
    q.push(src);

    while(!q.empty()){
        int u = q.front();

        for(int j = 0; j < adj_list[u].size(); j++){
            int v = adj_list[u][j].getTo();
            if(visited[v])continue;
            if(adj_list[u][j].getWeight() == 0)continue;

            if(dist[v] > dist[u] + 1){
                dist[v] = dist[u] + 1;
                q.push(v);
                visited[v] = 1;
                parent[v] = u;
            }

            if(v == sink)break;
        }
        q.pop();
    }

    int flow = 0;

    if(dist[sink] == inf)return flow;

    int u = sink;
    Edge* ed;
    flow  = inf;
    while(parent[u] != -1){
        ed = searchEdge(parent[u], u);
        flow = min(flow, ed->getWeight());
        u = parent[u];
    }

    u = sink;
    while(parent[u] != -1){
        ed = searchEdge(parent[u], u);
        ed->setWeight(ed->getWeight() - flow);

        ed = searchEdge(u, parent[u]);
        ed->setWeight(ed->getWeight() + flow);

        u = parent[u];
    }

    return flow;

}

int Graph::getMaxflow(int src, int sink)
{
    // initialize current flow
    Edge* ed;
    Graph resNet;
    resNet.setnVertices(n);

    for(int i = 0; i < n; i++){
        int sz = adj_list[i].size();
        for(int j = 0; j < sz; j++){
            ed = resNet.searchEdge(i, adj_list[i][j].getTo());
            if(ed){
                ed->setWeight(adj_list[i][j].getWeight());
            }
            else{
                resNet.addEdge(i, adj_list[i][j].getTo(), adj_list[i][j].getWeight());
                resNet.addEdge(adj_list[i][j].getTo(), i, 0);
            }
        }
    }

    int aug_flow = -1;
    maxflow = 0;
    while(aug_flow)
    {
        aug_flow = resNet.flow_bfs(src, sink);
        maxflow += aug_flow;
    }

    int diff;
    for(int i = 0; i < n; i++){
        int sz = adj_list[i].size();
        for(int j = 0; j < sz; j++){
            int flow = resNet.searchEdge(adj_list[i][j].getTo(), i)->getWeight();
            int cap = resNet.searchEdge(i, adj_list[i][j].getTo())->getWeight();

            ed = searchEdge(adj_list[i][j].getTo(), i);
            if(ed){
                if(cap > adj_list[i][j].getWeight()){
                    ed->setflow(cap - adj_list[i][j].getWeight());
                    adj_list[i][j].setflow(0);
                }
                else{
                    ed->setflow(0);
                    adj_list[i][j].setflow(adj_list[i][j].getWeight() - cap);
                }
            }
            else{
                adj_list[i][j].setflow(flow);
            }
        }
    }

    return maxflow;
}

int main()
{
//    fin.open("input.txt");
//    fout.open("output.txt", std::ofstream::out | std::ofstream::trunc);

    Graph G;

    int n, m, u, v, i, j, src, sink;
    int w, root = 0;

    fin >> n >> m;

    G.setnVertices(n);

    for(i =0; i < m; i++){
        fin >> u >> v >> w;
        G.addEdge(u, v, w);
    }
    fin >> src >> sink;

    G.getMaxflow(src, sink);

    G.printCurr_flow();
    fout << endl;

}
