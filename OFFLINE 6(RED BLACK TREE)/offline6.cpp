#include<bits/stdc++.h>
using namespace std;

class node
{
public:

    node *left;
    node *right;
    node *parent;
    int key;
    string color;
};




class node *newnode(int key, class node *New)
{
    class node *temp = new node;
    temp->key = key;
    temp->left = NULL;
    temp->right = NULL;
    temp->parent = New;
    temp->color = "r";
    return temp;
};


class RBT
{
    class node *root;
public:
    RBT()
    {
        root = NULL;
    }
    void LeftRotate(class node*);
    void RightRotate(class node*);
    void insert(int);
    void InsertFixup(class node*);
    bool Search(int);
    void Delete(int);
    void DeleteNode(class node*);
    void DeleteFixup(class node*, class node*);
    void Preorder(class node*);
    void print();


};

void RBT::LeftRotate(class node *node)
{
    class node *y = node->right;
    node->right = y->left;
    if(y->left != NULL)
        y->left->parent = node;
    y->parent = node->parent;
    if(node->parent == NULL)
    {
        root = y;
    }
    else if(node == node->parent->left)
    {
        node->parent->left = y;
    }
    else
        node->parent->right = y;
    y->left = node;
    node->parent = y;
}



void RBT::RightRotate(class node *node)
{
    class node *y = node->left;
    node->left = y->right;
    if(y->right != NULL)
        y->right->parent = node;
    y->parent = node->parent;
    if(node->parent == NULL)
    {
        root = y;
    }
    else if(node == node->parent->right)
    {
        node->parent->right = y;
    }
    else
        node->parent->left = y;
    y->right = node;
    node->parent = y;
}




void RBT::InsertFixup(class node *node)
{

    while(node->parent != NULL && node->parent->color == "r")
    {
        class node *grandparent = node->parent->parent;
        class node *uncle;

        if(node->parent == grandparent->left)
        {
            uncle = grandparent->right;
            if(uncle != NULL && uncle->color == "r")
            {
                node->parent->color = "b";
                uncle->color = "b";
                grandparent->color = "r";
                node = grandparent;
            }
            else
            {
                if(node == node->parent->right)
                {
                    node = node->parent;
                    LeftRotate(node);

                }
                node->parent->color = "b";
                node->parent->parent->color = "r";
                RightRotate(node->parent->parent);
            }
        }
        else
        {

            uncle = grandparent->left;
            if(uncle != NULL && uncle->color == "r")
            {

                node->parent->color = "b";
                uncle->color = "b";
                grandparent->color = "r";
                node = grandparent;
            }
            else
            {
                if(node == node->parent->left)
                {

                    node = node->parent;
                    RightRotate(node);

                }

                node->parent->color = "b";
                node->parent->parent->color = "r";

                LeftRotate(node->parent->parent);
            }
        }
    }
    root->color = "b";
}





void RBT::insert(int value)
{
    if(root == NULL)
    {
        root = newnode(value, NULL);
        root->color = "b";
    }
    else
    {
        class node *Newnode = newnode(value, NULL);
        class node *temp;
        class node *node = root;
        while(node != NULL)
        {
            temp = node;
            if(Newnode->key < node->key)
                node = node->left;
            else
                node = node->right;
        }
        Newnode->parent = temp;
        if(Newnode->key < temp->key)
            temp->left = Newnode;
        else
            temp->right = Newnode;

        InsertFixup(Newnode);
    }

    //if(value == node->key)
        //return oldnode(node,value);


};




bool RBT::Search(int value)
{
    class node *temp = root;
    while(true)
    {
        if(temp == NULL)
            return false;
        else if(temp->key == value)
            return true;
        else if(value < temp->key)
        {
            temp = temp->left;
        }
        else
        {
            temp = temp->right;
        }
    }

}



void RBT::Delete(int value)
{
    if(root == NULL)
        return ;
    class node *Dnode = root;
    while(Dnode != NULL)
    {
        if(Dnode->key == value)
        {
            DeleteNode(Dnode);
            break;
        }
        else if(Dnode->key > value)
        {
            Dnode = Dnode->left;
        }
        else
            Dnode = Dnode->right;
    }
};



