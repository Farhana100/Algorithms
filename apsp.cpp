#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#define nullvalue -9999999
#define inf 10000000

using namespace std;

fstream fin, fout;

class Edge
{
    int u;
    int v;
    double w;
public:
    Edge()
    {
        u = v = 0;
        w = 0;
    }
    Edge(int u, int v, double w)
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
    void setWeight(double new_w){w = new_w;}
    int getTo(){return v;}
    int getFrom(){return u;}
    double getWeight(){return w;}
    friend ostream& operator<<(ostream &out, const Edge& ed)
    {
        out << ed.v << '(' << ed.w << ')';
        return out;
    }
};

double abs(double num)
{
    return (num < 0.0)? -num: num;
}

class Graph
{
    vector < Edge > *adj_list;
    int n;
    int e;
    double **distanceMatrix;
    int **parentMatrix;
    double *dist;
    int *visited;
    int *parent;
    void printPath(int u, int v);

public:
    Graph()
    {
        adj_list = NULL;
        n = 0;
        e = 0;
        distanceMatrix = NULL;
        parentMatrix = NULL;
        dist = NULL;
        visited = NULL;
        parent = NULL;
    }
    void setnVertices(int n);
    void printGraph();
    bool isEdge(int u, int v);
    bool addEdge(int u, int v, double w);
    void removeEdge(int u, int v);
    Edge* searchEdge(int u, int v);
    void reweightEdge(int u, int v, double w);
    double getWeight(int u, int v);
    void floydWarshall();
    bool bellmanFord(int source = 1);
    void Dijkstra(int source);
    void johnsonsAlgo();
    double getShortestPathWeight(int u ,int v);
    void printShortestPath(int u, int v);
    void printDistanceMatrix();
    void printPredecessorMatrix();
    void cleanSPInfo();

    ~Graph()
    {
        delete adj_list;
        n = 0;
        e = 0;
    }
};

void Graph::setnVertices(int n)
{
    this->n = n;
    adj_list = new vector <Edge> [n+1];
    distanceMatrix = new double* [n+1];
    parentMatrix = new int* [n+1];
    visited = new int [n+1];
    dist = new double [n+1];
    parent = new int [n+1];

    for(int i =0; i <= n; i++){
        distanceMatrix[i] = new double [n+1];
    }
    for(int i =0; i <= n; i++){
        parentMatrix[i] = new int [n+1];
    }
}

