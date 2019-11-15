/**
 * Stephen Comarata and Dylan Wheeler
 * EECE 4040 - Adv Data Structures and Algorithms
 * Homework 4 - Topological Sort and DAGs
 * November 15, 2019 
 **/

#include <iostream>
#include <string.h>
#include <list>
#include <stack>

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
    void topologicalSortUtil(int v, bool visited[], stack<int> &Stack)
    {

        // Mark the current node as visited.
        visited[v] = true;
        if (adjList[v]->next != nullptr)
        {
            Node *temp = adjList[v]->next;
            if (!visited[temp->value])
            {
                topologicalSortUtil(temp->value, visited, Stack);
            }
        }
        // Push current vertex to stack which stores result
        Stack.push(v);
    }

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
        if (size <= src || size <= dest)
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
        cout << "-----Adj List-----" << endl;
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
    void performTopologicalSort()
    {
        stack<int> stk;
        bool vis[SIZE];

        for (int i = 0; i < size; i++)
            vis[i] = false; //initially all nodes are unvisited

        for (int i = 0; i < size; i++)
            if (!vis[i]) //when node is not visited
                topologicalSortUtil(i, vis, stk);

        while (!stk.empty())
        {
            cout << "-----Topological Sort-----" << endl;
            cout << stk.top() << " ";
            stk.pop();
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
    digraph.performTopologicalSort();
}

void showTasks()
{
    for (int i = 0; i < tasks_size; i++)
    {
        cout << i << ". " << tasks[i] << endl;
    }
}

void userInterface()
{
    Diagraph digraph;
    int menu = 0;
    cout << "Digraph Program" << endl;
    while (menu != 6)
    {
        cout << endl;
        cout << "Enter 0. to add a vertice" << endl
             << "Enter 1. to add an edge" << endl
             << "Enter 2. to delete an edge" << endl
             << "Enter 3. to show the adj list of the graph" << endl
             << "Enter 4. to show the topological sort of the graph" << endl
             << "Enter 5. to show the list of tasks" << endl
             << "Enter 6. to exit" << endl;
        cin >> menu;
        if (menu == 0)
        {
            string task;
            cout << "Enter the name of task: ";
            cin >> task;
            tasks[tasks_size] = task;
            tasks_size++;
            digraph.addVertice();
        }
        else if (menu == 1)
        {
            int src, dest;
            cout << "Enter the number of the source vertice: ";
            cin >> src;
            cout << "Enter the number of the destination vertice: ";
            cin >> dest;
            digraph.addEdge(src, dest);
        }
        else if (menu == 2)
        {
            int src, dest;
            cout << "Enter the number of the source vertice: ";
            cin >> src;
            cout << "Enter the number of the destination vertice: ";
            cin >> dest;
            digraph.deleteEdge(src, dest);
        }
        else if (menu == 3)
        {
            digraph.showGraph();
        }
        else if (menu == 4)
        {
            digraph.performTopologicalSort();
        }
        else if (menu == 5)
        {
            showTasks();
        }
    }
}

int main()
{
    //test();
    userInterface();
    return 0;
}