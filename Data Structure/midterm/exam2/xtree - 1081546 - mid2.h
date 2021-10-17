// xtree internal header

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
	   if ((pu == gu->left && gu->right->color == Color::Red) || (pu == gu->right && gu->left->color == Color::Red))
	   {
		   pu->color = Color::Black;
		   if (pu == gu->left)//LLr and LRr
		   {
			   gu->right->color = Color::Black;
		   }
		   else//RLr and RRr
		   {
			   gu->left->color = Color::Black;
		   }
		   if (gu->parent != myHead)//if gu is not the root 
		   {
			   gu->color = Color::Red;
			   if ((gu->parent)->color == Color::Red)//add
				   reBalance(gu);//add
		   }
	   }
	   else
	   {
		   if (pu == gu->left && node == pu->left && gu->right->color == Color::Black)
		   {
			   pu->color = Color::Black;
			   gu->color = Color::Red;
			   LLRotation(pu);
		   }
		   if (pu == gu->right && node == pu->right && gu->left->color == Color::Black)
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
	   if (gu == gu->parent->left)
	   {
		   gu->parent->left = p;
	   }
	   else
	   {
		   gu->parent->right = p;
	   }
	   p->parent = gu->parent;
	   gu->left = p->right;
	   if (p->right != myHead)
	   {
		   p->right->parent = gu;
	   }
	   p->right = gu;
	   gu->parent = p;
   }

   // rotate left at g, where p = g->right and node = p->right
   //void set< Kty >::RRbRotation( TreeNode< value_type > *node )
   void RRRotation( TreeNode< value_type > *p )
   {
	   TreeNode<value_type>* gu = p->parent;
	   if (gu == gu->parent->left)
	   {
		   gu->parent->left = p;
	   }
	   else
	   {
		   gu->parent->right = p;
	   }
	   p->parent = gu->parent;
	   gu->right = p->left;
	   if (p->left != myHead)
	   {
		   p->left->parent = gu;
	   }
	   p->left = gu;
	   gu->parent = p;
   }

   // erase node provided that the degree of node is at most one
   void eraseDegreeOne( TreeNode< value_type > *node )
   {
	   TreeNode<value_type>* p = node->parent;
	   TreeNode<value_type>* c = node->left == myHead ? node->right : node->left;
	   if (node->color == Color::Black && c->color == Color::Black && p == myHead)
	   {
		   myHead->parent = c;
		   c->parent = myHead;
	   }
	   else
	   {
		   if (p->left == node)
			   p->left = c;
		   else
			   p->right = c;

		   if (c != myHead)
			   c->parent = p;

		   if (node->color == Color::Black && c->color == Color::Black && p != myHead)
			   fixUp(c, p);
		   else if (node->color == Color::Black)
			   c->color = Color::Black;
	   }
	   delete node;
	   --mySize;
   }

   // rebalance for deletion
   void fixUp( TreeNode< value_type > *N, TreeNode< value_type > *P )
   {
	   if (N->color == Color::Red)
	   {
		   N->color = Color::Black;
	   }
	   else
	   {
		   if (N != myHead->parent)
		   {
			   while (true)
			   {
				   TreeNode<value_type>* S;
				   TreeNode<value_type>* SR;
				   TreeNode<value_type>* SL;
				   if (N == P->left)
				   {
					   S = P->right;
					   SR = S->right;
					   SL = S->left;
				   }
				   else
				   {
					   S = P->left;
					   SR = S->left;
					   SL = S->right;
				   }
				   if (S->color == Color::Red)//case 1
				   {
					   P->color = Color::Red;
					   S->color = Color::Black;

					   if (N == P->left)
					   {
						   RRRotation(S);
					   }
					   else
					   {
						   LLRotation(S);
					   }
				   }
				   else
				   {
					   if (SR->color == Color::Red)//case 2
					   {
						   S->color = P->color;
						   P->color = Color::Black;
						   SR->color = Color::Black;

						   if (N == P->left)
						   {
							   RRRotation(S);
						   }
						   else
						   {
							   LLRotation(S);
						   }
						   return;
					   }
					   else
					   {
						   if (SL->color == Color::Red)//case 3
						   {
							   SL->color = Color::Black;
							   S->color = Color::Red;

							   if (N == P->left)
							   {
								   LLRotation(SL);
							   }
							   else
							   {
								   RRRotation(SL);  
							   }
						   }
						   else
						   {
							   if (P->color == Color::Red)//csae 4
							   {
								   P->color = Color::Black;
								   S->color = Color::Red;
								   return;
							   }
							   else//case 5
							   {
								   S->color = Color::Red;
								   if (P->parent == myHead)
									   return;
								   else
								   {
									   N = P;
									   P = P->parent;
								   }

							   }
						   }
					   }
				   }
			   }
		   }
	   }
   }

