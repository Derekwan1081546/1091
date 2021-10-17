// xtree internal header
#define red Color::Red
#define black Color::Black
using std::swap;

#ifndef XTREE
#define XTREE

enum class Color{ Red, Black }; // colors for link to parent

template< typename Ty >
struct TreeNode
{
   using NodePtr = TreeNode *;
   using value_type = Ty;

   NodePtr    left;   // left subtree, or smallest element if head
   NodePtr    parent; // parent, or root of tree if head
   NodePtr    right;  // right subtree, or largest element if head
   Color      color;  // Red or Black, Black if head
   bool       isNil;  // true only if head (also nil) node
   value_type myval;  // the stored value, unused if head
};

// CLASS TEMPLATE TreeVal
template< typename Ty >
class TreeVal
{
public:
   using NodePtr = TreeNode< Ty > *;

   using value_type = Ty;
   using size_type  = size_t;

   TreeVal()
      : myHead( new TreeNode< value_type > ),
        mySize( 0 )
   {
      myHead->left = myHead;
      myHead->parent = myHead;
      myHead->right = myHead;
      myHead->color = Color::Black;
      myHead->isNil = true;
   }

   ~TreeVal()
   {
      clear( myHead->parent );
      delete myHead;
   }

   // Removes all elements from the set object (which are destroyed)
   void clear( TreeNode< value_type > *node )
   {
      if( !node->isNil ) // node is not an external node
      {
         clear( node->left );
         clear( node->right );
         delete node;
      }
   }

   // rebalance for insertion
   void reBalance( TreeNode< value_type > *node )
   {  // node->parent cannot be the root
       TreeNode<value_type>* pu = node->parent;
       TreeNode<value_type>* gu = pu->parent;
       if ((pu == gu->left && (gu->right)->color == Color::Red) || (pu == gu->right && (gu->left)->color == Color::Red))
       {
           pu->color = Color::Black;

           if (pu == gu->left)//LLr and LRr 
               (gu->right)->color = Color::Black;
           else//RLr and RRr
               (gu->left)->color = Color::Black;

           if (gu->parent != myHead)//if gu is not the root 
           {
               gu->color = Color::Red;
               if ((gu->parent)->color == Color::Red)
                   reBalance(gu);
           }
       }
       else
       {
           if (node == pu->left && pu == gu->left && (gu->right)->color == Color::Black)//LLb
           {
               pu->color = Color::Black;
               gu->color = Color::Red;
               LLRotation(pu);
           }
           if (node == pu->left && pu == gu->right && (gu->left)->color == Color::Black)//RLb
           {
               node->color = Color::Black;
               gu->color = Color::Red;
               RLRotation(node);
           }
           if (node == pu->right && pu == gu->left && (gu->right)->color == Color::Black)//LRb
           {
               node->color = Color::Black;
               gu->color = Color::Red;
               LRRotation(node);
           }
           if (node == pu->right && pu == gu->right && (gu->left)->color == Color::Black)//RRb
           {
               pu->color = Color::Black;
               gu->color = Color::Red;
               RRRotation(pu);
           }
       }
   }

   // rotate right at g, where p = g->left and node = p->left
   //void set< Kty >::LLbRotation( TreeNode< value_type > *node )
   void LLRotation( TreeNode< value_type > *p )
   {
       TreeNode<value_type>* gu = p->parent;

       if (gu->parent == myHead)//gu is the root
           myHead->parent = p;
       else
       {
           if (gu == (gu->parent)->left)
               (gu->parent)->left = p;
           else
               (gu->parent)->right = p;
       }
       p->parent = gu->parent;

       gu->left = p->right;

       if (p->right != myHead)
           (p->right)->parent = gu;

       gu->parent = p;
       p->right = gu;
   }

