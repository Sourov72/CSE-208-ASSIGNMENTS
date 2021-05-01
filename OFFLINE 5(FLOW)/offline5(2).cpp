#include <bits/stdc++.h>
#define mod 1000000007
#define pie M_PI
#define INF INT_MAX
#define NULL_VALUE -999999
#define WHITE 1
#define GREY 2
#define BLACK 3
using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
const long long int maxs = 100000000;


class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;   // circular queue implementation
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}






class Edge
{
    int Svertex;
    int Dvertex;
    int flow;
    int capacity;
    int residualc;
public:
    void makeEdge(int u, int v, int w, int c)
    {
        Svertex = u;
        Dvertex = v;
        flow = w;
        capacity = c;
        residualc = c;
    }
    void weightset(int w)
    {
        flow = w;
    }
    void Rcapacityset(int r)
    {
        residualc = r;
    }
    //void
    void capacityset(int c)
    {
        capacity = c;
    }
    int getsource()
    {
        return Svertex;
    }
    int getdestination()
    {
        return Dvertex;
    }
    int getweight()
    {
        return flow;
    }
    int getcapacity()
    {
        return capacity;
    }
    int getresidualcapacity()
    {
        return residualc;
    }




};


class Graph
{
    int nVertices;
	int *BFScolor ;
	int *BFSparent;
	bool *visited;
    vector <Edge> *lis;
    vector <int> source;
    vector <int> sink;

public:

    Graph();
    Edge* searchEdge(int, int);
    void setnVertices(int);
    bool addEdge(int, int, int);
    void addnewEdge(int, int);
    void removeEdge(int, int);
    void reweightEdge(int, int, int);
    void reweightRcapacity(int, int, int);
    bool isEdge(int, int);
    int getweight(int, int);
    int getResidualcapacity(int, int);
    int getCapacity(int, int);
    int bfs(int s, int t);
    bool BipartiteCheck(int);
    int maxflow(int s, int t);
    void newGraph();
    void check();
    void printFlowNetwork();
    void printFlowNetworkfile(std::fstream &File);
    void printGraph();
};


Graph::Graph()
{
    nVertices = 0;
    BFScolor = 0;
    BFSparent = 0;

}


void Graph::setnVertices(int v)
{
    nVertices = v + 2;
    BFScolor = new int[nVertices];
    BFSparent = new int[nVertices];
    visited = new bool[nVertices];
    lis = new vector<Edge> [nVertices];


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


bool Graph::addEdge(int u, int v, int w)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
    {
        return false;
    }

    Edge e;
    e.makeEdge(u, v, 0, w);
    lis[u].push_back(e);
    Edge e1;
    e1.makeEdge(v, u, 0, w);
    lis[v].push_back(e1);

    return true;


}

void Graph::addnewEdge(int u, int v)
{
    Edge e;
    e.makeEdge(u, v, 0, 1);
    lis[u].push_back(e);
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


void Graph::reweightEdge(int u, int v, int w)
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


}


void Graph::reweightRcapacity(int u, int v, int w)
{
    int vertex;
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
    {
        cout << "out of bounds" << endl;
        return;
    }

    Edge *edge = searchEdge(u, v);
    if(edge != NULL)
    {
        edge->Rcapacityset(w);
    }


}

