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
    int *distance;
    bool *visited;
    int *parent;
    int *parentP;
    int *rank;
    int kdistance;
    int pdistance;
    vector<pi> *edge;
    vector<pi> print;
    vector< pair<int, pi> > edges;
    priority_queue<pi, vector<pi>, greater<pi> > minqueue;

public:

    Graph();
    ~Graph();
    void setgraph(int, int);
    void addEdge(int, int, int);
    void makeset(int);
    int findset(int);
    void unionset(int, int);
    void Prims(int);
    void kruskal(std::fstream &File);
    int totalDistance();
    void printedge(std::fstream &File);
    void printedgeP(std::fstream &File);
};


Graph::Graph()
{
    nVertices = 0;
    Edges = 0;
    distance = 0;
    visited = 0;
    parent = 0;
    parentP = 0;
    rank = 0;
    kdistance = 0;

}


void Graph::setgraph(int v, int e)
{
    nVertices = v ;
    Edges = e;
    edge = new vector<pi> [nVertices];
}


void Graph::addEdge(int u, int v, int w)
{
    edge[u].push_back(make_pair(v,w));
    edge[v].push_back(make_pair(u,w));
    edges.push_back({w, {u, v}});

}

void Graph::makeset(int i)
{
    parent[i] = i;
    rank[i] = 0;
}

int Graph::findset(int x)
{
    if(x == parent[x])
        return x;
    x = findset(parent[x]);
}


void Graph::unionset(int x, int y)
{
    int r, s;
    r = findset(x);
    s = findset(y);
    if(r == s) return;
    else if(rank[r] > rank[s])
        parent[s] = r;
    else if(rank[s] > rank[r])
        parent[r] = s;
    else
    {
        parent[s] = r;
        rank[r]++;
    }

}



void Graph::Prims(int source)
{
    pair<int, int> top ;
    int v, w;
    if(distance) delete[] distance;
        distance = 0;
    if(parentP) delete[] parentP;
        parentP = 0;
    if(visited) delete[] visited;
        visited = 0;
    distance = new int[nVertices];
    parentP = new int[nVertices];
    visited = new bool[nVertices];

    for(int i = 0;i < nVertices; i++)
    {
        distance[i] = INT_MAX;
        parentP[i] = -1;
        visited[i] = false;
    }
    print.clear();
    distance[source] = 0;
    pdistance = 0;
    minqueue.push(make_pair(0, source));
    while(!minqueue.empty())
    {

        top = minqueue.top();
        source = top.second;
        minqueue.pop();
        visited[source] = true;
        for (auto it = edge[source].begin(); it!=edge[source].end(); it++)
        {
            v = it->first;
            w = it->second;
            if(!visited[v] && distance[source] != INT_MAX)
            {
                if(w < distance[v])
                {
                    distance[v] = w;
                    parentP[v] = source;
                    minqueue.push(make_pair(distance[v], v));
                }
            }
        }

    }



}


void Graph::kruskal(std::fstream &File)
{
    int u, v;
    int x, y;
    if(parent) delete[] parent;
        parent = 0;
    if(rank) delete[] rank;
        rank = 0;
    parent = new int[nVertices];
    rank = new int[nVertices];
    kdistance = 0;
    print.clear();
    for(int i = 0; i < nVertices; i++)
        makeset(i);
    sort(edges.begin(), edges.end());
    for (auto it = edges.begin(); it!=edges.end(); it++)
    {
        u = it->second.first;
        v = it->second.second;
        x = findset(u);
        y = findset(v);
        if(x != y)
        {
            print.push_back(make_pair(u,v));
            unionset(x, y);
            kdistance += it->first;

        }
    }
    File <<"Kruskal distance: " << kdistance << endl;


}



int Graph::totalDistance()
{

    int initial_sum  = 0;
    return accumulate(distance, distance + nVertices, initial_sum);

}

void Graph::printedge(std::fstream &File)
{
    for (auto it = print.begin(); it!=print.end(); it++)
    {
        File << it->first << " " << it->second << endl;
    }

}

void Graph::printedgeP(std::fstream &File)
{
    File << "Prim's Distance: " << totalDistance() << endl;
    for (int i = 0; i < nVertices; i++)
    {
        if(parentP[i] != -1)
            File << parentP[i] << " " << i << endl;
    }

}



Graph::~Graph()
{
    // destructor here

    if(distance) delete[] distance; //deallocate memory

    if(parent) delete[] parent;
;
    if(visited) delete[] visited;




}


int main()
{

    // ios_base::sync_with_stdio(0);
    // cin.tie(NUint);
    // cout.tie(NUint);
    Graph g;
    ifstream myfile1;
    fstream myfile2;
    int root;
    int N, M, u, v, weight, source, destination;
    myfile1.open("input.txt", ios::in);
    myfile2.open("output.txt", ios::out);
    int line;
    if(!myfile1)
    {
        cout << "NO INPUT FILE" << endl;
        return 0;
    }
    myfile1 >> line;
    N = line;
    myfile1 >> line;
    M = line;
    g.setgraph(N, M);
    while(M--)
    {
        myfile1 >> line;
        u = line;
        myfile1 >> line;
        v = line;
        myfile1 >> line;
        weight = line;
        g.addEdge(u, v, weight);

    }
    myfile1.close();
    myfile2 << "Kruskal’s algorithm: " << endl;
    g.kruskal(myfile2);
    g.printedge(myfile2);
    myfile2 << "Prim’s Algorithm: " << endl;
    root = 0;
    myfile2 << "Root node = " << root << endl;
    g.Prims(root);
    g.printedgeP(myfile2);
    myfile2.close();



}
