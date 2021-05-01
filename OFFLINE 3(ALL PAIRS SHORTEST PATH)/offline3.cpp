#include <bits/stdc++.h>
#define mod 1000000007
#define pie M_PI
#define INF INT_MAX
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
const long long int maxs = 100000000;


class Edge
{
    int Svertex;
    int Dvertex;
    double weight;
public:
    void makeEdge(int u, int v, double w)
    {
        Svertex = u;
        Dvertex = v;
        weight = w;
    }
    void weightset(double w)
    {
        weight = w;
    }
    //void
    int getsource()
    {
        return Svertex;
    }
    int getdestination()
    {
        return Dvertex;
    }
    double getweight()
    {
        return weight;
    }




};


class Graph
{
    int nVertices;
    double *distance;
    double *distanceD;
    bool *visited;
    double **distanceMatrix;
    int **parentMatrix;
    vector<Edge> *lis;
    priority_queue<pi, vector<pi>, greater<pi> > minqueue;

public:

    Graph();
    ~Graph();
    Edge* searchEdge(int, int);
    void setnVertices(int);
    bool addEdge(int, int, double);
    void removeEdge(int, int);
    void reweightEdge(int, int, double);
    bool isEdge(int, int);
    int getweight(int, int);
    void Dijkstra(int);
    bool Bellmanford();
    void floydWarshall();
    void johnsonsAlgo();
    double getShortestPathWeight(int u ,int v);
    void printShortestPath(int u, int v);
    void printDistanceMatrix();
    void printPredecessorMatrix();
    void printGraph();
    void clean();
};


Graph::Graph()
{
    nVertices = 0;
    distance = 0;
    distanceD = 0;
    visited = 0;

}


void Graph::setnVertices(int v)
{
    nVertices = v + 1;
    lis = new vector<Edge> [nVertices];
    distanceMatrix = new double*[nVertices];
    parentMatrix = new int*[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        distanceMatrix[i] = new double[nVertices];
        parentMatrix[i] = new int[nVertices];
        for(int j = 0; j < nVertices; j++)
        {
            distanceMatrix[i][j] = INT_MAX;
            parentMatrix[i][j] = -1;

        }

    }

}


Edge* Graph::searchEdge(int u, int v)
{
    for (auto it = lis[u].begin(); it!=lis[u].end(); it++)
    {
        if(it->getsource() == u && it-> getdestination() == v)
        {
           return &(*it);

        }

    }
    return NULL;
}



bool Graph::addEdge(int u, int v, double w)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
    {
        return false;
    }
    Edge *edge = new Edge();
    edge = searchEdge(u, v);
    if(edge != NULL)
    {
        return false;
    }

    Edge e;
    e.makeEdge(u, v, w);
    lis[u].push_back(e);
    return true;


}



void Graph::removeEdge(int u, int v)
{
    int vertex;

    Edge *edge = new Edge();
    edge = searchEdge(u, v);
    if(edge != NULL)
    {
        for (auto it = lis[u].begin(); it!=lis[u].end(); it++)
        {
            if(it->getsource() == u && it-> getdestination() == v)
            {
                 lis[u].erase(it);
                 break;
             }

        }
    }




}



void Graph::reweightEdge(int u, int v, double w)
{
    int vertex;
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
    {
        cout << "out of bounds" << endl;
        return;
    }

    Edge *edge = searchEdge(u, v);;
    if(edge != NULL)
    {
        edge->weightset(w);
    }
    else
    {
        Edge edge;
        edge.makeEdge(u, v, w);
        lis[u].push_back(edge);
    }






}

bool Graph::isEdge(int u, int v)
{

    Edge *edge = searchEdge(u, v);
    if(edge != NULL)
    {
        cout << "present edge" <<endl;
        return true;
    }
    cout << "NO edge" <<endl;
    return false;

}



int Graph::getweight(int u, int v)
{
    int vertex;
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
    {
        cout << "out of bounds";
    }

    Edge *edge = searchEdge(u, v);
    if(edge != NULL)
    {
        return edge->getweight();
    }
    return 1000000;


}


