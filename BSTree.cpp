/*
 * C++ Program To Implement BST
 */
# include <iostream>
# include <cstdlib>
using namespace std;
/*
 * Node Declaration
 */
struct node
{
    int info;
    struct node *left;										//declaring a node for left side insertion
    struct node *right;										//declaring a node for right side insertion
}*rootbs;

/*
 * Class Declaration
 */
class BST
{
    public:
        void insert(node*,node*);						 	//method to insert node
        void display(node *, int);							//method to display node
        BST()
        {
            rootbs = NULL;									//initializing to NULL
        }
};


/*
 * Inserting Element into the Tree
 */
void BST::insert(node *tree, node *newnode)
{
    if (rootbs == NULL)										//if the tree is empty				
    {
        rootbs = new node;									//creating new node
        rootbs->info = newnode->info;						//store the value in the data
        rootbs->left = NULL;								//making the left value null
        rootbs->right = NULL;								//making the right value null
        cout<<"Root Node is Added"<<endl;
        return;
    }
    if (tree->info == newnode->info)						//if input value already in the tree
    {
        cout<<"Element already in the tree"<<endl;
        return;
    }
    if (tree->info > newnode->info)							//if input is lesser than the tree value
    {
        if (tree->left != NULL)								//if the left of the tree value is NULL			
        {
            insert(tree->left, newnode);					//perform insert operation on the left node
        }	
        else
        {
            tree->left = newnode;							//create a new node on the left
            (tree->left)->left = NULL;						//make the left of the left of the tree value NULL
            (tree->left)->right = NULL;						//make the right of the left of the tree value NULL
            cout<<"Node Added To Left"<<endl;
            return;
        }
    }
    else
    {
        if (tree->right != NULL)							//if the right of the tree value is NULL	
        {
            insert(tree->right, newnode);					//perform insert operation on the right node
        }
        else
        {
            tree->right = newnode;							//create a new node on the left
            (tree->right)->left = NULL;						//make the left of the right of the tree value NULL
            (tree->right)->right = NULL;					//make the right of the right of the tree value NULL
            cout<<"Node Added To Right"<<endl;
            return;
        }
    }
}





/*
 * Display Tree Structure
 */
void BST::display(node *ptr, int level)
{
    int i;
    if (ptr != NULL)										//if the tree is not empty
    {
        display(ptr->right, level+1);						//perform the display operation for the right side value
        cout<<endl;
        if (ptr == rootbs)									 //if the value is the root value
            cout<<"Root->:  ";
        else
        {
            for (i = 0;i < level;i++)
                cout<<"       ";
        }
        cout<<ptr->info;									//print the value
        display(ptr->left, level+1);						//perform the display operation for the left side value
    }
}