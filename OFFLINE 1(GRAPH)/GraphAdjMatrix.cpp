#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INF 999999
#include<bits/stdc++.h>
#define WHITE 1
#define GREY 2
#define BLACK 3
using namespace std;

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
	rear = (rear + 1) % queueMaxSize ;  // circular queue implementation
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************


//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	int ** matrix ;
	int *distance;
	int *BFScolor ;
	int *BFSparent;
	int *DFScolor;
	int *DFSparent;
	Queue q;
	//adjacency matrix to store the graph
	//define other variables required for bfs such as BFScolor, BFSparent, and dist
	//you must use pointers and dynamic allocation

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	bool addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getInDegree(int u);
    int getOutDegree(int u);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source);
	void bfst(int source);
	void dfsvisit(int source);
	void dfs(int source);
	void TIME();
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	matrix = 0 ;
	directed = dir ;
	BFSparent = 0;
	BFScolor = 0;
	distance = 0;
	DFScolor = 0;
	DFSparent = 0;

	//distance = new int[]
	//set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;

	//allocate space for the matrix
    matrix = new int*[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0;j<nVertices;j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }
    BFScolor = new int[nVertices];
    DFScolor = new int[nVertices];
    distance = new int[nVertices];
    BFSparent = new int[nVertices];
    DFSparent = new int[nVertices];

}

bool Graph::addEdge(int u, int v)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
    {
        cout << "VERTICES LIMIT CROSSED" << endl;
        return false;
    }
    if(!matrix[u][v])
    {
        matrix[u][v] = 1;
        if(!directed) matrix[v][u] = 1;
        nEdges++;
        //cout << "an edge is added" << endl;
        return true;
    }
    else
        return false;

}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
    {
        cout << "VERTICES LIMIT CROSSED" << endl;
        return;
    }
    if(matrix[u][v])
    {
        matrix[u][v] = 0;
        if(!directed) matrix[v][u] = 0;
        cout << "the edge between " << u << " & " << v << " is removed" << endl;
        nEdges--;
    }
    else
    {
        cout << "There is no edge between " << u << " & " << v << endl;
    }

}

bool Graph::isEdge(int u, int v)
{

    if(u<0 || u>=nVertices || v<0 || v>=nVertices)
        return false;
    if(matrix[u][v] == 1)
        return true;
    else
        return false;

    //returns true if (u,v) is an edge, otherwise should return false
}



int Graph::getInDegree(int u)
{
    int count = 0;
    for(int i = 0;i < nVertices; i++)
    {
        if(matrix[i][u])
            count++;
    }
    return count;

}

int Graph::getOutDegree(int u)
{
    int count = 0;
    for(int i = 0;i < nVertices; i++)
    {
        if(matrix[u][i])
            count++;
    }
    return count;

}



/*void Graph::printAdjVertices(int u)
{
    //prints all adjacent vertices of a vertex u
    if(directed)
    {
        for(int i = 0;i < nVertices; i++)
        {
            if(matrix[u][i] == 1)
                cout << i << " ";

        }

        cout << endl;
    }
    if(!directed)
    {
        for(int i = 0;i < nVertices; i++)
        {
            if(matrix[u][i] == 1)
                cout << i << " ";

        }
        for(int i = 0;i < nVertices; i++)
        {
            if(matrix[i][u] == 1)
                cout << i << " ";

        }
        cout << endl;
    }


}*/

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    for(int i = 0;i < nVertices; i++)
    {
        if((matrix[u][i] == 1 && matrix[v][i] == 1))
            return true;

    }

    return false;

}

void Graph::bfs(int source)
{

    for(int i = 0;i < nVertices; i++)
    {
        BFScolor[i] = WHITE;
    }

    for(int i = 0;i < nVertices; i++)
    {
        BFSparent[i] = -1;
    }

    for(int i = 0;i < nVertices; i++)
    {
        distance[i] = 0;
    }
    BFScolor[source] = GREY;
    BFSparent[source] = source;
    q.enqueue(source);
    while(!q.empty())
    {
        // Dequeue a vertex from queue and print it

        source = q.dequeue();
        cout << source << " ";

        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited,
        // then mark it visited and enqueue it

        for (int i = 0; i < nVertices; i++)
        {
            if(matrix[source][i])
            {

                if (BFScolor[i] == WHITE)
                {
                    BFScolor[i] = GREY;
                    q.enqueue(i);
                    distance[i] = distance[source] + 1;
                    BFSparent[i] = source;
                }

            }
        }

        BFScolor[source] = BLACK;
    }
    cout << endl;

}


void Graph::bfst(int source)
{

    for(int i = 0;i < nVertices; i++)
    {
        BFScolor[i] = WHITE;
    }

    for(int i = 0;i < nVertices; i++)
    {
        BFSparent[i] = -1;
    }

    for(int i = 0;i < nVertices; i++)
    {
        distance[i] = 0;
    }
    BFScolor[source] = GREY;
    BFSparent[source] = source;
    q.enqueue(source);
    while(!q.empty())
    {
        // Dequeue a vertex from queue and print it

        source = q.dequeue();

        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited,
        // then mark it visited and enqueue it

        for (int i = 0; i < nVertices; i++)
        {
            if(matrix[source][i])
            {

                if (BFScolor[i] == WHITE)
                {
                    BFScolor[i] = GREY;
                    q.enqueue(i);
                    distance[i] = distance[source] + 1;
                    BFSparent[i] = source;
                }

            }
        }

        BFScolor[source] = BLACK;
    }

}