/*
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
*/

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
		   root->left = scaryVal.myHead;
		   root->right = scaryVal.myHead;
		   root->parent = scaryVal.myHead;
		   root->isNil = false;
		   root->myval = val;
		   root->color = Color::Black;
		   scaryVal.myHead->left = root;
		   scaryVal.myHead->right = root;
		   scaryVal.myHead->parent = root;
		   scaryVal.mySize = 1;
	   }
	   else
	   {
		   TreeNode<value_type>* node = scaryVal.myHead->parent;
		   while (val != node->myval)
		   {
			   if (keyCompare(val, node->myval))
			   {
				   if (node->left != scaryVal.myHead)
				   {
					   node = node->left;
				   }
				   else
					   break;
			   }
			   else
			   {
				   if (node->right != scaryVal.myHead)
				   {
					   node = node->right;
				   }
				   else
					   break;
			   }
		   }
		   if (val != node->myval)
		   {
			   TreeNode<value_type>* newnode = new TreeNode<value_type>;
			   newnode->parent = node;
			   newnode->left = scaryVal.myHead;
			   newnode->right = scaryVal.myHead;
			   newnode->color = Color::Red;
			   newnode->isNil = false;
			   newnode->myval = val;
			   scaryVal.mySize++;
			   if (keyCompare(val, node->myval))
			   {
				   node->left = newnode;
			   }
			   else
			   {
				   node->right = newnode;
			   }
			   if (scaryVal.myHead->left->myval > val)
			   {
				   scaryVal.myHead->left = newnode;
			   }
			   if (scaryVal.myHead->right->myval < val)
			   {
				   scaryVal.myHead->right = newnode;
			   }
			   if (node->color == Color::Red)
				   scaryVal.reBalance(newnode);//modify
		   }
	   }
   }

   // Removes from the set container a single element whose value is val
   // This effectively reduces the container size by one, which are destroyed.
   // Returns the number of elements erased.
   size_type erase( const key_type &val )
   {
	   TreeNode<value_type>* node = scaryVal.myHead->parent;
	   while (node != scaryVal.myHead && val != node->myval)
	   {
		   if (keyCompare(val, node->myval))
		   {
			   node = node->left;
		   }
		   else
		   {
			   node = node->right;
		   }
	   }
	   if (node == scaryVal.myHead)//not found
		   return 0;
	   else//found
	   {
		   if (node->left == scaryVal.myHead || node->right == scaryVal.myHead)
			   scaryVal.eraseDegreeOne(node);
		   else
		   {
			   TreeNode<value_type>* rightmin = node->right;
			   while (rightmin->left != scaryVal.myHead)
				   rightmin = rightmin->left;
			   node->myval = rightmin->myval;
			   scaryVal.eraseDegreeOne(rightmin);
		   }
		   //scaryVal.mySize--;delete
		   return 1;
	   }
   }

private:
   key_compare keyCompare;
   ScaryVal scaryVal;
};

#endif // XTREE
