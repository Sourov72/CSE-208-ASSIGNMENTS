#include<bits/stdc++.h>
using namespace std;
#define MAX 52


int tsize;

unordered_set <string> words;

string wordgenerator()
{
    char alphabet[MAX] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                          'h', 'i', 'j', 'k', 'l', 'm', 'n',
                          'o', 'p', 'q', 'r', 's', 't', 'u',
                          'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C',
                          'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
                          'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S',
                          'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    string res = "";
    for (int i = 0; i < 7; i++)
        res = res + alphabet[rand() % MAX];

    return res;
}

void wordinsert()
{
    string result;
    while(1)
    {
        result = wordgenerator();
        if(words.find(result) == words.end())
        {
            words.insert(result);
            break;
        }
    }
}

int auxHash(string s)
{
    int intLength = s.length() / 4;
    long sum = 0;
    for (int j = 0; j < intLength; j++)
    {
        string c = s.substr(j * 4, (j * 4) + 4);
        long mult = 1;
        for (int k = 0; k < c.length(); k++)
        {
            sum += c[k] * mult;
            mult *= 256;
        }
     }

    string c = s.substr(intLength * 4);
    long mult = 1;
    for (int k = 0; k < c.length(); k++)
    {
       sum += c[k] * mult;
       mult *= 256;
    }

    return(abs(sum) % tsize);
}


int Hash1(string str)
{
    long long hash = 5381;
    int c;
    int i = 0;
    while (c = str[i])
    {
        hash = ((hash << 5) + hash) + c;
        i++;
    }
         // hash*33 + c return hash; }
    return int((hash % tsize));

}



int Hash2(string str)
{
    unsigned long hash = 0;
    int c;
    int i = 0;;
    while (c = str[i])
    {
        hash = c + (hash << 6) + (hash << 16) - hash;
        i++;
    }
    return int(hash % tsize);
}


class node
{
public:
    string key;
    int value;
};


class lList
{
public:
    node* item;
    lList* next;
};

class node *newnode(string s, int v)
{
    class node *temp = new node;
    temp->key = s;
    temp->value = v;
    return temp;
};

class lList *newlist(node* it)
{
    class lList *temp = new lList;
    temp->item = it;
    temp->next = NULL;
    return temp;
};


class HashTable
{
    node** htable;
    lList** obuckets;
    node** doubleH;
    node** customH;
    int *Larray;
    int *Darray;
    int *Carray;
    int size;
    int Lcollisions;
    int Dcollisions;
    int Ccollisions;
    int Lprobing;
    int Dprobing;
    int Cprobing;
    int Lvalue;
    int Dvalue;
    int Cvalue;

public:
    HashTable()
    {
        Lcollisions = 0;
        Dcollisions = 0;
        Ccollisions = 0;
        Lprobing = 0;
        Dprobing = 0;
        Cprobing = 0;
        Lvalue = 0;
        Dvalue = 0;
        Cvalue = 0;
    }

    void createhashtable(int);
    void createbucketlist();
    void createdoublehash();
    void createcustomhash();
    void setcollision();
    void setprobing();
    void chaincolhandle(int, node*);
    void listinsert(lList*, node*, int);
    void Linsert(string, int);
    void Dinsert(string, int);
    void Cinsert(string, int);
    void Lsearch(string, int);
    void Dsearch(string, int);
    void Csearch(string, int);
    void Ldelete(string, int);
    void Ddelete(string, int);
    void Cdelete(string, int);
    void Lprint();
    void Dprint();
    void Cprint();
    void allinfo();
    void DestroyH();
};

void HashTable::setcollision()
{
        Lcollisions = 0;
        Dcollisions = 0;
        Ccollisions = 0;
        Lvalue = 0;
        Dvalue = 0;
        Cvalue = 0;
}

void HashTable::setprobing()
{
    Lprobing = 0;
    Dprobing = 0;
    Cprobing = 0;
}

void HashTable::createdoublehash()
{
    doubleH = new node*[size];
    for(int i=0;i<size;i++)
    {
        doubleH[i] = NULL;

    }
}

void HashTable::createcustomhash()
{
    customH = new node*[size];
    for(int i=0;i<size;i++)
    {
        customH[i] = NULL;

    }
}