void Graph::Dijkstra(int source)
{
    int place = source;
    distanceMatrix[place][place] = 0;
    pair<int, int> top ;
    int v;
    double w;
    if(distanceD) delete[] distanceD;
        distanceD = 0;

    if(visited) delete[] visited;
        visited = 0;
    distanceD = new double[nVertices];
    visited = new bool[nVertices];
    for(int i = 0;i < nVertices; i++)
    {
        distanceD[i] = INT_MAX;
        visited[i] = false;
    }

    distanceD[source] = 0;
    minqueue.push(make_pair(0, source));
    while(!minqueue.empty())
    {

        top = minqueue.top();
        source = top.second;
        minqueue.pop();
        visited[source] = true;
        for (auto it = lis[source].begin(); it!=lis[source].end(); it++)
        {
            v = it->getdestination();
            w = it->getweight();
            if(!visited[v] && distanceD[source] != INT_MAX)
            {
                if((distanceD[source] + w < distanceD[v]))
                {
                    distanceD[v] = distanceD[source] + w;
                    minqueue.push(make_pair(distanceD[v], v));
                    distanceMatrix[place][v] = distanceD[v] - distance[place] + distance[v];
                    parentMatrix[place][v] = source;
                }
            }
        }


    }


}



bool Graph::Bellmanford()
{
    int v;
    double w;
    if(distance) delete[] distance;
        distance = 0;
    distance = new double[nVertices];
    for(int i = 0;i < nVertices; i++)
    {
        distance[i] = INT_MAX;
    }
    distance[0] = 0;

    for(int i = 1; i <= nVertices - 2; i++)
    {
        for(int u = 0;u < nVertices; u++)
        {

            for (auto it = lis[u].begin(); it!=lis[u].end(); it++)
            {
                v = it->getdestination();
                w = it->getweight();

                if(distance[u] != INT_MAX)
                {
                    if((distance[u] + w < distance[v]))
                    {
                        distance[v] = distance[u] + w;
                    }
                }
            }

        }
    }
    for(int u = 0;u < nVertices; u++)
    {

        for (auto it = lis[u].begin(); it!=lis[u].end(); it++)
        {
            v = it->getdestination();
            w = it->getweight();
            if(distance[u] != INT_MAX)
            {
                if((distance[u] + w < distance[v]))
                {
                    return false;
                }
            }
        }

    }

    return true;

}


void Graph::floydWarshall()
{
    int v;
    double w;

    for(int u = 1;u < nVertices; u++)
    {

        for (auto it = lis[u].begin(); it!=lis[u].end(); it++)
        {

            v = it->getdestination();
            w = it->getweight();
            if(distanceMatrix[u][v] > w)
            {
                distanceMatrix[u][v] = w;
                parentMatrix[u][v] = u;

            }

        }

    }


    for(int k = 1; k < nVertices; k++)
    {
        for(int i = 1; i < nVertices; i++)
        {
            for(int j = 1; j < nVertices; j++)
            {
                if(i == j)
                {
                    distanceMatrix[i][j] = 0;
                    continue;
                }

                if(i == k || k == j) continue;
                if(distanceMatrix[i][j] > (distanceMatrix[i][k] + distanceMatrix[k][j]))
                {
                    distanceMatrix[i][j] = distanceMatrix[i][k] + distanceMatrix[k][j];
                    parentMatrix[i][j] = parentMatrix[k][j];
                }

            }
        }
    }


}


void Graph::johnsonsAlgo()
{
    int v;
    double w;
    for(int i = 1;i < nVertices; i++)
    {
        Edge e;
        e.makeEdge(0, i, 0);
        lis[0].push_back(e);
    }

    if(!Bellmanford())
    {
        cout << "There is a negative-weight cycle." << endl;
        return;
    }

    for(int u = 1;u < nVertices; u++)
    {

        for (auto it = lis[u].begin(); it!=lis[u].end(); it++)
        {
            v = it->getdestination();
            w = it->getweight();
            reweightEdge(u, v, w + distance[u] - distance[v]);
            w = it->getweight();
        }
    }

    for(int u = 1; u < nVertices; u++)
       Dijkstra(u);
    for(int u = 1;u < nVertices; u++)
    {

        for (auto it = lis[u].begin(); it!=lis[u].end(); it++)
        {
            v = it->getdestination();
            w = it->getweight();
            reweightEdge(u, v, w - distance[u] + distance[v]);
            w = it->getweight();
        }
    }

}