   // LR rotation; p = g->left and node = p->right
   void LRRotation( TreeNode< value_type > *node )
   {    // LRb rotation

       RRRotation(node); // rotate left at p first
       LLRotation(node); // then rotate right at g

       /*TreeNode<value_type>* pu = node->parent;
       TreeNode<value_type>* gu = pu->parent;

       if (gu->parent == myHead)
           myHead->parent = node;
       else
       {
           if (gu == (gu->parent)->left)
               (gu->parent)->left = node;
           else
               (gu->parent)->right = node;
       }

       node->parent = gu->parent;
       gu->left = node->right;

       if (node->right != myHead)
           (node->right)->parent = gu;

       node->right = gu;
       gu->parent = node;

       pu->right = node->left;
       if (node->left != myHead)
           (node->left)->parent = pu;

       node->left = pu;
       pu->parent = node;*/

   }

   // RL rotation; p = g->right and node = p->left
   void RLRotation( TreeNode< value_type > *node )
   {   // RLb rotation

       LLRotation(node); // rotate right at p first
       RRRotation(node); // then rotate left at g

       //TreeNode<value_type>* pu = node->parent;
       //TreeNode<value_type>* gu = pu->parent;

       //if (gu->parent == myHead)// g is the root
       //    myHead->parent = node;
       //else
       //{
       //    if (gu == (gu->parent)->left)
       //        (gu->parent)->left = node;
       //    else
       //        (gu->parent)->right = node;
       //}

       //node->parent = gu->parent;
       //gu->right = node->left;

       //if (node->left != myHead)
       //    (node->left)->parent = gu;

       //node->left = gu;
       //gu->parent = node;

       //pu->left = node->right;
       //if (node->right != myHead)
       //    (node->right)->parent = pu;

       //node->right = pu;
       //pu->parent = node;

   }

   // rotate left at g, where p = g->right and node = p->right
   //void set< Kty >::RRbRotation( TreeNode< value_type > *node )
   void RRRotation( TreeNode< value_type > *p )
   {
       TreeNode<value_type>* gu = p->parent;

       if (gu->parent == myHead)// gu is the root
           myHead->parent = p;
       else
       {
           if (gu == (gu->parent)->left)
               (gu->parent)->left = p;
           else
               (gu->parent)->right = p;
       }
       p->parent = gu->parent;

       gu->right = p->left;
       if (p->left != myHead)
           (p->left)->parent = gu;

       gu->parent = p;
       p->left = gu;
   }

