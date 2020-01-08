#include<iostream>

using namespace std;

struct node 
{
    string keyword, meaning;
    struct node *ln, *rn;
};

class Dictionary
{
    node *root;
    public:
        Dictionary();
        node* getRoot();
        void create(string, string);
        node* add(node*, node*);
        void del(string);
        void update(string);
        void search(string);
        void sort(string);
        void displayInorder(node*);
        void displayRevInorder(node*);
        void maxComp(string);
};

Dictionary::Dictionary()
{
    root = NULL;
}

node* Dictionary::getRoot()
{
    return root;
}

void Dictionary::create(string k, string m)
{
    node *nn = new node;
    nn->keyword = k;
    nn->meaning = m;
    nn->ln = NULL;
    nn->rn = NULL;
    
    if(root == NULL)
    {
        root = nn;
    }
    else
   	    add(root, nn);
}

node* Dictionary::add(node *temp, node *nn)
{
    if(temp == NULL)
    {
        temp = nn;
    }
    else
    {
        if(nn->keyword.compare(temp->keyword) < 0)
        {
            temp->ln = add(temp->ln, nn);
        }
        else if (nn->keyword.compare(temp->keyword) > 0)
        {
            temp->rn = add(temp->rn, nn);
        }
        else
        {
            cout << "The keyword already exists. Update the meaning instead.\n\n";
        }
    }
    return temp;
}

void Dictionary::displayInorder(node *cn)
{
    if(cn != NULL)
    {
        displayInorder(cn->ln);
        cout << cn->keyword << ": " << cn->meaning << endl;
        displayInorder(cn->rn);
    }
}

int main()
{
    Dictionary D;
    int ch, maxCmp = 0;
    string k, m;
    do
    {
        cout << "1. Add keyword\n";
        cout << "2. Delete\n";
        cout << "3. Update\n";
        cout << "4. Search\n";
        cout << "5. Display in Alphabetical Order\n";
        cout << "6. Display in reverse Alphabetical Order\n";
        cout << "7. Count maximum number of comparisions for a specific keyword\n";
        cout << "8. Exit\n";
     	cout << "Enter your choice: ";
        cin >> ch;
        cout << endl;
        
        switch(ch)
        {
        	case 1: // add
        		cout << "Enter the keyword: ";
        		cin >> k;
        		cout << "Enter the meaning: ";
        		cin >> m;
        		D.create(k, m);
        		break;
        	case 2: // delete
        		break;
        	case 3: // update
        		break;
        	case 4: // search
        		break;
        	case 5: // display in order
        		D.displayInorder(D.getRoot());
        		break;
        	case 6: // display in rev order
        		break;
        	case 7: // max no of comparisions
        		break;
        	case 8: // exit
        		break;
        	default: // ch out of bound
        		cout << "Please enter your choice between 1 - 8, only!\n\n";
        }
    }while(ch != 8);
    
    return 0;
}