void RBT::DeleteNode(class node* node)
{
    class node *current;
    class node *temp;
    if(node->left == NULL || node->right == NULL)
    {
        current = node;
    }
    else
    {
        temp = node->right;
        while(temp->left != NULL)
        {
            temp = temp->left;
        }
        current = temp;


    }
    if(current->left != NULL)
    {
        temp = current->left;
    }
    else
    {
        temp = current->right;
    }
    if(temp != NULL)
    temp->parent = current->parent;
    if(current->parent == NULL)
    {
        if(temp != NULL)
        root = temp;
        else
        {
            root = NULL;
            return;
        }
    }
    else if(current == current->parent->left)
    {
        current->parent->left = temp;
    }
    else
        current->parent->right = temp;
    if(current != node)
    {
        node->key = current->key;
    }

    if(current->color == "b")
    {
        DeleteFixup(temp, current->parent);
    }
    if(temp == root && temp->key == node->key)
    root = NULL;
    else
        delete current;
}


void RBT::DeleteFixup(class node *node, class node *father)
{

    class node *sibling;
    while(node == NULL || (node->color == "b" && node != root))
    {
        if(node == father->left)
        {

            sibling = father->right;
            if(sibling != NULL)
            {

                if(sibling->color == "r")
                {

                    sibling->color = "b";
                    father->color = "r";
                    LeftRotate(father);
                    sibling = father->right;
                }
                if((sibling->left == NULL && sibling->right == NULL) || (sibling ->left != NULL && sibling->left->color == "b" && sibling->right != NULL && sibling->right->color == "b"))
                {
                    sibling->color = "r";
                    node = father;
                    father = node->parent;
                }
                else if(sibling->right == NULL || sibling->right->color == "b")
                {
                    sibling->left->color = "b";
                    sibling->color = "r";
                    RightRotate(sibling);
                    sibling = father->right;
                }
                else
                {
                    sibling->color = father->color;
                    father->color = "b";
                    if(sibling->right != NULL)
                    sibling->right->color = "b";
                    LeftRotate(father);
                    node = root;
                }


            }
        }

        else
        {
            sibling = father->left;
            if(sibling != NULL)
            {

                if(sibling->color == "r")
                {
                    sibling->color = "b";
                    father->color = "r";
                    RightRotate(father);
                    sibling = father->left;
                }
                if((sibling->left == NULL && sibling->right == NULL) || (sibling ->left != NULL && sibling->left->color == "b" && sibling->right != NULL && sibling->right->color == "b"))
                {
                    sibling->color = "r";
                    node = father;
                    father = node->parent;
                }
                else if(sibling ->left == NULL || sibling->left->color == "b")
                {
                    sibling->right->color = "b";
                    sibling->color = "r";
                    LeftRotate(sibling);
                    sibling = father->left;
                }
                else
                {
                    sibling->color = father->color;
                    father->color = "b";
                    if(sibling->left != NULL)
                    sibling->left->color = "b";
                    RightRotate(father);
                    node = root;
                }


            }
        }

    }
    node->color = "b";
}



void RBT::Preorder(class node* node)
{
    if(node == NULL)
        return;
    cout << node->key << ":" << node->color;
    if(node->left == NULL && node->right == NULL)
        return;
    cout << "(";
    Preorder(node->left);
    cout << ")(";
    Preorder(node->right);
    cout << ")";
}

void RBT::print()
{
    Preorder(root);
}


int main()
{
    class RBT tree;
    int c;
    string s;
    int i = 0;
    int element;
    ifstream myfile1;
    myfile1.open("input.txt", ios::in);
    if(!myfile1)
    {
        cout << "NO INPUT FILE" << endl;
        return 0;
    }
    while(myfile1>>s>>c)
    {
        if(s == "I")
        {
            //cout << "Insert" << endl;
            tree.insert(c);
            tree.print();
            cout << endl;
        }
        else if(s == "F")
        {
            //cout << "Search" << endl;
            if(tree.Search(c))
            {
                cout << "True" << endl;
            }
            else
            {
                 cout << "False" << endl;
            }
        }
        else if(s == "D")
        {
            //cout << "Delete: " << c << endl;
            tree.Delete(c);
            tree.print();
            cout << endl;

        }

    }
    myfile1.close();

    return 0;
}
