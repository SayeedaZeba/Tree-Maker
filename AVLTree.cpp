#include<iostream>
#include<cstdio>
#include<sstream>
#include<algorithm>
#define pow2(n) (1 << (n))
using namespace std;

/*
 * Node Declaration
 */
struct avl_node
{
    int data;
    struct avl_node *left;                          //declaring a node for left side insertion
    struct avl_node *right;                         //declaring a node for right side insertion
}*root;

/*
 * Class Declaration
 */
class avlTree
{
    public:
        int height(avl_node *);                     //integer method for height of the avl tree
        int diff(avl_node *);                       //integer method for difference between left and right side heights
        avl_node *rr_rotation(avl_node *);          //method for RR rotation            
        avl_node *ll_rotation(avl_node *);          //method for LL rotation  
        avl_node *lr_rotation(avl_node *);          //method for LR rotation  
        avl_node *rl_rotation(avl_node *);          //method for RL rotation  
        avl_node* balance(avl_node *);              //method to balance the tree
        avl_node* insert(avl_node *, int );         //method to insert the elements into the tree
        void display(avl_node *, int);              //method to display the tree

        avlTree()                                   //constructor to initialize the node to NULL
        {
            root = NULL;
        }
};

/*
 * Height of AVL Tree
 */
int avlTree::height(avl_node *temp)                 
{
    int h = 0;
    if (temp != NULL)
    {
        int l_height = height (temp->left);         //height towards the left of the tree
        int r_height = height (temp->right);        //height towards the right of the tree
        int max_height = max (l_height, r_height);  //choosing the max value between the left and right heights
        h = max_height + 1;                         //adding 1 to the max height obtained
    }
    return h;
}

/*
 * Height Difference
 */
int avlTree::diff(avl_node *temp)
{
    int l_height = height (temp->left);             //height towards the left of the tree         
    int r_height = height (temp->right);            //height towards the right of the tree
    int b_factor= l_height - r_height;              //difference between the left and right heights
    return b_factor;
}
/*
 * Right- Right Rotation
 */
avl_node *avlTree::rr_rotation(avl_node *parent)    
{
    avl_node *temp;                                 //creating a temporary node
    temp = parent->right;                           //storing the value from the right side of the parent node
    parent->right = temp->left;                     //replacing the value on the right side with the value on the left side
    temp->left = parent;                            //replacing the value on the left side with the parent node 
    return temp;                                    //returning the modified node
}
/*
 * Left- Left Rotation
 */
avl_node *avlTree::ll_rotation(avl_node *parent)
{
    avl_node *temp;                                 //creating a temporary node
    temp = parent->left;                            //storing the value from the left side of the parent node
    parent->left = temp->right;                     //replacing the value on the left side with the value on the right side
    temp->right = parent;                           //replacing the value on the right side with the parent node 
    return temp;                                    //returning the modified node
}

/*
 * Left - Right Rotation
 */
avl_node *avlTree::lr_rotation(avl_node *parent)
{
    avl_node *temp;                                 //creating a temporary node
    temp = parent->left;                            //storing the value from the left side of the parent node
    parent->left = rr_rotation (temp);              //performing RR rotation on the node and storing it on the left side
    return ll_rotation (parent);                    //performing LL rotation and returning the modified node
}

/*
 * Right- Left Rotation
 */
avl_node *avlTree::rl_rotation(avl_node *parent)
{
    avl_node *temp;                                 //creating a temporary node
    temp = parent->right;                           //storing the value from the right side of the parent node
    parent->right = ll_rotation (temp);             //performing LL rotation on the node and storing it on the right side
    return rr_rotation (parent);                    //performing RR rotation and returning the modified node
}

/*
 * Balancing AVL Tree
 */
avl_node *avlTree::balance(avl_node *temp)
{
    int bal_factor = diff (temp);                   //retrieving the height difference value
    if (bal_factor > 1)                             //if height difference is greater than 1
    {
        if (diff (temp->left) > 0)                  //if height difference on left node is greater than 0
            temp = ll_rotation (temp);              //perform LL rotation
        else
            temp = lr_rotation (temp);              //perform RR rotation
    }
    else if (bal_factor < -1)                       //if height difference is lesser than -1
    {
        if (diff (temp->right) > 0)                 //if height difference on right node is greater than 0
            temp = rl_rotation (temp);              //perform RL rotation
        else
            temp = rr_rotation (temp);              //perform RR rotation
    }
    return temp;
}

/*
 * Insert Element into the tree
 */
avl_node *avlTree::insert(avl_node *root, int value)
{
    if (root == NULL)                               //if the tree is empty
    {
        root = new avl_node;                        //add a new node to the root
        root->data = value;                         //store the value in the data
        root->left = NULL;                          //making the left value null
        root->right = NULL;                         //making the right value null
        return root;                                //return the added node
    }
    else if (value < root->data)                    //if the input value is lesser than the root value
    {
        root->left = insert(root->left, value);     //go towards the left side and check the root again (insert operation)
        root = balance (root);                      //balance the tree with the new added node
    }
    else if (value >= root->data)                   //if the input value is greater than the root value           
    {
        root->right = insert(root->right, value);   //go towards the right side and check the root again (insert operation)
        root = balance (root);                      //balance the tree with the new added node
    }
    return root;                                    
}

/*
 * Display AVL Tree
 */
void avlTree::display(avl_node *ptr, int level)
{
    int i;
    if (ptr!=NULL)                                  //if the tree is not empty
    {
        display(ptr->right, level + 1);             //perform the display operation for the right side value
        printf("\n");   
        if (ptr == root)                            //if the value is the root value
        cout<<"Root -> ";
        for (i = 0; i < level && ptr != root; i++)
            cout<<"        ";
        cout<<ptr->data;                            //print the value
        display(ptr->left, level + 1);              //perform the display operation for the left side value
    }
}