   // erase node provided that the degree of node is at most one
   void eraseDegreeOne( TreeNode< value_type > *node )
   {
       TreeNode<value_type>* p = node->parent;
       TreeNode<value_type>* c = node->left == myHead ? node->right : node->left;
       // Simple Case 3 -> M and C are black, and M is the root
       if (node->color == Color::Black && c->color == Color::Black && p == myHead)//node is the root => let c be the new root
       {
           myHead->parent = c;
           c->parent = myHead;
       }
       else
       {
           // Simple Case 1 -> M is red or M is a leaf node : delete M and connect P and C
           // connect P and C
           //node == p->left ? p->left = c : p->right = c;
           if (node == p->left)
               p->left = c;
           else
               p->right = c;
           //if (!c->isNil) c->parent = p;
           if (c != myHead)
               c->parent = p;

           if (node->color == Color::Black && c->color == Color::Black && p != myHead) // Complex Case -> M and C are black, and M is not the root : connect P and C, then rebalance
               fixUp(c, p);
           else if (node->color == Color::Black) // Simple Case 2 -> M is black, C is red : delete M, connect P and C, and make C black
               c->color = Color::Black;
       }

       delete node;
       --mySize;

      // // p -> M's parent, if M is the root, p is myHead
      // // child -> M's only child, if M doesn't have any child, C is the nil node
      // TreeNode<value_type>* child = node->left->isNil ? node->right : node->left;
      // TreeNode<value_type>* p = node->parent;

      // // Simple Case 3 -> M and C are black, and M is the root
      // if (node->color == Color::Black && child->color == Color::Black && p->isNil)
      // {
      //     // delete M and make C be the root
      //     myHead->parent = child;
      //     child->parent = myHead;
      //     delete node;
      //     --mySize;
      //     return;
      // }


      // // Simple Case 1 -> node is red or node is a leaf node : delete node and connect P and C
      // node == p->left ? p->left = child : p->right = child;
      // if (!child->isNil) child->parent = p;

      // // Simple Case 2 -> node is black, C is red : delete node, connect P and C, and make C black
      // if (node->color == Color::Black && child->color == Color::Red)
      //     child->color = Color::Black;

      // // Complex Case -> node and C are black, and node is not the root : connect P and C, then rebalance
      // if (node->color == Color::Black && child->color == Color::Black && !p->isNil)
      //     fixUp(child, p);

      //delete node;
      //--mySize;


      //if (node == myHead->parent)//if node is the root
       //{
       //    //set child to be the new root
       //    child->parent = myHead;
       //    child->color = Color::Black;
       //    myHead->parent = child;

       //    if (myHead->left == node)
       //        myHead->left = child;
       //    if (myHead->right == node)
       //        myHead->right = child;
       //}
       //else
       //{
       //    //node is the node with largest key
       //    if (node == myHead->right)
       //    {
       //        if (node->left != myHead)
       //            myHead->right = child;
       //        else
       //            myHead->right = p;
       //        p->right = node->right;
       //    }
       //    else if (node == myHead->left)
       //    {
       //        if (node->right != myHead)
       //            myHead->left = child;
       //        else
       //            myHead->left = p;
       //        p->left = node->left;
       //    }
       //    else
       //    {
       //        if (child == myHead)//degree 0
       //        {
       //            if (node == p->left)
       //                p->left = myHead;
       //            else
       //                p->right = myHead;
       //            
       //        }
       //        else//degree 1
       //        {
       //            if (node == p->left)
       //                p->left = child;
       //            else
       //                p->right = child;
       //        }
       //    }

       //}




      //// refer to the video of class
      // // M -> the node need to delete
      // // P -> M's parent, if M is the root, P is myHead
      // // C -> M's only child, if M doesn't have any child, C is the nil node
      //TreeNode< value_type >* M = node;
      //TreeNode< value_type >* P = node->parent;
      //TreeNode< value_type >* C = node->left->isNil ? node->right : node->left;
      //// Simple Case 3 -> M and C are black, and M is the root
      //if (M->color ==Color::Black && C->color == Color::Black && P->isNil)
      //{   // delete M and make C be the root
      //    myHead->parent = C;
      //    C->parent = myHead;
      //    delete M;
      //    --mySize;
      //    return;
      //}
      //// Simple Case 1 -> M is red or M is a leaf node : delete M and connect P and C
      //// connect P and C
      //M == P->left ? P->left = C : P->right = C;
      //if (!C->isNil) C->parent = P;
      //// Complex Case -> M and C are black, and M is not the root : connect P and C, then rebalance
      //if (M->color == Color::Black && C->color == Color::Black && !P->isNil) fixUp(C, P);

      //// Simple Case 2 -> M is black, C is red : delete M, connect P and C, and make C black
      //if (M->color == Color::Black && C->color == Color::Red) C->color = Color::Black;
      //delete M;
      //--mySize;
   }

