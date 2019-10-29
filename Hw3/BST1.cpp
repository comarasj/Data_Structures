#include <iostream>
#include <string.h>

using namespace std;

class Node
{
public:
    Node *left;
    Node *right;
    string phoneNumber;
    string lastName;
    string firstName;

    Node(string _phoneNumber, string _firstName, string _lastName)
    {
        phoneNumber = _phoneNumber;
        firstName = _firstName;
        lastName = _lastName;
        left = nullptr;
        right = nullptr;
    }

    string getName()
    {
        return lastName + firstName;
    }

    string getPhoneNumber()
    {
        return phoneNumber;
    }

    void setPhoneNumber(string number)
    {
        phoneNumber = number;
    }

    void setName(string first, string last)
    {
        firstName = first;
        lastName = last;
    }
};

class BST
{
private:
    Node *root;
    int size;

public:
    BST(string _phoneNumber, string _firstName, string _lastName)
    {
        root = new Node(_phoneNumber, _firstName, _lastName);
        int size = 1;
    }

    void inorderTraversal()
    /**
     *  Outputs list in alphabetical order
     **/
    {
        cout << "LastName   FirstName   PhoneNumber" << endl;
        inorder(root);
    }

    void inorder(Node *n)
    {
        if (n != nullptr)
        {
            inorder(n->left);
            cout << n->lastName << "   " << n->firstName << "   " << n->phoneNumber << endl;
            inorder(n->right);
        }
    }

    void insert(string _phoneNumber, string _firstName, string _lastName)
    {
        Node *n = new Node(_phoneNumber, _firstName, _lastName);
        recursiveInsert(n, root);
    }

    void recursiveInsert(Node *n, Node *root)
    {
        if (n->getName() <= root->getName())
        {
            if (root->left == nullptr)
            {
                root->left = n;
            }
            else
            {
                recursiveInsert(n, root->left);
            }
        }
        else
        {
            if (root->right == nullptr)
            {
                root->right = n;
            }
            else
            {
                recursiveInsert(n, root->right);
            }
        }
    }

    void search(string _firstName, string _lastName)
    {
        string name = _lastName + _firstName;
        Node *n = recursiveSearch(root, name);
        if (n != nullptr)
        {
            cout << "Found: " <<  n->lastName << " " << n->firstName << " " << n->phoneNumber << endl;
        }
        else
        {
            cout << "Person not found in Phonebook" << endl;
        }
    }

    Node *recursiveSearch(Node *root, string name)
    {
        if (root == nullptr || root->getName() == name)
        {
            return root;
        }
        else
        {
            if (name <= root->getName())
            {
                return recursiveSearch(root->left, name);
            }
            else
            {
                return recursiveSearch(root->right, name);
            }
        }
    }

    void change(string _firstName, string _lastName, string newNumber)
    {
        string name = _lastName + _firstName;
        Node *n = recursiveSearch(root, name);
        if (n != nullptr)
        {
            n->setPhoneNumber(newNumber);
            cout << "Changed: " << n->lastName << " " << n->firstName << " " << n->phoneNumber << endl;
        }
        else
        {
            cout << "Person not found in Phonebook" << endl;
        }
    }

    void remove(string _firstName, string _lastName)
    {
        string name = _lastName + _firstName;
        Node *n = recursiveRemove(root, name);
        if (n != nullptr)
        {
            cout << "Removed: " << n->lastName << " " << n->firstName << " " << n->phoneNumber << endl;
        }
        else
        {
            cout << "Person not found in Phonebook" << endl;
        }
    }

    Node *recursiveRemove(Node *root, string name)
    {
        if (root == nullptr)
        {
            return root;
        }

        // need more here
    }
};

void test()
{
    BST Phonebook("123456789", "Stephen", "Comarata");
    Phonebook.insert("123456789", "Tyler", "Sasse");
    Phonebook.insert("123456789", "Dylan", "Wheeler");

    Phonebook.inorderTraversal();
    Phonebook.change("Tyler", "Sasse", "987654321");
}

int main()
{
    test();
}

//First name and Last name must start with capital letter -- implement in menu