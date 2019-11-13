/**
 * Stephen Comarata and Dylan Wheeler
 * EECE 4040 - Adv Data Structures and Algorithms
 * Homework 4 - Topological Sort and DAGs
 * November 15, 2019 
 **/

#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>

using namespace std;

const int SIZE = 500;

string tasks[SIZE];
int tasks_size = 0;

class Node
{
private:
public:
    Node *next;
    int value;
    Node(int _value)
    {
        value = _value;
        next = nullptr;
    }
};

class Diagraph
{
private:
public:
    Node *adjList[SIZE];
    int size;
    Diagraph()
    {
        size = 0;
    }

    void addVertice()
    {
        adjList[size] = new Node(size);
        size++;
    }

    void addEdge(int src, int dest)
    {
        if (size < src || size < dest)
        {
            cout << "source or destination nodes do not exist" << endl;
        }
        else
        {
            recursiveAddEdge(adjList[src], dest);
        }
    }

    void recursiveAddEdge(Node *root, int dest)
    {
        if (root->value == dest)
        {
            cout << "Edge already exists" << endl;
        }
        else if (root->next == nullptr)
        {
            //add edge
            root->next = new Node(dest);
        }
        else
        {
            //recurse
            recursiveAddEdge(root->next, dest);
        }
    }

    void deleteEdge(int src, int dest)
    {
        if (size < src || size < dest)
        {
            cout << "source or destination nodes do not exist" << endl;
        }
        else
        {
            Node *temp = adjList[src];
            Node *prev;

            while (temp != nullptr && temp->value != dest)
            {
                prev = temp;
                temp = temp->next;
            }

            if (temp == nullptr)
            {
                cout << "edge does not exist" << endl;
            }
            else
            {
                prev->next = temp->next;
                delete temp;
            }
        }
    }

    void showGraph()
    {
        cout << "-----Digraph-----" << endl;
        for (int i = 0; i < size; i++)
        {
            cout << adjList[i]->value;
            if (adjList[i]->next != nullptr)
            {
                recursiveShowGraph(adjList[i]->next);
            }
            cout << endl;
        }
    }

    void recursiveShowGraph(Node *root)
    {
        cout << " -> " << root->value;
        if (root->next != nullptr)
        {
            recursiveShowGraph(root->next);
        }
    }
};

void test()
{
    Diagraph digraph;
    for (int i = 0; i < 5; i++)
    {
        digraph.addVertice();
    }
    digraph.addEdge(1, 2);
    digraph.addEdge(2, 1);
    digraph.addEdge(3, 4);
    digraph.addEdge(1, 4);
    digraph.addEdge(1, 4);
    digraph.showGraph();
    digraph.deleteEdge(1, 4);
    digraph.showGraph();
}

int main()
{
    test();
    return 0;
}