void Graph::printShortestPath(int u, int v)
{
    int parent = u;
    int dest = v;
    stack <int> s;
    while(parentMatrix[u][v]!= u)
    {
        s.push(parentMatrix[u][v]);
        v = parentMatrix[u][v];
    }
    cout << parent << " -> ";
    while(!s.empty())
    {
        cout << s.top() << "(" << distanceMatrix[parent][s.top()] << ")" << " -> ";
        parent = s.top();
        s.pop();
    }
    cout << dest << "(" << distanceMatrix[parent][dest] << ")" << endl;

}


double Graph::getShortestPathWeight(int u, int v)
{
    return distanceMatrix[u][v];
}


void Graph::printDistanceMatrix()
{
    for(int i = 1;i < nVertices; i++)
    {
        for(int j = 1; j < nVertices ; j++)
        {

            if(distanceMatrix[i][j] == INT_MAX)
                cout << "INF ";
            else
                cout << distanceMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

void Graph::printPredecessorMatrix()
{
    for(int i = 1;i < nVertices; i++)
    {
        for(int j = 1; j < nVertices ; j++)
        {
            if(parentMatrix[i][j] == -1)
                cout << "NIL ";
            else
                cout << parentMatrix[i][j] << " ";
        }
        cout << endl;
    }
}


void Graph::clean()
{

    for(int i=0;i<nVertices;i++)
    {

        for(int j = 0; j < nVertices; j++)
        {
            distanceMatrix[i][j] = INT_MAX;
            parentMatrix[i][j] = -1;

        }
             //initialize the matrix ceints to 0
    }
}



void Graph::printGraph()
{
    int v, w;
    for(int u = 1;u < nVertices; u++)
    {
        cout << u << " : ";
        for (auto it = lis[u].begin(); it!=lis[u].end(); it++)
        {
            v = it->getdestination();
            w = it->getweight();
            cout << v << "(" << w << ")" << " -> ";

        }
        cout << endl;

    }
}


Graph::~Graph()
{
    // destructor here
    if(distance) delete[] distance; //deallocate memory
    if(visited) delete[] visited;
    if(distanceD) delete[] distanceD;
    if(parentMatrix) delete [] parentMatrix;
    if(distanceMatrix) delete [] distanceMatrix;

}


int main()
{

    // ios_base::sync_with_stdio(0);
    // cin.tie(NUint);
    // cout.tie(NUint);
    Graph g;;
    int N, M, u, v;
    double weight;
    cin >> N >> M;
    g.setnVertices(N);
    while(M--)
    {
        cin >> u >> v >> weight;
        if(!g.addEdge(u, v, weight))
            cout << "edge is not added" << endl;


    }
    cout << "Graph Created." << endl;
    int C;
    while(cin >> C)
    {
        if(C == 1)
        {
            g.clean();
            cout << "APSP matrices cleared" << endl;
        }
        if(C == 2)
        {
            g.floydWarshall();
            cout << "Floyd-Warshall algorithm implemented" << endl;
        }
        if(C == 3)
        {
            g.johnsonsAlgo();
            cout << "Johnson's algorithm implemented" << endl;
        }
        if(C == 4)
        {
            int u, v;
            cin >> u >> v;
            if(g.getShortestPathWeight(u, v) != INT_MAX)
            {
                cout << "Shortest Path Weight: " << g.getShortestPathWeight(u, v) << endl;
                g.printShortestPath(u, v);

            }
            else
            {
                cout << "The distance is infinity" << endl;
            }


        }
        if(C == 5)
        {
            cout << "Graph:" << endl;
            g.printGraph();
            cout << endl;
        }
        if(C == 6)
        {
            cout << "Distance Matrix: " << endl;
            g.printDistanceMatrix();

        }
        if(C == 7)
        {
            cout << "Predecessor Matrix:" << endl;
            g.printPredecessorMatrix();

        }
        if(C == 8)
            break;
    }


}



