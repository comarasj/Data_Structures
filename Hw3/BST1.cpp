#include <iostream>
#include <string.h>
#include <fstream>

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
            cout << "Removed phonebook entry" << endl;
        }
        else
        {
            cout << "Person not found in Phonebook" << endl;
        }
    }

    Node *recursiveRemove(Node *root, string name)
    {
     if(root==NULL) return root;
    else if(name<root->getName()) 
        root->left = recursiveRemove(root->left, name);
    else if (name> root->getName())
        root->right = recursiveRemove(root->right, name);
    else
    {
        //No child
        if(root->right == NULL && root->left == NULL)
        {
            delete root;
            root = NULL;   
        }
        //One child 
        else if(root->right == NULL)
        {
            Node* temp = root;
            root= root->left;
            delete temp;
        }
        else if(root->left == NULL)
        {
            Node* temp = root;
            root= root->right;
            delete temp;
        }
        //two child
        else
        {
            Node* temp = FindMax(root->left);
            root->getName() = temp->getName();
            root->left = recursiveRemove(root->left, temp->getName());
        }
    }
    return root;
}
Node* FindMax(Node* root)
{
    if(root==NULL)
    return NULL;

    while(root->right != NULL)
    {
        root = root->right;
    }
    return root;
}
};
/* Attempt at writing to a file, not entirely sure what im doing
void write(Node* n){
fstream New("phonebook.txt");
write_node(n, New);
New.close()
}
void write_node(Node* n, fstream& file){
if(!n){
 return;
}
write_node(n->left, file);
file << n*>data;
write_node(n->right, file);
}
*/
void GUI()
{   
    int menu;
    string fName;
    string lName; 
    string phoneN;
    BST Phonebook("123123", "Stephen", "Comarata");
   

while(menu != 6){
cout << "Enter 1. to ADD to phonebook" << endl <<  "Enter 2. to DELETE from phonebook" << endl << "Enter 3. to FIND from phonebook" << endl << "Enter 4. to CHANGE phone number entry" << endl << "Enter 5. to DISPLAY phonebook" << endl << "Enter 6. to QUIT" << endl;
cin >> menu;
if(menu == 1){
cout << "First name to be added? : " << endl;
cin >> fName;
cout << "Last name to be added? : " << endl;
cin >> lName;
cout << "Phone number of person? : " << endl;
cin >> phoneN;
Phonebook.insert(phoneN, fName, lName);
}

if(menu == 2){
cout << "First name? : " << endl;
cin >> fName;
cout << "Last name? : " << endl;
cin >> lName;
Phonebook.remove(fName,lName);
}

if(menu == 3){
cout << "First name? : " << endl;
cin >> fName;
cout << "Last name? : " << endl;
cin >> lName;
Phonebook.search(fName,lName);
}

if(menu == 4){
cout << "First name? : " << endl;
cin >> fName;
cout << "Last name? : " << endl;
cin >> lName;
cout << "new phone number? : " << endl;
cin >> phoneN;
Phonebook.change(fName,lName,phoneN);
}

if(menu == 5){
Phonebook.inorderTraversal();
}

}



}

int main()
{
    GUI();
    
}

//First name and Last name must start with capital letter -- implement in menu
