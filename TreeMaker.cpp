#include<iostream>
#include "AVLTree.cpp"  //this file contains the functionality for avl tree creation
#include "BSTree.cpp"      //this file contains the functionality for binary search tree creation
#include "BTree.cpp"    //this file contains the functionality for btree creation
using namespace std;


main()
{ 
  system("clear");
  avlTree a;            //creating an object of avlTree class
  BST bst;              //creating an object of BST class
  node *temp;           //creating an temporary node
 cout<<"\t\t\t\tTHE TREE MAKER"<<endl<<endl;
 while(1)
 {

  int c,n,e;                
  cout<<endl<<"\t\t\t\t1. ENTER";
  cout<<endl<<"\t\t\t\t2. DISPLAY";
  cout<<endl<<"\t\t\t\t3. EXIT";
  cout<<endl<<"\t\t\t\tWhat would you like to do? ";    //Displaying the options to the user
  cin>>c;
  switch(c)
  {
   case 1: cout<<endl<<"How many elements do you want to enter: ";      //If user chooses to enter, ask how many elements they want to enter?
           cin>>e;
           for(int i=0;i<e;i++)
           {
            cout<<endl<<"Enter the number: ";                           //Taking in the input values
   cin>>n;
            //avl insertion
            root=a.insert(root,n);                                      
            //btree insertion
            eatline();
            insert(n);
            //bst insertion
            temp=new node;
            temp->info=n;
            bst.insert(rootbs,temp);
           }

            break;

   case 2:
           //AVL display
           cout<<endl<<endl<<endl<<" \t\tAVL TREE: "<<endl;
           a.display(root,1);
           //Btree display
           cout<<endl<<endl<<endl<<"\t\t BTREE: "<<endl;
           display(rootbt,0);
           //BST display
           cout<<endl<<endl<<endl<<"\t\t BST: "<<endl;
           bst.display(rootbs,1);
           cout<<endl;

           break;
case 3: exit(1);
            break;
   default: cout<<endl<<"Wrong input";                                  //If they enter an invalid option
   }
  }
}