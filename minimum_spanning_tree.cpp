#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#define nullvalue -9999999
#define inf 10000000
//#define fin cin
//#define fout cout

using namespace std;

fstream fin, fout;


class disjoint_set
{
    int n;
    int *parent;
    int *Rank;

public:
    disjoint_set()
    {
        n = 0;
        parent = NULL;
        Rank = NULL;
    }
    disjoint_set(int n)
    {
        this->n = n;
        parent = new int[n+1];
        Rank = new int[n+1];
    }
    void makeset(int n)
    {
        if(this->n == 0){
            this->n = n;
            parent = new int[n+1];
            Rank = new int[n+1];
        }

        for(int i  = 0; i < n; i++){
            parent[i] = i;
            Rank[i] = 0;
        }
    }
    int findset(int x)
    {
        int save = x;
        while(parent[x] != x){
            x = parent[x];
        }
        parent[save] = x;
        return x;
    }
    int unionset(int x, int y)
    {
        x = findset(x);
        y = findset(y);

        if(x == y){
                cout << "yo" << endl;
            return x;
        }

        if(Rank[x] > Rank[y]){
            parent[y] = x;
            return x;
        }
        else if(Rank[x] < Rank[y]){
            parent[x] = y;
            return y;
        }
        parent[y] = x;
        Rank[x]++;
        return x;
    }
};

class Edge
{
    int u;
    int v;
    int w;
public:
    Edge()
    {
        u = v = 0;
        w = 0;
    }
    Edge(int u, int v, int w)
    {
        this->u = u;
        this->v = v;
        this->w = w;
    }
    void setVertex(int u, int v)
    {
        this->u = u;
        this->v = v;
    }
    void setWeight(int new_w){w = new_w;}
    int getTo(){return v;}
    int getFrom(){return u;}
    int getWeight(){return w;}
    friend ostream& operator<<(ostream &out, const Edge& ed)
    {
        out << ed.v << '(' << ed.w << ')';
        return out;
    }
    bool operator<(const Edge& b)
    {
        return this->w < b.w;
    }
    bool operator>(const Edge& b)
    {
        return this->w > b.w;
    }
    bool operator==(const Edge& b)
    {
        return this->w == b.w;
    }
    bool operator<=(const Edge& b)
    {
        return this->w <= b.w;
    }
    bool operator>=(const Edge& b)
    {
        return this->w >= b.w;
    }
    ~Edge(){}
};

class Graph
{
    vector < Edge > *adj_list;
    vector < Edge > MST;
    int n;
    int e;
    int mst;
    int *dist;
    int *visited;
    int *parent;
    void printPath(int u, int v);

public:
    Graph()
    {
        adj_list = NULL;
        n = 0;
        e = 0;
        mst = 0;
        dist = NULL;
        visited = NULL;
        parent = NULL;
    }
    void setnVertices(int n);
    void printGraph();
    bool isEdge(int u, int v);
    bool addEdge(int u, int v, int w);
    void removeEdge(int u, int v);
    Edge* searchEdge(int u, int v);
    int getWeight(int u, int v);
    void Prim(int source);
    void printMST();
    int getmst(){return mst;};
    void Kruskal();

    ~Graph()
    {
        delete adj_list;
        delete dist;
        delete visited;
        delete parent;
        MST.clear();

        mst = 0;
        n = 0;
        e = 0;
    }
};

void Graph::setnVertices(int n)
{
    this->n = n;
    adj_list = new vector <Edge> [n+1];
    visited = new int [n+1];
    dist = new int [n+1];
    parent = new int [n+1];
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
            fout << " --> ";
        }fout << endl;
    }
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
    e++;

    return true;
}


void Graph::removeEdge(int u, int v)
{
    int sz = adj_list[u].size();
    int i;
    vector <Edge> temp;
    for( i = 0; i < sz; i++){
        if(adj_list[u][i].getTo() == v){
            e--;
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


int Graph::getWeight(int u, int v)
{
    Edge *ed = searchEdge(u, v);
    if(ed == NULL) return nullvalue;
    return ed->getWeight();
}


void Graph::Prim(int source)
{
    MST.clear();
    mst = 0;

    int i, j, k;

    for(i = 0; i<= n; i++){
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
        int sz = adj_list[t].size();
        for(i = 0 ; i < sz; i++){
            if(visited[adj_list[t][i].getTo()]) continue;
            if(dist[adj_list[t][i].getTo()] > dist[t] + abs(adj_list[t][i].getWeight())){
                dist[adj_list[t][i].getTo()] = dist[t] + abs(adj_list[t][i].getWeight());
                parent[adj_list[t][i].getTo()] = t;
                pq.push(make_pair(-dist[adj_list[t][i].getTo()], adj_list[t][i].getTo()));
            }
        }
        visited[t] = 1;
    }
    Edge temp;

    for(int i = 0; i < n; i++){
        if(i == source)continue;
        temp = *searchEdge(parent[i], i);
        MST.push_back(temp);
        mst += temp.getWeight();
    }
}

void Graph::printMST()
{
    for(int i = 0; i < n-1; i++){
        fout << MST[i].getFrom() << ' ' << MST[i].getTo() << endl;
    }
}

void Graph::Kruskal()
{
    MST.clear();
    mst = 0;

    disjoint_set ds;
    ds.makeset(n);

    vector < Edge> tempv;

    for(int i = 0; i < n; i++){
        int sz = adj_list[i].size();

        for(int j = 0; j < sz;j++){
            tempv.push_back(adj_list[i][j]);
        }
    }

    sort(tempv.begin(), tempv.end());

    int u, v;
    for(int i = 0; i < e; i++){
        u = ds.findset(tempv[i].getFrom());
        v = ds.findset(tempv[i].getTo());
        if(u != v){
            ds.unionset(u, v);
            MST.push_back(tempv[i]);
            mst += tempv[i].getWeight();
        }
    }

}


int main()
{
    fin.open("input.txt");
    fout.open("output.txt", std::ofstream::out | std::ofstream::trunc);

    Graph G;

    int n, m, u, v, i, j;
    int w, root = 0;

    fin >> n >> m;

    G.setnVertices(n);

    for(i =0; i < m; i++){
        fin >> u >> v >> w;
        G.addEdge(u, v, w);
        G.addEdge(v, u, w);
    }


    G.Kruskal();
    fout << G.getmst() << endl;
    fout << "Kruskal's algorithm:" << endl;
    G.printMST();
    fout << endl;


    fout << "Prim's Algorithm:\n" ;
    G.Prim(root);
    fout << "Root node = " << root << endl;
    G.printMST();

}