   // rebalance for deletion
   void fixUp( TreeNode< value_type > *N, TreeNode< value_type > *P )
   {
       if (N->color == Color::Red)
           N->color = Color::Black;
       else
       {
           if (N != myHead->parent)// N is not the root
           {
               while (true)
               {
                   TreeNode<value_type>* SR;
                   TreeNode<value_type>* SL;
                   TreeNode<value_type>* S;

                   if (N == P->left)
                   {
                       S = P->right;
                       SL = S->left;
                       SR = S->right;
                   }
                   else
                   {
                       S = P->left;
                       SR = S->left;
                       SL = S->right;
                   }

                   if (S->color == Color::Red)// Case 1
                   {
                       S->color = Color::Black;
                       P->color = Color::Red;
                       if (N == P->left)
                           RRRotation(S);//rotate left at p
                       else
                           LLRotation(S);//rotate right at p
                   }
                   else//s->color == Color::Black
                   {
                       if (SR->color == Color::Red) // Case 2
                       {
                           S->color = P->color;
                           P->color = Color::Black;
                           SR->color = Color::Black;
                           if (N == P->left)
                               RRRotation(S);//rotate left at p
                           else
                               LLRotation(S);//rotate right at p
                           //twoTraversals();//add
                           //system("pause");//add
                           return;
                       }
                       else // SR->color == Color::Black
                       {
                           if (SL->color == Color::Red) //Case 3
                           {
                               S->color = Color::Red;
                               SL->color = Color::Black;
                               if (N == P->left)
                                   LLRotation(SL);
                               else
                                   RRRotation(SL);
                           }
                           //SL->color = Color::Black;
                           else //SL->color == Color::Black
                           {
                               if (P->color == Color::Red)// Case 4
                               {
                                   // Just exchange the colors of S and of P
                                   P->color = Color::Black;
                                   S->color = Color::Red;
                                   return;
                               }
                               else//P->color == Color::Black Case 5
                               {
                                   if (S != myHead)
                                       S->color = Color::Red;
                                   if (P == myHead->parent)//If P is the root, we are done
                                       return;
                                   else
                                   {
                                       N = P;//proceed;
                                       P = P->parent;
                                   }
                                   //twoTraversals();//add
                                   //system("pause");//add
                               }
                           }
                       }
                   }
               }
           }
       }

       //TreeNode< value_type >* S = N == P->left ? P->right : P->left; // N's sibling

       //// Case 1
       //if (S->color == red && N == P->left)
       //{   // Case 1.1 -> S is red and N is P's left child
       //    swap(P->color, S->color);
       //    RRRotation(S); // rotate left at P
       //    // update S, then go to Case 2.1, 3.1, or 4
       //}
       //if (S->color == red && N == P->right)
       //{   // Case 1.2 -> S is red and N is P's right child
       //    swap(P->color, S->color);
       //    LLRotation(S); // rotate right at P
       //    // update S, then go to Case 2.2, 3.2, or 4
       //}

       //// update S
       //S = N == P->left ? P->right : P->left;

       //// Case 3
       //if (S->color == black && S->right->color == black && N == P->left && S->left->color == red)
       //{   // Case 3.1 -> S and SR are black, N is P's left child, but SL is red
       //    swap(S->color, S->left->color);
       //    LLRotation(S->left); // rotate right at S
       //    // update S, then go to Case 2.1
       //}
       //if (S->color == black && S->left->color == black && N == P->right && S->right->color == red)
       //{   // Case 3.2 -> S and SL are black, N is P's right child, but SR is red
       //    swap(S->color, S->right->color);
       //    RRRotation(S->right); // rotate left at S
       //    // update S, then go to Case 2.2
       //}

       //// update S
       //S = N == P->left ? P->right : P->left;

       //// Case 2
       //if (S->color == black && S->right->color == red && N == P->left)
       //{   // Case 2.1 -> S is black, SR is red and N is P's left child
       //    swap(P->color, S->color);
       //    S->right->color = black;
       //    RRRotation(S); // rotate left at P
       //    return;
       //}
       //if (S->color == black && S->left->color == red && N == P->right)
       //{   // Case 2.2 -> S is black, SL is red and N is the right child of P
       //    swap(P->color, S->color);
       //    S->left->color = black;
       //    LLRotation(S); // rotate right at P
       //    return;
       //}

       //// Case 4 -> S, SR and SL are black, but P is red
       //if (S->color == black && S->right->color == black && S->left->color == black && P->color == red)
       //{   // Just exchange the colors of S and of P
       //    swap(S->color, P->color);
       //    return;
       //}

       //// Case 5 -> S, SR, SL and P are black
       //if (S->color == black && S->right->color == black && S->left->color == black && P->color == black)
       //{
       //    S->color = red;
       //    fixUp(P, P->parent);
       //}
   }

   // preorder traversal and inorder traversal
   void twoTraversals()
   {
      cout << "Preorder sequence:\n";
      preorder( myHead->parent );

      cout << "\nInorder sequence:\n";
      inorder( myHead->parent );
      cout << endl;
   }

   // preorder traversal
   void preorder( TreeNode< value_type > *node )
   {
      if( node != myHead )
      {
         cout << setw( 5 ) << node->myval << ( node->color == Color::Red ? "R" : "B" );
         preorder( node->left );
         preorder( node->right );
      }
   }