void HashTable::createbucketlist()
{
    obuckets = new lList*[size];
    for(int i=0;i<size;i++)
    {
        obuckets[i] = NULL;

    }
}

void HashTable::createhashtable(int n)
{
    size = n;
    htable = new node*[size];

    for(int i=0;i<size;i++)
    {
        htable[i] = NULL;
    }
    Larray = new int[size];
    Darray = new int[size];
    Carray = new int[size];
    memset(Larray, 0, sizeof(Larray));
    memset(Larray, 0, sizeof(Darray));
    memset(Larray, 0, sizeof(Carray));
    createbucketlist();
    createdoublehash();
    createcustomhash();
}

void HashTable::Lsearch(string key, int x)
{
    int index;
    if(x == 1)
        index = Hash1(key);
    else
        index = Hash2(key);
    node* nodeitem = htable[index];
    lList* listitem = obuckets[index];
    while (nodeitem != NULL && Larray[index] == 1)
    {
        Lprobing++;
        if (nodeitem->key == key)
        {
            return ;
        }

        if (listitem == NULL)
            return ;
        nodeitem = listitem->item;
        listitem = listitem->next;
    }
    return ;
}


void HashTable::Dsearch(string s, int x)
{
    int index1;
    if(x == 1)
        index1 = Hash1(s);
    else
        index1 = Hash2(s);
    int index2 = auxHash(s);
    long long i = 0;
    long long newindex;
    node* nodeitem;
    while (1)
    {

        newindex = (index1 + i * index2) % size;
        if(i && newindex == index1)
            return;
        Dprobing++;
        nodeitem = doubleH[newindex];
        if (nodeitem == NULL && Darray[newindex] == 0)
        {
            return ;
        }
        if(Darray[newindex] == 1 && nodeitem->key == s)
        {
            return ;
        }
        i++;
    }
}


void HashTable::Csearch(string s, int x)
{
    int index1;
    if(x == 1)
        index1 = Hash1(s);
    else
        index1 = Hash2(s);
    int index2 = auxHash(s);
    long long i = 0;
    int c1 = 3, c2 = 5;
    long long newindex;
    node* nodeitem;
    while (1)
    {
        newindex = (index1 + c1 * i * index2 + c2 * i * i) % size;
        if(i && newindex == index1)
            return;
        Cprobing++;
        nodeitem = customH[newindex];
        if (nodeitem == NULL && Carray[newindex] == 0)
        {
            return ;
        }

        if(Darray[newindex] == 1 && nodeitem->key == s)
        {

            return;
        }
        i++;
    }
}


void HashTable::listinsert(lList *list, node* item, int index)
{

    if (list->next == NULL)
    {
        lList *newl = newlist(item);
        list->next = newl;
        obuckets[index] = list;
        return;
    }

    lList* temp = list;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    lList* newl = newlist(item);
    temp->next = newl;
    obuckets[index] = list;
}

void HashTable::chaincolhandle(int ind, node* item)
{
    lList* head = obuckets[ind];
    if (head == NULL)
    {
        head = newlist(item);
        obuckets[ind] = head;
        return;
    }
    else
    {
        listinsert(head, item, ind);
        return;
    }
}

void HashTable::Linsert(string s, int x)
{
    Lvalue++;
    node* newitem = newnode(s, Lvalue);
    int index;
    if(x == 1)
        index = Hash1(s);
    else
        index = Hash2(s);
    node* current = htable[index];

    if(current == NULL)
    {
        htable[index] = newitem;
        Larray[index] = 1;
        return;
    }
    else
    {
        Lcollisions++;
        chaincolhandle(index, newitem);
    }

}

void HashTable::Dinsert(string s, int x)
{
    Dvalue++;
    node* newitem = newnode(s, Dvalue);
    int index;
    if(x == 1)
        index = Hash1(s);
    else
        index = Hash2(s);
    node* current = doubleH[index];

    if(current == NULL)
    {
        doubleH[index] = newitem;
        Darray[index] = 1;
        return;
    }
    else
    {

        int index2 = auxHash(s);
        long long i = 1;
        while (1)
        {
            long long newIndex = (index + i * index2) % size;
            if(newIndex == index)
                return;
            Dcollisions++;
            node* current2 = doubleH[newIndex];
            if (current2 == NULL)
            {
                doubleH[newIndex] = newitem;
                Darray[newIndex] = 1;
                return;
            }
            i++;

        }

    }
}