void Graph::printGraph()
{
    fout << "Graph:" << endl;
    for(int i = 1; i <= n; i++){
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

bool Graph::addEdge(int u, int v, double w)
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


void Graph::reweightEdge(int u, int v, double w)
{
    Edge *ed = searchEdge(u, v);
    if(ed == NULL){
        addEdge(u, v, w);return;
    }
    ed->setWeight(w);
}


double Graph::getWeight(int u, int v)
{
    Edge *ed = searchEdge(u, v);
    if(ed == NULL) return nullvalue;
    return ed->getWeight();
}


void Graph::Dijkstra(int source)
{
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
}

void Graph::floydWarshall()
{

//    if(bellmanFord())return;
    int i, j, k;

    cleanSPInfo();
    for(i = 0; i <= n; i++){
        for(j = 0; j <= n; j++){
            double wgh = getWeight(i, j);
            if(wgh != nullvalue){
                distanceMatrix[i][j] = wgh;
                parentMatrix[i][j] = i;
            }



        }
    }

    for(i = 0; i<= n; i++){
        distanceMatrix[i][i] = 0;
    }


    for(k = 1; k <= n; k++){
        for(i = 1; i <= n; i++){
            for(j = 1; j <= n; j++){
                if(distanceMatrix[i][j] > distanceMatrix[i][k] + distanceMatrix[k][j]){
                    distanceMatrix[i][j] = distanceMatrix[i][k] + distanceMatrix[k][j];
                    parentMatrix[i][j] = parentMatrix[k][j];
                }
            }
        }
    }

}

bool Graph::bellmanFord(int  source)
{
    int i, j, k;

    for(i = 0; i <= n; i++){
        dist[i] = inf;
        parent[i] = -1;
    }

    dist[source] = 0;
    for(k = 0; k <= n; k++){
        for(i = 0; i <= n ;i++){
            for(j = 0; j < adj_list[i].size(); j++){
                if(dist[adj_list[i][j].getTo()] > dist[i] + adj_list[i][j].getWeight()){
                    dist[adj_list[i][j].getTo()] = dist[i] + adj_list[i][j].getWeight();
                    parent[adj_list[i][j].getTo()] = i;
                }
            }
        }

    }
    for(i = 0; i <= n ;i++){
        for(j = 0; j < adj_list[i].size(); j++){
            if(dist[adj_list[i][j].getTo()] > dist[i] + adj_list[i][j].getWeight()){
                return true;
            }
        }
    }
    return false;
}

void Graph::johnsonsAlgo()
{
    Graph G;
    G.setnVertices(n);

    cleanSPInfo();

    int i, j, k;

    for(i = 1; i <= n; i++){
        for(j = 0; j < adj_list[i].size(); j++){
            G.addEdge(i, adj_list[i][j].getTo(), adj_list[i][j].getWeight());
        }
    }

    for(i = 1; i <= n; i++){
        G.addEdge(0, i, 0);
    }


    if(G.bellmanFord(0)){
        fout << "There is a negative-weight cycle." << endl;return;
    }

    int inc_w[n+1];
    for(i =1; i<= n; i++){
        inc_w[i] = G.dist[i];
    }

    for(i = 1; i <= n; i++){
            int sz = G.adj_list[i].size();
        for(j = 0; j < sz; j++){
            int v = G.adj_list[i][j].getTo();
            double w = G.adj_list[i][j].getWeight();
            G.adj_list[i][j].setWeight(w + inc_w[i] - inc_w[v]);
        }
    }

    for(i = 1; i<= n;i++){
        G.Dijkstra(i);
        for(j = 1; j<= n; j++){
            distanceMatrix[i][j] = G.dist[j] - inc_w[i] + inc_w[j];
            parentMatrix[i][j] = G.parent[j];
        }
    }

}
double Graph::getShortestPathWeight(int u ,int v)
{
    johnsonsAlgo();
    return distanceMatrix[u][v];
}
void Graph::printShortestPath(int u, int v)
{
    johnsonsAlgo();

    printPath(u, v);

    fout << v;
    if(parentMatrix[u][v] != -1)
        fout << '(' << searchEdge(parentMatrix[u][v], v)->getWeight() << ')';

    fout << endl;
}
void Graph::printDistanceMatrix()
{
    int i, j;
    fout << "Distance Matrix:" << endl;
    for(i =1; i<= n; i++){
        for(j =1 ; j <= n ;j++){
            if(distanceMatrix[i][j]==inf)fout << "INF" << ' ';
            else fout << distanceMatrix[i][j] << ' ';
        }fout << endl;
    }
}
void Graph::printPredecessorMatrix()
{
    int i, j;
    fout << "Predecessor Matrix:" << endl;
    for(i =1; i<= n; i++){
        for(j =1 ; j <= n ;j++){
            if(parentMatrix[i][j]==-1)fout << "NIL" << ' ';
            else fout << parentMatrix[i][j] << ' ';
        }fout << endl;
    }

}
void Graph::cleanSPInfo()
{

    int i, j;
    for(i =0; i<= n; i++){
        for(j =0 ; j <= n ;j++){
            parentMatrix[i][j] = -1;
            distanceMatrix[i][j] = inf;
        }
    }
}


void Graph::printPath(int u, int v)
{
    int x = parentMatrix[u][v];

    if(x == -1){
        return;
    }
    printPath(u, x);

    fout << x;
    if(parentMatrix[u][x] != -1)
        fout << '(' << searchEdge(parentMatrix[u][x], x)->getWeight() << ')';
    fout << " --> ";
}


int main()
{
    fin.open("input.txt");
    fout.open("output.txt", std::ofstream::out | std::ofstream::trunc);

    Graph G;

    int n, m, u, v, i, j;
    double w;

    fin >> n >> m;

    G.setnVertices(n);

    for(i =0; i < m; i++){
        fin >> u >> v >> w;
        G.addEdge(u, v, w);
    }

    fout << "Graph Created.\n" ;

    int C;
    while(true)
    {
        fin >> C;

        switch(C)
        {
        case 1:
            {
                G.cleanSPInfo();
                fout << "APSP matrices cleared" << endl;
                break;
            }
        case 2:
            {
                G.floydWarshall();
                fout << "Floyd-Warshall algorithm implemented" << endl;
                break;
            }
        case 3:
            {
                G.johnsonsAlgo();
                fout << "Johnson's algorithm implemented" << endl;
                break;
            }
        case 4:
            {
                fin >> u >> v;
                fout << "Shortest Path Weight: " << G.getShortestPathWeight(u, v) << endl;
                fout << "Path: ";
                G.printShortestPath(u, v);
                break;
            }
        case 5:
            {
                G.printGraph();
                break;
            }
        case 6:
            {
                G.printDistanceMatrix();
                break;
            }
        case 7:
            {
                G.printPredecessorMatrix();
                break;
            }
        default:
            {
                return 0;
            }
        }
    }

}


