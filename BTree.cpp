#include <iostream>
#include <stdlib.h>
#define M 3
#include<cstdio>
using namespace std;
struct nodebt {
    int n; 												// n < M No. of keys in node will always less than order of B tree 
    int keys[M-1]; 										//array of keys
    struct nodebt *p[M];								//(n+1 pointers will be in use) 
}*rootbt=NULL;		

enum KeyStatus { Duplicate,SearchFailure,Success,InsertIt,LessKeys };

void insert(int key);									//insert method	declaration						
void display(struct nodebt *rootbt,int);				//display method declaration
enum KeyStatus ins(struct nodebt *r, int x, int* y, struct nodebt** u);		//Keystatus Ins method declaration
int searchPos(int x,int *key_arr, int n);				//searching method declaration
void eatline(void);										//eatLine method declaration

/*
 * Insert Element into the tree
 */
void insert(int key)
{
    struct nodebt *newnode;
    int upKey;
    enum KeyStatus value;
    value = ins(rootbt, key, &upKey, &newnode);			//input value to be added to the tree
    if (value == Duplicate)								//if value already in the tree
        cout<<endl<<"Key already available\n";
    if (value == InsertIt)								//if value to be inserted
    {
        struct nodebt *uproot = rootbt;							
        rootbt=new struct nodebt;						//new node created			
        rootbt->n = 1;								
        rootbt->keys[0] = upKey;
        rootbt->p[0] = uproot;
        rootbt->p[1] = newnode;
    }
}

/*
 * KeyStatus Insert
 */
enum KeyStatus ins(struct nodebt *ptr, int key, int *upKey,struct nodebt **newnode)
{
    struct nodebt *newPtr, *lastPtr;
    int pos, i, n,splitPos;
    int newKey, lastKey;
    enum KeyStatus value;
    if (ptr == NULL)									//if node is NULL
    {
        *newnode = NULL;
        *upKey = key;
        return InsertIt;
    }
    n = ptr->n;
    pos = searchPos(key, ptr->keys, n);					//obtaining the position 
    if (pos < n && key == ptr->keys[pos])
        return Duplicate;
    value = ins(ptr->p[pos], key, &newKey, &newPtr);
    if (value != InsertIt)
        return value;
    
    if (n < M - 1)										//if keys in node is less than M-1 where M is order of B tree
    {
        pos = searchPos(newKey, ptr->keys, n);			//obtaining the position 
        
        for (i=n; i>pos; i--)							//shifting the key and pointer right for inserting the new key
        {
            ptr->keys[i] = ptr->keys[i-1];
            ptr->p[i+1] = ptr->p[i];
        }
        
        ptr->keys[pos] = newKey;						//key is inserted at exact location
        ptr->p[pos+1] = newPtr;
        ++ptr->n; 										//incrementing the number of keys in node
        return Success;
    }
    
    if (pos == M - 1)									//if keys in nodes are maximum and position of node to be inserted is last
    {
        lastKey = newKey;
        lastPtr = newPtr;
    }
    else 												//if keys in node are maximum and position of node to be inserted is not last
    {
        lastKey = ptr->keys[M-2];
        lastPtr = ptr->p[M-1];
        for (i=M-2; i>pos; i--)
        {
            ptr->keys[i] = ptr->keys[i-1];
            ptr->p[i+1] = ptr->p[i];
        }
        ptr->keys[pos] = newKey;
        ptr->p[pos+1] = newPtr;
    }
    splitPos = (M - 1)/2;
    (*upKey) = ptr->keys[splitPos];

    (*newnode)=new struct nodebt;						//right node after split
    ptr->n = splitPos;									//no. of keys for left splitted node
    (*newnode)->n = M-1-splitPos;						//no. of keys for right splitted node
    for (i=0; i < (*newnode)->n; i++)
    {
        (*newnode)->p[i] = ptr->p[i + splitPos + 1];
        if(i < (*newnode)->n - 1)
            (*newnode)->keys[i] = ptr->keys[i + splitPos + 1];
        else
            (*newnode)->keys[i] = lastKey;
    }
    (*newnode)->p[(*newnode)->n] = lastPtr;
    return InsertIt;
}

/*
 * Display Btree
 */
void display(struct nodebt *ptr, int blanks)
{
    if (ptr)
    {
        int i;
        for(i=1; i<=blanks; i++)
            cout<<" ";
        for (i=0; i < ptr->n; i++)
            cout<<ptr->keys[i]<<" ";
        cout<<"\n";
        for (i=0; i <= ptr->n; i++)
            display(ptr->p[i], blanks+10);
    }
}

/*
 * Search for the position
 */
int searchPos(int key, int *key_arr, int n)
{
    int pos=0;
    while (pos < n && key > key_arr[pos])
        pos++;
    return pos;
}
/*
 * eatLine
 */
void eatline(void) {
  char c;
  cout<<" ";
  while (c=getchar()!='\n') ;
}