void HashTable::Cinsert(string s, int x)
{
    int c1 = 3, c2 = 5;
    Cvalue++;
    node* newitem = newnode(s, Cvalue);
    int index;
    if(x == 1)
        index = Hash1(s);
    else
        index = Hash2(s);
    node* current = customH[index];

    if(current == NULL)
    {
        customH[index] = newitem;
        Carray[index] = 1;
        return;
    }
    else
    {
        int index2 = auxHash(s);
        long long i = 1;

        while (1)
        {
            Ccollisions++;
            long long newIndex = (index + c1 * i * index2 + c2 * i * i) % size;
            if(newIndex == index)
                return;
            node* current2 = customH[newIndex];
            if (current2 == NULL)
            {
                customH[newIndex] = newitem;
                Carray[newIndex] = 1;
                return;
            }
            i++;

        }

    }
}


void HashTable::Ldelete(string key, int x)
{
    int index;
    if(x == 1)
        index = Hash1(key);
    else
        index = Hash2(key);
    node* item = htable[index];
    lList* head = obuckets[index];

    if (item == NULL)
    {
        cout << "item doesn't exist" << endl;
        return;
    }
    else
    {
        if (head == NULL && item->key == key)
        {
            htable[index] = NULL;
            delete item;
            return;
        }
        else if (head != NULL)
        {
            if (item->key == key)
            {
                delete item;
                lList* temp = head;
                head = head->next;
                temp->next = NULL;
                htable[index] = newnode(temp->item->key, temp->item->value);
                delete temp;
                obuckets[index] = head;
                return;
            }

            lList* curr = head;
            lList* prev = NULL;

            while (curr != NULL)
            {
                if (curr->item->key == key)
                {
                    if (prev == NULL)
                    {
                        delete head;
                        obuckets[index] = NULL;
                        return;
                    }
                    else
                    {
                        prev->next = curr->next;
                        curr->next = NULL;
                        delete curr;
                        obuckets[index] = head;
                        return;
                    }
                }
                curr = curr->next;
                prev = curr;
            }

        }
    }
}


void HashTable::Ddelete(string key, int x)
{
    int index1;
    if(x == 1)
        index1 = Hash1(key);
    else
        index1 = Hash2(key);
    int index2 = auxHash(key);
    long long i = 0;
    long long newindex;
    node* nodeitem;
    while (1)
    {
        newindex = (index1 + i * index2) % size;
        //cout << newindex << endl;
        if(i && newindex == index1)
        {
            //cout << "Doesn't exist\n";
            return;
        }

        nodeitem = doubleH[newindex];
        if (!Darray[newindex] && nodeitem == NULL)
        {
            //cout << "Doesn't exist\n";
            return ;
        }
        if(Darray[newindex] == 1 && nodeitem->key == key)
        {
            delete nodeitem;
            doubleH[newindex] = NULL;
            Darray[newindex] = 2;
            return;
        }
        i++;
    }
}


void HashTable::Cdelete(string key, int x)
{
    int index1;
    if(x == 1)
        index1 = Hash1(key);
    else
        index1 = Hash2(key);
    int index2 = auxHash(key);
    long long i = 0, c1 = 3, c2 = 5;
    long long newindex;
    node* nodeitem;
    while (1)
    {
        newindex = (index1 + c1 * i * index2 + c2 * i * i) % size;
        if(i && newindex == index1)
        {
            //cout << "doesn't exist" << endl;
            return;
        }

        nodeitem = customH[newindex];
        if (nodeitem == NULL && Carray[newindex] == 0)
        {
            //cout << "Doesn't exist\n";
            return ;
        }
        if(Carray[newindex] == 1 && nodeitem->key == key)
        {
            delete nodeitem;
            customH[newindex] = NULL;
            Carray[newindex] = 2;
            break;
        }
        i++;
    }
}


