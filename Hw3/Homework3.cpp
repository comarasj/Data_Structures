/** EECE 4040 
 * Homework 3 Binary Search Tree Phonebook Project
 * Stephen Comarata and Dylan Wheeler
 * */
#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

class Person
{
public:
    Person *left;
    Person *right;
    string phoneNumber;
    string lastName;
    string firstName;

    Person(string _phoneNumber, string _firstName, string _lastName)
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

class BinarySearchTree
{
private:
    Person *root;
    int size;

public:
    BinarySearchTree(string _phoneNumber, string _firstName, string _lastName)
    {
        root = new Person(_phoneNumber, _firstName, _lastName);
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

    void inorder(Person *n)
    {
        if (n != nullptr)
        {
            inorder(n->left);
            cout << n->lastName << "   " << n->firstName << "   " << n->phoneNumber << endl;
            inorder(n->right);
        }
    }

    void preorder(Person *n)
    {
        if (n != nullptr)
        {
            cout << n->lastName << " " << n->firstName << " " << n->phoneNumber << endl;
            preorder(n->left);
            preorder(n->right);
        }
    }

    void insert(string _phoneNumber, string _firstName, string _lastName)
    {
        Person *n = new Person(_phoneNumber, _firstName, _lastName);
        recursiveInsert(n, root);
        size++;
    }

    void recursiveInsert(Person *n, Person *root)
    {
        if (root == nullptr)
        {
            root = n;
        }
        else
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
    }

    void search(string _firstName, string _lastName)
    {
        string name = _lastName + _firstName;
        Person *n = recursiveSearch(root, name);
        if (n != nullptr)
        {
            cout << "Found: " << n->lastName << " " << n->firstName << " " << n->phoneNumber << endl;
        }
        else
        {
            cout << "Person not found in Phonebook" << endl;
        }
    }

    Person *recursiveSearch(Person *root, string name)
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
        Person *n = recursiveSearch(root, name);
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
        Person *n = recursiveRemove(root, name);
        if (n != nullptr)
        {
            size--;
            cout << "Removed phonebook entry" << endl;
        }
        else
        {
            cout << "Person not found in Phonebook" << endl;
        }
    }

    Person *recursiveRemove(Person *root, string name)
    {
        if (root == NULL)
            return root;
        else if (name < root->getName())
            root->left = recursiveRemove(root->left, name);
        else if (name > root->getName())
            root->right = recursiveRemove(root->right, name);
        else
        {
            //No child
            if (root->right == NULL && root->left == NULL)
            {
                delete root;
                root = NULL;
            }
            //One child
            else if (root->right == NULL)
            {
                Person *temp = root;
                root = root->left;
                delete temp;
            }
            else if (root->left == NULL)
            {
                Person *temp = root;
                root = root->right;
                delete temp;
            }
            //two child
            else
            {
                Person *temp = FindMax(root->left);
                root->getName() = temp->getName();
                root->left = recursiveRemove(root->left, temp->getName());
            }
        }
        return root;
    }
    Person *FindMax(Person *root)
    {
        if (root == NULL)
            return NULL;

        while (root->right != NULL)
        {
            root = root->right;
        }
        return root;
    }

    void write()
    {
        ofstream myfile("phonebook.txt", ios::trunc);
        recursiveWrite(root, myfile);
        myfile.close();
    }

    void recursiveWrite(Person *n, ofstream &myfile)
    {
        if (n != nullptr)
        {
            //preorder traversal
            myfile << n->lastName << " " << n->firstName << " " << n->phoneNumber << endl;
            recursiveWrite(n->left, myfile);
            recursiveWrite(n->right, myfile);
        }
    }

    void read()
    {
        root->left = nullptr;
        root->right = nullptr;
        ifstream myfile("phonebook.txt");
        string line;
        string delimiter = " ";
        int i = 0;
        while (getline(myfile, line))
        {
            int space = line.find(delimiter);
            string lname = line.substr(0, space);
            line = line.substr(space + 1, line.length());

            space = line.find(delimiter);

            string fname = line.substr(0, space);
            string number = line.substr(space + 1, line.length());
            if (i != 0)
            {
                insert(number, fname, lname);
            }
            else
            {
                i = 1;
                root->setPhoneNumber(number);
                root->setName(fname, lname);
            }
        }
    }
};

void GUI()
{
    int menu;
    string fName;
    string lName;
    string phoneN;
    BinarySearchTree Phonebook("123123", "Stephen", "Comarata");

    while (menu != 6)
    {
        cout << "Enter 0. to LOAD the phonebook from the 'phonebook.txt' file" << endl
             << "Enter 1. to ADD to phonebook" << endl
             << "Enter 2. to DELETE from phonebook" << endl
             << "Enter 3. to FIND from phonebook" << endl
             << "Enter 4. to CHANGE phone number entry" << endl
             << "Enter 5. to DISPLAY phonebook" << endl
             << "Enter 6. to QUIT" << endl;
        cin >> menu;
        if (menu == 0)
        {
            Phonebook.read();
            cout << "====================Phonebook===================" << endl;
            Phonebook.inorderTraversal();
            cout << "================================================" << endl;
        }
        else if (menu == 1)
        {
            cout << "First name to be added? : " << endl;
            cin >> fName;
            cout << "Last name to be added? : " << endl;
            cin >> lName;
            cout << "Phone number of person? : " << endl;
            cin >> phoneN;
            Phonebook.insert(phoneN, fName, lName);
        }

        else if (menu == 2)
        {
            cout << "First name? : " << endl;
            cin >> fName;
            cout << "Last name? : " << endl;
            cin >> lName;
            Phonebook.remove(fName, lName);
        }

        else if (menu == 3)
        {
            cout << "First name? : " << endl;
            cin >> fName;
            cout << "Last name? : " << endl;
            cin >> lName;
            Phonebook.search(fName, lName);
        }

        else if (menu == 4)
        {
            cout << "First name? : " << endl;
            cin >> fName;
            cout << "Last name? : " << endl;
            cin >> lName;
            cout << "new phone number? : " << endl;
            cin >> phoneN;
            Phonebook.change(fName, lName, phoneN);
        }

        else if (menu == 5)
        {
            cout << "====================Phonebook===================" << endl;
            Phonebook.inorderTraversal();
            cout << "================================================" << endl;
        }
    }
    Phonebook.write();
}

int main()
{
    GUI();
}