void Graph::dfsvisit(int source)
{
    cout << source << " ";
    DFScolor[source] = GREY;

    for(int i = 0;i < nVertices; i++)
    {
        if(matrix[source][i])
        {
            if(DFScolor[i] == WHITE)
            {
                DFSparent[i] = source;
                dfsvisit(i);
            }
        }
    }
    DFScolor[source] = BLACK;
}

void Graph::dfs(int source)
{
    for(int i = 0;i < nVertices; i++)
    {
        DFScolor[i] = WHITE;
    }

    for(int i = 0;i < nVertices; i++)
    {
        DFSparent[i] = -1;
    }
    DFScolor[source] = GREY;
    DFSparent[source] = source;
    cout << source << " ";

    for(int i = 0;i < nVertices; i++)
    {
        if(matrix[source][i])
        {
            if(DFScolor[i] == WHITE)
            {
                DFSparent[i] = source;
                dfsvisit(i);
            }
        }

    }
    DFScolor[source] = BLACK;

    cout << endl;

}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance

    bfs(u);
    if(u == v)
    {
        return 0;
    }
    if(distance[v])
        return distance[v];
    else
        return INF;

}



void Graph::TIME()
{
    srand(time(NULL));
    int vertices[5] = {1000, 2000, 4000, 8000, 16000};
    for(int vt = 0;vt < 5; vt++)
    {
        printf("number of vertices: %d\n", vertices[vt]);
        if(matrix) delete[] matrix;
        matrix = 0;
        setnVertices(vertices[vt]);
        int e = vertices[vt];
        int count = 0;
        double avg = 0;
        while(e <= ((vertices[vt] * vertices[vt]) - vertices[vt]) / 8)
        {
            for(int i = count;i < e; i++)
            {
                int u = rand() % vertices[vt];
                int v = rand() % vertices[vt];
                while(matrix[u][v] != 0)
                {
                    u = rand() % vertices[vt] ;
                    v = rand() % vertices[vt] ;
                }
                matrix[u][v] = 1;
                if(!directed) matrix[v][u] = 1;
            }
            for(int j = 0;j < 10; j++)
            {
                int rsource = rand() % vertices[vt];
                auto start = std::chrono::steady_clock::now();
                bfst(rsource);
                auto end = std::chrono::steady_clock::now();
                std::chrono::duration<double> diff = end-start;
                avg += (diff.count() * 1000000);
               // cout << "time: " << diff.count() * 1000000 << endl;
            }
            avg = (avg / 10.0);
            printf("avgtime for edges %d is %ff\n", e, avg);
            avg = 0;
            count = e;
            e = e * 2;


        }

    }

}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<nVertices;j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    //write your destructor here
    if(BFScolor) delete[] BFScolor; //deallocate memory
    BFScolor = 0;
    if(distance) delete[] distance; //deallocate memory
    distance = 0;
    if(BFSparent) delete[] BFSparent;
    BFSparent = 0;
    if(DFSparent) delete[] DFSparent;
    DFSparent = 0;
    if(DFScolor) delete[] DFScolor;
    DFScolor = 0;
    if(matrix) delete[] matrix;
    matrix = 0;


}




//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    srand(time(NULL));
    int n;
    int choice;
    bool dir;
    printf("Enter your choice:\n");
    printf("1. directed graph   2. undirected graph\n");
    scanf("%d",&choice);
    if(choice == 1)dir = true;
    else if(choice == 2)dir = false;

    Graph g(dir);
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        printf("1. Add edge. \n");
        printf("2. Remove edge. \n");
        printf("3. IN degree. \n");
        printf("4. OUT degree. \n");
        printf("5. hasCommonAdjacent. \n");
        printf("6. edge present check. \n");
        printf("7. BFS . \n");
        printf("8. DFS . \n");
        printf("9. Get distance. \n");
        printf("10. Print Graph. \n");
        printf("11. Run Time Analysis Check. \n");
        printf("12. Exit. \n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
            printf("Add edge between: \n");
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
        }
        else if(ch==2)
        {
            int u, v;
            printf("Remove the edge between: \n");
            scanf("%d%d", &u, &v);
            g.removeEdge(u, v);
        }
        else if(ch==3)
        {
            int u;
            printf("In degree of vertex: ");
            cin >> u;
            cout << g.getInDegree(u);

        }
        else if(ch==4)
        {
            int u;
            printf("Out degree of vertex: ");
            cin >> u;
            cout << g.getOutDegree(u);
        }
        else if(ch==5)
        {
            int u, v;
            cout << "common adjacent between two vertexs" << endl;
            cout << "the two vertexes are: ";
            scanf("%d%d", &u, &v);
            if(g.hasCommonAdjacent(u, v))
           {
               cout << "is present" << endl;
           }
           else
           {
               cout << "isn't present" << endl;
           }

        }
        else if(ch==6)
        {
            int u, v;
            printf("the edge present check between vertex: ");
            scanf("%d%d", &u, &v);
            if(g.isEdge(u, v))
            {
                cout << "is present" << endl;
            }
            else
            {
                cout << "isn't present" << endl;
            }

        }
        else if(ch==7)
        {
            int u;
            cout << "Source: ";
            cin >> u;
            g.bfs(u);
        }
        else if(ch==8)
        {
            int u;
            cout << "Source: ";
            cin >> u;
            g.dfs(u);
        }
        else if(ch==9)
        {
            int u, v;
            printf("the shortest path distance between two vertexes and the vertexes are: ");
            cin >> u >> v;
            int d = g.getDist(u, v);
            cout << "the distance is : " << d << endl;
        }
        else if(ch==10)
        {
           g.printGraph();
        }

        else if(ch == 11)
        {

            g.TIME();


        }
        else if(ch==12)
        {
           break;
        }

        cout << endl;
    }

}
