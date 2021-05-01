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
    vector <Edge> *lis;

public:

    Graph();
    ~Graph();
    Edge* searchEdge(int, int);
    void setnVertices(int);
    bool addEdge(int, int, int);
    void removeEdge(int, int);
    void reweightEdge(int, int, int);
    void reweightRcapacity(int, int, int);
    bool isEdge(int, int);
    int getweight(int, int);
    int getResidualcapacity(int, int);
    int getCapacity(int, int);
    int bfs(int s, int t);
    int maxflow(int s, int t);
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
    nVertices = v;
    BFScolor = new int[nVertices];
    BFSparent = new int[nVertices];
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
    Edge *edge = new Edge();
    edge = searchEdge(u, v);
    if(edge != NULL)
    {
        edge->capacityset(w + edge->getcapacity());
        edge->Rcapacityset(w + edge->getresidualcapacity());
        return true;
    }

    Edge e;
    e.makeEdge(u, v, 0, w);
    lis[u].push_back(e);
    Edge e1;
    e1.makeEdge(v, u, 0, 0);
    lis[v].push_back(e1);

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



int Graph::bfs(int source, int sink)
{
    Queue q;
    for(int i = 0;i < nVertices; i++)
    {
        BFScolor[i] = WHITE;
    }
    for(int i = 0;i < nVertices; i++)
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
            tflow = INT_MAX;
            dest = t;
            while(BFSparent[dest] != dest)
            {

                source = BFSparent[dest];
                tflow = min(tflow, getResidualcapacity(source, dest));
                dest = source;
            }
            mflow += tflow;
            dest = t;
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
    for(int i = 0; i < nVertices; i++)
    {
        for(auto it = lis[i].begin(); it != lis[i].end(); it++)
        {
            c = it->getcapacity();
            if(c > 0)
            {
                v = it->getdestination();
                f = it->getweight();
                printf("%d %d %d/%d\n", i, v, f, c);
            }

        }
    }
}

void Graph::printFlowNetworkfile(std::fstream &File)
{

    int v, f, c;
    for(int i = 0; i < nVertices; i++)
    {
        for(auto it = lis[i].begin(); it != lis[i].end(); it++)
        {
            c = it->getcapacity();
            if(c > 0)
            {
                v = it->getdestination();
                f = it->getweight();
                File << i << " " << v << " " << f << "/" << c << "\n";
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



Graph::~Graph()
{
    // destructor here
    if(BFScolor) delete [] BFScolor;
    if(BFSparent) delete [] BFSparent;

}


int main()
{

    // ios_base::sync_with_stdio(0);
    // cin.tie(NUint);
    // cout.tie(NUint);
    Graph g;
    ifstream myfile1;
    fstream myfile2;
    int N, M, u, v, capacity, source, sink;
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
    g.setnVertices(N);
    while(M--)
    {
        myfile1 >> line;
        u = line;
        myfile1 >> line;
        v = line;
        myfile1 >> line;
        capacity = line;
        if(!g.addEdge(u, v, capacity))
            cout << "edge is not added" << endl;

    }
    myfile1 >> line;
    source = line;
    myfile1 >> line;
    sink = line;
    myfile1.close();
    //g.printGraph();
    cout << "Flow network created" << "\n";
    cout << "1. File print." << "\n";
    cout << "2. Console print." << "\n";
    int c;
    cin >> c;
    cout << endl;
    if(c == 1)
    {
        myfile2 << g.maxflow(source, sink) << endl;
        g.printFlowNetworkfile(myfile2);
    }
    if(c == 2)
    {

        cout << g.maxflow(source, sink) << endl;
        g.printFlowNetwork();

    }
    myfile2.close();



}