   // inorder traversal
   void inorder( TreeNode< value_type > *node )
   {
      if( node != myHead )
      {
         inorder( node->left );
         cout << setw( 5 ) << node->myval << ( node->color == Color::Red ? "R" : "B" );
         inorder( node->right );
      }
   }

   NodePtr myHead;   // pointer to head node
   size_type mySize; // number of elements
};

// CLASS TEMPLATE Tree
template< typename Traits >
class Tree // ordered red-black tree for map/multimap/set/multiset
{
public:
   using value_type = typename Traits::value_type;

protected:
   using ScaryVal = TreeVal< value_type >;

public:
   using key_type      = typename Traits::key_type;
   using key_compare   = typename Traits::key_compare;

   using size_type       = size_t;

   Tree( const key_compare &parg )
      : keyCompare( parg ),
        scaryVal()
   {
   }

   ~Tree()
   {
   }

   // Extends the container by inserting a new element,
   // effectively increasing the container size by one.
   void insert( const value_type &val )
   {
       if (scaryVal.mySize == 0)
       {
           TreeNode<value_type>* root = new TreeNode<value_type>;
           root->myval = val;
           root->left = scaryVal.myHead;
           root->right = scaryVal.myHead;
           root->isNil = false;
           root->parent = scaryVal.myHead;
           root->color = Color::Black;
           scaryVal.myHead->left = root;
           scaryVal.myHead->parent = root;
           scaryVal.myHead->right = root;
           scaryVal.mySize = 1;
       }
       else
       {
           TreeNode<value_type>* node = scaryVal.myHead->parent;
           while (val != node->myval)
           {
               if (keyCompare(val, node->myval)) //if (val < node->myval)  if (keyCompare(val, node->myval))
               {
                   if (node->left != scaryVal.myHead)
                       node = node->left;
                   else
                       break;
               }
               else
               {
                   if (node->right != scaryVal.myHead)
                       node = node->right;
                   else
                       break;
               }
           }

           if (val != node->myval)
           {
               TreeNode<value_type>* newnode = new TreeNode<value_type>;
               newnode->myval = val;
               newnode->left = scaryVal.myHead;
               newnode->right = scaryVal.myHead;
               newnode->isNil = false;
               newnode->parent = node;
               newnode->color = Color::Red;
               scaryVal.mySize++;
               if (keyCompare(val, node->myval)) //if (val < node->myval) if (keyCompare(val, node->myval))
               {
                   node->left = newnode;
               }
               else
               {
                   node->right = newnode;
               }
               if (scaryVal.myHead->left->myval > val)
                   scaryVal.myHead->left = newnode;
               if (scaryVal.myHead->right->myval < val)
                   scaryVal.myHead->right = newnode;

               if (node->color == Color::Red)
                   scaryVal.reBalance(newnode);
           }
       }
   }

   // Removes from the set container a single element whose value is val
   // This effectively reduces the container size by one, which are destroyed.
   // Returns the number of elements erased.
   size_type erase( const key_type &val )
   {
       TreeNode<key_type>* node = scaryVal.myHead->parent;
       while (node != scaryVal.myHead && val != node->myval)
       {
           if (keyCompare(val, node->myval)) //if (val < node->myval)  if (keyCompare(val, node->myval))
               node = node->left;
           else
               node = node->right;
       }
       if (node == scaryVal.myHead) //not found
           return 0;
       else //found
       {
           if (node->left == scaryVal.myHead || node->right == scaryVal.myHead)//node is the leaf node 
               scaryVal.eraseDegreeOne(node);
           else
           {
               TreeNode<key_type>* rightmin = node->right;
               while (rightmin->left != scaryVal.myHead)//find the minnest number in right side
                   rightmin = rightmin->left;
               node->myval = rightmin->myval;//copy the rightmin number to the node
               scaryVal.eraseDegreeOne(rightmin);
           }
           return 1;
       }
   }

private:
   key_compare keyCompare;
   ScaryVal scaryVal;
};

#endif // XTREE