bool Graph::isEdge(int u, int v)
{

    Edge *edge = searchEdge(u, v);
    if(edge != NULL)
    {
        return true;
    }
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




int Graph::getCapacity(int u, int v)
{
    int vertex;
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
    {
        cout << "out of bounds";
    }

    Edge *edge = searchEdge(u, v);
    if(edge != NULL)
    {
        return edge->getcapacity();
    }
    return 1000000;


}



int Graph::getResidualcapacity(int u, int v)
{
    int vertex;
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
    {
        cout << "out of bounds";
    }

    Edge *edge = searchEdge(u, v);
    if(edge != NULL)
    {
        return edge->getresidualcapacity();
    }
    return 1000000;


}


bool Graph::BipartiteCheck(int s)
{
    Queue q;
    int v;
    int source;
    for(int i = 0;i <= nVertices; i++)
    {
        BFScolor[i] = 0;
        BFSparent[i] = -1;
        visited[i] = false;
    }

    for(int i = 1; i <= nVertices - 2; i++)
    {
        if(!visited[i])
        {
            source = i;
            BFScolor[source] = 1;
            BFSparent[source] = source;
            q.enqueue(source);
            visited[source] = true;
            while(!q.empty())
            {
                source = q.dequeue();
                for (auto it = lis[source].begin(); it!=lis[source].end(); it++)
                {
                    v = it->getdestination();
                    if(!visited[v])
                    {

                        BFScolor[v] = 1 - BFScolor[source];
                        q.enqueue(v);
                        visited[v] = true;

                    }
                    if(visited[v] && BFScolor[source] == BFScolor[v])
                    {
                        return false;
                    }
                }
            }
        }
    }


    return true;

}


void Graph::newGraph()
{
   for(int i = 1; i <= nVertices - 2; i++)
   {
       if(BFScolor[i])
       {
           addnewEdge(0, i);
       }

       else
       {
           addnewEdge(i, nVertices - 1);
           sink.push_back(i);

       }

   }


}

void Graph::check()
{
    for(int i = 0; i < sink.size(); i++)
    {
        for (auto it = lis[sink[i]].begin(); it!=lis[sink[i]].end(); it++)
        {
            if(it->getdestination() != nVertices - 1)
            {
                it->capacityset(0);
                it->Rcapacityset(0);
            }

        }
    }

}


int Graph::bfs(int source, int sink)
{
    Queue q;
    for(int i = 0;i <= nVertices + 1; i++)
    {
        BFScolor[i] = WHITE;
    }
    for(int i = 0;i <= nVertices + 1; i++)
    {
        BFSparent[i] = -1;
    }
    BFScolor[source] = GREY;
    BFSparent[source] = source;
    q.enqueue(source);

    int v, r;
    while(!q.empty())
    {
        source = q.dequeue();
        for (auto it = lis[source].begin(); it!=lis[source].end(); it++)
        {
            v = it->getdestination();
            r = it->getresidualcapacity();
            if(r > 0 && BFScolor[v] == WHITE)
            {

                BFScolor[v] = GREY;
                q.enqueue(v);
                BFSparent[v] = source;
                if(v == sink)
                {
                    return 1;
                }

            }
        }
        BFScolor[source] = BLACK;
    }
    return 0;

}



int Graph::maxflow(int s, int t)
{
    int mflow = 0;
    int tflow;
    int source, dest;
    while(true)
    {
        int flow = bfs(s, t);

        if(flow)
        {
            tflow = 1;
            dest = t;
            mflow += tflow;
            source = BFSparent[dest];
            while(BFSparent[dest] != dest)
            {

                source = BFSparent[dest];
                reweightRcapacity(source, dest, getResidualcapacity(source, dest) - tflow);
                reweightRcapacity(dest, source, getResidualcapacity(dest, source) + tflow);
                if(isEdge(dest, source) && getCapacity(dest, source) > 0)
                {
                    if(getweight(dest, source) < tflow)
                    {
                        reweightEdge(source, dest, tflow - getweight(dest, source));
                        reweightEdge(dest, source,0);
                    }
                    else
                    {
                        reweightEdge(source, dest, 0);
                        reweightEdge(dest, source, abs(tflow - getweight(dest, source)));
                    }
                }
                else
                {
                    reweightEdge(source, dest, getweight(source, dest) + tflow);

                }
                dest = source;
            }

        }
        else
        {
            return mflow;
        }
    }

}






void Graph::printFlowNetwork()
{
    int v, f, c;
    for(int i = 1; i <= nVertices - 2; i++)
    {
        for(auto it = lis[i].begin(); it != lis[i].end(); it++)
        {
            c = it->getcapacity();
            f = it->getweight();
            v = it->getdestination();
            if(c > 0 && f > 0 && v != 0 && v != nVertices - 1)
            {
                printf("%d %d\n", i - 1, v - 1);
            }

        }
    }
}

void Graph::printFlowNetworkfile(std::fstream &File)
{

    int v, f, c;
    for(int i = 1; i <= nVertices - 2; i++)
    {
        for(auto it = lis[i].begin(); it != lis[i].end(); it++)
        {
            c = it->getcapacity();
            f = it->getweight();
            v = it->getdestination();
            if(c > 0 && f > 0 && v != 0 && v != nVertices - 1)
            {
                File << i - 1 << " " << v - 1 << endl;
            }

        }
    }
}



void Graph::printGraph()
{
    for(int i = 0; i < nVertices; i++)
    {
        for(auto it = lis[i].begin(); it != lis[i].end(); it++)
        {
            cout << i << " " << it->getdestination() << " " << it->getcapacity();
            cout << endl;

        }
    }
}



int main()
{

    // ios_base::sync_with_stdio(0);
    // cin.tie(NUint);
    // cout.tie(NUint);
    Graph g;
    ifstream myfile1;
    fstream myfile2;
    int N, M, u, v, capacity, source, sink, maxflow;
    myfile1.open("in7.txt", ios::in);
    myfile2.open("output1.txt", ios::out);
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
    g.setnVertices(N);
    while(M--)
    {
        myfile1 >> line;
        u = line;
        myfile1 >> line;
        v = line;
        if(!g.addEdge(u + 1, v + 1, 1))
            cout << "edge is not added" << endl;

    }
    myfile1.close();


    cout << "Flow network created" << "\n";
    cout << "1. File print." << "\n";
    cout << "2. Console print." << "\n";
    int c;
    cin >> c;
    cout << endl;
    if(c == 1)
    {
        if(g.BipartiteCheck(1))
        {
            g.newGraph();
            g.check();
            maxflow = g.maxflow(0, N + 1);
            myfile2 << maxflow << endl;
            g.printFlowNetworkfile(myfile2);


        }
        else
        {
            myfile2 << "The graph is not bipartite." << endl;
        }
    }
    if(c == 2)
    {

        if(g.BipartiteCheck(1))
        {
            g.newGraph();
            g.check();
            maxflow = g.maxflow(0, N + 1);
            cout << maxflow << endl;
            g.printFlowNetwork();


        }
        else
        {
            cout << "The graph is not bipartite." << endl;
        }

    }
    myfile2.close();

    //g.printGraph();




}