void HashTable::Lprint()
{
    for (int i=0; i<size; i++)
    {
        if (htable[i])
        {
            cout << i << " " << htable[i]->key << " " << htable[i]->value << " ";
            if (obuckets[i])
            {
                lList* head = obuckets[i];
                while (head)
                {
                    cout << head->item->key << " " << head->item->value;
                    head = head->next;
                }
            }
           cout << endl;
        }
    }
    cout << endl;
}

void HashTable::Dprint()
{
    int num = 0;
    for(int i = 0; i < 10000; i++)
    {
        if(doubleH[i])
        {
            cout << doubleH[i]->key << " " << doubleH[i]->value << endl;
            num++;
        }


    }
    //cout << "number of words for double hashing: ";
    //cout << num << endl;
    cout << endl;

}

void HashTable::Cprint()
{
    int num = 0;
    for(int i = 0; i < 10000; i++)
    {
        if(customH[i])
        {
            cout << customH[i]->key << " " << customH[i]->value << endl;
            num++;
        }

    }
    //cout << "number of words for custom hashing: ";
    //cout << num << endl;
    cout << endl;

}


void HashTable::allinfo()
{
    cout << "collisions for Chaining method " << Lcollisions << endl;
    cout << "collisions for Double hashing method " << Dcollisions << endl;
    cout << "collisions for Custom hashing method " << Ccollisions << endl;
    //cout << "total probing for Chaining method " << Lprobing << endl;
    //cout << "total probing for Double hashing method " << Dprobing << endl;
    //cout << "total probing for Custom hashing method " << Cprobing << endl;
    cout << "average probing for Chaining method " << double(Lprobing) / 1000.0 << endl;
    cout << "average probing for Double hashing method " << double(Dprobing) / 1000.0 << endl;
    cout << "average probing for Custom hashing method " << double(Cprobing) / 1000.0 << endl;
    cout << endl << endl;
}


void HashTable::DestroyH()
{
    delete [] htable;
    delete [] obuckets;
    delete [] doubleH;
    delete [] customH;
}


HashTable Insert(HashTable H, int x)
{
    H.setcollision();
    H.setprobing();
    unordered_set<string> :: iterator itr;
    for(itr = words.begin(); itr != words.end(); ++itr)
    {
        H.Linsert(*itr, x);
    }
    for(itr = words.begin(); itr != words.end(); ++itr)
    {
        H.Dinsert(*itr, x);
    }
    for(itr = words.begin(); itr != words.end(); ++itr)
    {
        H.Cinsert(*itr, x);
    }
    return H;
}


HashTable Delete(HashTable H,int x)
{
    unordered_set<string> :: iterator itr;
    for(itr = words.begin(); itr != words.end(); ++itr)
    {
        H.Ldelete(*itr, x);
    }
    for(itr = words.begin(); itr != words.end(); ++itr)
    {
        H.Ddelete(*itr, x);
    }
    for(itr = words.begin(); itr != words.end(); ++itr)
    {
        H.Cdelete(*itr, x);
    }
    H.setcollision();
    H.setprobing();

    return H;
}


HashTable Search(HashTable H, int x)
{
    H.setprobing();
    string temp;
    int num = 0;
    while(num < 1000)
    {
        temp = *std::next(words.begin(), rand() % tsize);
        H.Lsearch(temp, x);
        H.Dsearch(temp, x);
        H.Csearch(temp, x);
        num++;
    }
    return H;
}


int main()
{
    srand(time(NULL));
    int x;
    cout << "size of the table: " << endl;
    cin >> tsize;

    for (int i = 0; i < tsize; i++)
    {
        wordinsert();
    }
    while(1)
    {
        cout << "press:1 for output with hash function 1." << endl;
        cout << "press:2 for output with hash function 2." << endl;
        cout << "press:3 for closing the program." << endl;
        cin >> x;
        if(x == 1)
        {
            HashTable H1;
            H1.createhashtable(tsize);
            H1 = Insert(H1, x);
            H1 = Search(H1, x);
            H1.allinfo();
            H1.DestroyH();


        }
        else if(x == 2)
        {
            HashTable H2;
            H2.createhashtable(tsize);
            H2 = Insert(H2, x);
            H2 = Search(H2, x);
            H2.allinfo();
            H2.DestroyH();

        }
        else if(x == 3)
        {
            break;
        }
    }



}
