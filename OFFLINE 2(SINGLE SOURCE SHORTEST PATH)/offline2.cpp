#include <bits/stdc++.h>
#define mod 1000000007
#define pie M_PI
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
const long long int maxs = 100000000;

class Graph
{
    int nVertices;
    int Edges;
    int **matrix;
    int *distance;
    bool *visited;
    int *parent;
    priority_queue<pi, vector<pi>, greater<pi> > minqueue;

public:

    Graph();
    ~Graph();
    void setgraph(int, int);
    void addEdge(int, int, int);
    void print();
    void findminimum(int, int);
    void Dijkstra(int);
    bool Bellmanford(int);
    int getdistance(int);
    void printparent(int, std::fstream &File);
    void printpath(int, std::fstream &OutputFile);
};


Graph::Graph()
{
    nVertices = 0;
    Edges = 0;
    matrix = 0;
    distance = 0;
    visited = 0;
    parent = 0;

}


void Graph::setgraph(int v, int e)
{
    nVertices = v ;
    Edges = e;
    matrix = new int*[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        matrix[i] = new int[nVertices];
        for(int j = 0; j < nVertices; j++)
            matrix[i][j] = 0; //initialize the matrix ceints to 0
    }
}


void Graph::addEdge(int u, int v, int w)
{
    matrix[u][v] = w;
}



void Graph::Dijkstra(int source)
{
    pair<int, int> top ;
    if(distance) delete[] distance;
        distance = 0;
    if(parent) delete[] parent;
        parent = 0;
    if(visited) delete[] visited;
        visited = 0;
    distance = new int[nVertices];
    parent = new int[nVertices];
    visited = new bool[nVertices];
    for(int i = 0;i < nVertices; i++)
    {
        distance[i] = INT_MAX;
        parent[i] = -1;
        visited[i] = false;
    }

    distance[source] = 0;
    minqueue.push(make_pair(0, source));
    while(!minqueue.empty())
    {

        top = minqueue.top();
        source = top.second;
        minqueue.pop();
        visited[source] = true;
        for(int i = 0; i < nVertices; i++)
        {
            if(matrix[source][i] != 0 && !visited[i] && distance[source] != INT_MAX)
            {
                if((distance[source] + abs(matrix[source][i])) < distance[i])
                {
                    distance[i] = distance[source] + abs(matrix[source][i]);
                    parent[i] = source;
                    minqueue.push(make_pair(distance[i], i));
                }
            }
        }

    }


}

bool Graph::Bellmanford(int source)
{
    if(distance) delete[] distance;
        distance = 0;
    if(parent) delete[] parent;
        parent = 0;
    distance = new int[nVertices];
    parent = new int[nVertices];
    for(int i = 0;i < nVertices; i++)
    {
        distance[i] = INT_MAX;
        parent[i] = -1;
    }
    distance[source] = 0;
    for(int i = 1; i <= nVertices - 1; i++)
    {
        for(int u = 0;u < nVertices; u++)
        {
            for(int v = 0;v < nVertices; v++)
            {
                if(matrix[u][v] != 0 && distance[u] != INT_MAX)
                {
                    if(distance[u] + matrix[u][v] < distance[v])
                    {
                        distance[v] = distance[u] + matrix[u][v];
                        parent[v] = u;
                    }
                }
            }
        }
    }

    for(int u = 0;u < nVertices; u++)
    {
        for(int v = 0;v < nVertices; v++)
        {
            if(matrix[u][v] != 0 && distance[u] != INT_MAX)
            {
                if(distance[u] + matrix[u][v] < distance[v])
                {
                    return false;
                }
            }
        }
    }
    return true;


}



int Graph::getdistance(int dist)
{
    return distance[dist];
}


void Graph::printparent(int dist, std::fstream &File)
{
    if(dist == -1)
        return;
    else
    {
         printparent(parent[dist], File);
         File << dist << " -> ";
    }


}

void Graph::printpath(int dist, std::fstream &File)
{
    printparent(parent[dist], File);
    //cout << dist << endl;
    File << dist << endl;

}

void Graph::print()
{
    for(int i = 0;i < nVertices; i++)
    {
        for(int j = 0;j < nVertices; j++)
        {
            if(matrix[i][j] != 0)
            {
                cout << matrix[i][j] << endl;
            }
        }
    }
}



Graph::~Graph()
{
    // destructor here

    if(distance) delete[] distance; //deallocate memory
    distance = 0;
    if(parent) delete[] parent;
    parent = 0;
    if(visited) delete[] visited;
    visited = 0;
    if(matrix) delete[] matrix;
    matrix = 0;


}


int main()
{

    // ios_base::sync_with_stdio(0);
    // cin.tie(NUint);
    // cout.tie(NUint);
    Graph g;
    ifstream myfile1;
    fstream myfile2;
    int N, M, u, v, weight, source, destination;
    myfile1.open("input.txt", ios::in);
    myfile2.open("output.txt", ios::out);
    string line;
    if(!myfile1)
    {
        cout << "NO INPUT FILE" << endl;
        return 0;
    }
    myfile1 >> line;
    N = stoi(line);
    myfile1 >> line;
    M = stoi(line);
    g.setgraph(N, M);
    while(M--)
    {
        myfile1 >> line;
        u = stoi(line);
        myfile1 >> line;
        v = stoi(line);
        myfile1 >> line;
        weight = stoi(line);
        g.addEdge(u, v, weight);


    }
    //g.print();
    myfile1 >> line;
    source = stoi(line);
    myfile1 >> line;
    destination = stoi(line);
    myfile1.close();
    myfile2 << "Bellman Ford Algorithm:" << endl;
    g.Bellmanford(source);
    if(g.Bellmanford(source))
    {
        myfile2 << g.getdistance(destination) << endl;
        g.printpath(destination, myfile2);
    }
    else
        myfile2 << "contains negative edge cycle" << endl;

    myfile2 << "Dijkstra Algorithm:" << endl;
    g.Dijkstra(source);
    myfile2 << g.getdistance(destination) << endl;
    g.printpath(destination, myfile2);
    cout << endl;
    myfile2.close();



}
