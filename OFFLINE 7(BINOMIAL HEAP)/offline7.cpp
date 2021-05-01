#include<bits/stdc++.h>
using namespace std;


class node
{
public:

    node *parent;
    node *child;
    node *sibling;
    int key;
    int degree;
};


class node *newnode(int key, int degree)
{
    class node *temp = new node;
    temp->key = key;
    temp->degree = degree;
    temp->parent = NULL;
    temp->child = NULL;
    temp->sibling = NULL;
    return temp;
};


class Bheap
{
    class node *head;
public:
    Bheap()
    {
        head = NULL;
    }
    void sethead(class node*);
    node *gethead();
    node *findmin();
    void insert(int);
    node *merge(Bheap);
    void linkBtrees(class node*, class node*);
    void unify(Bheap);
    node* extractmin();
    void printheap();



};

void Bheap::sethead(class node* newnode)
{
    head = newnode;
}

node* Bheap::gethead()
{
    return head;
}

node* Bheap::findmin()
{
    class node* minnode = head;
    if(head == NULL)
        return minnode;
    class node* current = minnode->sibling;
    while(current != NULL)
    {
        if(current->key < minnode->key)
            minnode = current;
        current = current->sibling;

    }

    return minnode;
}

void Bheap::linkBtrees(class node* Root, class node* Branch)
{
    if (Root->key > Branch->key)
        swap(Root, Branch);
    Branch->parent = Root;
    Branch->sibling = Root->child;
    Root->child = Branch;
    Root->degree = Root->degree + 1;
}

node* Bheap::merge(Bheap T)
{
    class node *temp;
    class node *ahead = T.gethead();
    class node *current1;
    class node *current2;
    class node *current;
    class node *tail;
    if(head == NULL)
    {
        //cout << "bla";
        return ahead;
    }
    if(head->degree <= ahead->degree)
    {
        temp = head;
        current1 = head->sibling;
        current2 = ahead;
    }
    else
    {
        temp = ahead;
        current2 = ahead->sibling;
        current1 = head;
    }
    current = temp;
    while(current1 != NULL && current2 != NULL)
    {
        if(current1->degree <= current2->degree)
        {
            current->sibling = current1;
            current = current->sibling;
            current1 = current1->sibling;

        }
        else
        {
            current->sibling = current2;
            current = current->sibling;
            current2 = current2->sibling;
        }
    }

    if(current1 == NULL)
        tail = current2;
    else
        tail = current1;
    while(tail != NULL)
    {
        current->sibling = tail;
        current = current->sibling;
        tail = tail->sibling;
    }
    return temp;

}


void Bheap::unify(Bheap T)
{
    class node *final_heap = merge(T);

    class node *pre = NULL;
    class node *current;
    class node *next;
    if(final_heap == NULL)
    {
        head = final_heap;
        return;
    }
    //cout << "hello" << endl;
    current = final_heap;
    next = current->sibling;

    bool nmerge;
    while(next != NULL)
    {
        nmerge = true;
        if(current->degree != next->degree)
            nmerge = false;
        if(next->sibling != NULL && (next->sibling->degree == current->degree))
            nmerge = false;
        if(nmerge)
        {
            if(current->key <= next->key)
            {
                current->sibling = next->sibling;
                linkBtrees(current, next);
            }
            else if(pre != NULL)
            {
                pre->sibling = next;
                linkBtrees(next, current);
                current = next;
            }
            else
            {
                final_heap = next;
                linkBtrees(next, current);
                current = next;
            }

        }
        else
        {
            pre = current;
            current = next;
        }
        next = current->sibling;
    }

    head = final_heap;

}


void Bheap::insert(int value)
{
    Bheap T;
    class node *Newnode = newnode(value, 0);
    T.sethead(Newnode);
    unify(T);
}


node* Bheap::extractmin()
{
    class node* curr = head;
    if(curr == NULL)
        return curr;
    class node* prevmin = NULL;
    class node* minnode = NULL;
    class node* prevnode = NULL;
    int min = INT_MAX;
    while (curr != NULL)
    {
        if (curr->key < min)
        {
            min = curr->key;
            prevmin = prevnode;
            minnode = curr;
        }
        prevnode = curr;
        curr = curr->sibling;
    }
    if (prevmin != NULL && minnode->sibling != NULL)
    {
        prevmin->sibling = minnode->sibling;
    }
    else if (prevmin != NULL && minnode->sibling == NULL)
    {
        prevmin->sibling = NULL;
    }
    if(prevmin == NULL)
    {
        head = minnode->sibling;
    }

    stack <node*> rootlist;
    class node* current = minnode->child;
    while(current != NULL)
    {
        current->parent = NULL;
        rootlist.push(current);
        current = current->sibling;
    }
    class node* temp;
    if(rootlist.size() > 0)
    {
        current = rootlist.top();
        rootlist.pop();
    }
    temp = current;
    while(!rootlist.empty())
    {
        current->sibling = rootlist.top();
        rootlist.pop();
        current = current->sibling;
    }
    if(temp != NULL)
    {
        current->sibling = NULL;
        Bheap T;
        T.sethead(temp);
        unify(T);
    }


    return minnode;
}

void Bheap::printheap()
{
    cout << "Printing Binomial Heap..." << endl;
    class node *current = head;
    while(current)
    {
        int degree = current->degree;
        cout << "Binomial Tree, B" << degree;
        queue<node*> q;
        int level = 0, count = 0;
        q.push(current);
        while (!q.empty())
        {
            if (!count)
            {
                count = q.size();
                cout << endl ;
                cout << "Level " << level << " : ";
                level = level + 1;
            }
            node* cur = q.front();
            q.pop();
            cout << cur->key << " ";
            if (cur->child)
            {
                node* temp = cur->child;
                while (temp)
                {
                    q.push(temp);
                    temp = temp->sibling;
                }
            }
            count = count - 1;
        }
        current = current->sibling;
        cout << endl;
    }
}




int main()
{
    Bheap bheap;
    int c;
    string s;
    ifstream myfile1;
    fstream myfile2;
    myfile1.open("in1.txt", ios::in);
    myfile2.open("output.txt", ios::out);
    if(!myfile1)
    {
        cout << "NO INPUT FILE" << endl;
        return 0;
    }
    cout << "1. File print." << "\n";
    cout << "2. Console print." << "\n";
    int x;
    cin >> x;
    if(x == 1)
        freopen("output.txt", "w", stdout);

    while(myfile1 >> s)
    {
        if(s == "I")
        {
            myfile1 >> c;
            bheap.insert(c);

        }
        else if(s == "F")
        {
            node *minn = bheap.findmin();
            if(minn == NULL)
                cout << "There is no key in the heap" << endl;
            else
                cout << "Find-Min returned " << minn->key << endl;
        }
        else if(s == "E")
        {
            node *minn = bheap.extractmin();
            if(minn == NULL)
                cout << "There is no key in the heap" << endl;
            else
                cout << "Extract-Min returned " << minn->key << endl;
        }
        else if(s == "U")
        {
            queue <int> q;
            string line;
            getline(myfile1, line);
            istringstream input(line);
            Bheap bheap1;
            while(input >> c)
            {
                bheap1.insert(c);
            }


            bheap.unify(bheap1);
        }
        else
        {
            bheap.printheap();
        }
    }
}
