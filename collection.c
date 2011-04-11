/* File: collection.c
 * Implements the collection abstraction defined 
 * in the interface file collection.h.  Internally, the 
 * collection is represented by a red-black binary tree.
 */

#include "collection.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define RED 0
#define BLACK 1

typedef struct cellT {	
  ElementType value;
  struct cellT* right;
  struct cellT* left;
  struct cellT* pred;
  struct cellT* succ;
  struct cellT* parent;
  int color;
} cellT;

/* 
 * The structure of the collection. Maintains pointers to the max and
 * min nodes. 
 */

struct collectionCDT { 
  cellT* root;
  ElementType max;
  ElementType min;
  cellT* nil;
};

/* 
 * NewCell
 * -------
 * Simply allocates memory for a new cell structure 
 * and initializes it to store the given 'elem'
 */
 
static cellT* NewCell(ElementType elem)
{
  cellT* cell = malloc(sizeof(cellT));
  if (!cell) assert(0);
  cell->value = elem;
  cell->left = NULL;
  cell->right = NULL;
  cell->succ = NULL;
  cell->pred = NULL;
  cell->color = RED;
  cell->parent = NULL;
  return (cell);
}

/* 
 * FindCell
 * --------
 * A helper function that finds the cell in 
 * the tree that stores the given element.  Returns the parent of the
 * found node.  Returns nil if root node.  Returns would-be parent of an
 * element that is not in the list.  Returns NULL if tree is empty.
 */
 
static cellT* FindCell(collectionADT coll, ElementType elem)
{
  cellT* curr = coll->root;
  cellT* parent = coll->nil;

  if(curr==NULL) return NULL;

  while(curr->value != SENTINEL) {
    if (curr->value == elem) break;
    else if (curr->value > elem)
     {
      parent=curr;
      curr=curr->left;
     }
    else
      {
	parent=curr;
	curr=curr->right;
      }
 }
  
  return parent;
}

/* 
 * CollectionNew
 * -------------
 * Simply allocates memory for the collection and 
 * allocates all unknown values to SENTINEL. 
 * Root points to nil.
 */
 
collectionADT CollectionNew()
{

  cellT* nil;
  collectionADT coll;

  coll = malloc(sizeof(struct collectionCDT));
  if (!coll) assert(0);
  
  nil = NewCell(SENTINEL);
  nil->color=BLACK;
  
  coll->nil=nil;
  coll->root=NULL;
  
  coll->max=SENTINEL;
  coll->min=SENTINEL;
  return coll;
}





void freeHelper(cellT* curr)
{
  if(curr->value==SENTINEL)
    return;
  freeHelper(curr->left);
  freeHelper(curr->right);
  free(curr);
}

/* 
 * CollectionFree
 * --------------
 * Frees all the memory associated with the list
 */

void CollectionFree(collectionADT coll)
{
  cellT* curr = coll->root;
  
  if(coll->root->value!=SENTINEL)
    freeHelper(curr);
  free(coll->nil);
  free(coll);
}



void LeftRotate(collectionADT T, cellT* x)
{
  cellT* y = x->right;
  x->right=y->left;
  if(y->left->value!=SENTINEL)
    y->left->parent=x;
  y->parent=x->parent;
  if(x->parent->value==SENTINEL)
    T->root=y;
  else
    if(x==x->parent->left)
      x->parent->left=y;
    else
      x->parent->right=y;
  y->left=x;
  x->parent=y;
}

void RightRotate(collectionADT T, cellT* x)
{
  cellT* y = x->left;
  x->left=y->right;
  if(y->right->value!=SENTINEL)
    y->right->parent=x;
  y->parent=x->parent;
  if(x->parent->value==SENTINEL)
    T->root=y;
  else
    if(x==x->parent->right)
      x->parent->right=y;
    else
      x->parent->left=y;
  y->right=x;
  x->parent=y;
}



//maintains RB properties of tree after an insert.
void InsertFixup(collectionADT T, cellT* z)
{
  cellT* y;


  while((z->parent!=NULL)&&(z->parent->color==RED))
    {
      if(z->parent==z->parent->parent->left)
	{
	  y=z->parent->parent->right;
	  if(y->color==RED)
	    {
	      z->parent->color=BLACK;
	      y->color=BLACK;
	      z->parent->parent->color=RED;
	      z=z->parent->parent;
	    }
	  else 
	    {
	      if(z==z->parent->right)
		{
		  z=z->parent;
		  LeftRotate(T,z);
		}
	      z->parent->color=BLACK;
	      z->parent->parent->color=RED;
	      RightRotate(T,z->parent->parent);
	    }
	}
      else
	{
	  y=z->parent->parent->left;
	  if(y->color==RED)
	    {
	      z->parent->color=BLACK;
	      y->color=BLACK;
	      z->parent->parent->color=RED;
	      z=z->parent->parent;
	    }
	  else 
	    {
	      if(z==z->parent->left)
		{
		  z=z->parent;
		  RightRotate(T,z);
		}
	      z->parent->color=BLACK;
	      z->parent->parent->color=RED;
	      LeftRotate(T,z->parent->parent);
	    }
	}
  
    }
   T->root->color=BLACK;
}

/* 
 * CollectionInsert
 * ----------------
 * Inserts the given 'elem' into the collection, 
 * provided it doesn't already exist. Maintains information about
 * successors, predecessors, min, and max.
 */
 
void CollectionInsert(collectionADT coll, ElementType elem)
{
  cellT* newCell = NewCell(elem);

  cellT* parent = FindCell(coll, elem); 

  
  if(coll->root==NULL)
    {    
      coll->root=newCell;
      coll->max=newCell->value;
      coll->min=newCell->value;
      newCell->parent=coll->nil;
      newCell->left=coll->nil;
      newCell->right=coll->nil;
      newCell->color=BLACK;
      return;
    }

  //else if(parent == NULL)
  //  return;
  else if(parent->value==SENTINEL)   //found the root
    return;
  else if(parent->value > elem)
    {
      if(parent->left->value != SENTINEL)
	return;                         //elem is already in collection
      parent->left=newCell;
      

      newCell->succ=parent;
      newCell->pred=parent->pred;
      parent->pred=newCell;
    }

  else
    {
      if(parent->right->value != SENTINEL)
	return;
      parent->right=newCell;

      newCell->pred=parent;
      newCell->succ=parent->succ;
      parent->succ=newCell;

    }
  
  newCell->left=coll->nil;
  newCell->right=coll->nil;
  newCell->parent=parent;

  if(newCell->value > coll->max)
    coll->max=newCell->value;
  if(newCell->value < coll->min)
    coll->max=newCell->value;

  InsertFixup(coll,newCell);

}

/* 
 * CollectionSearch
 * ----------------
 * Determines whether the given element exists in the collection
 */
 
int CollectionSearch(collectionADT coll, ElementType elem)
{
  cellT* parent;

  if(coll->root==NULL)
    return 0;

  parent = FindCell(coll, elem);
  if(parent->value==SENTINEL)   //found root
   return 1;

  if(elem > parent->value)
    return (parent->right->value != SENTINEL);

  else
    return (parent->left->value != SENTINEL);
}


/* 
 * CollectionMax, CollectionMin
 * ----------------------------
 * Return the minimum and maximum values in 
 * the collection.  If the collection is empty, SENTINEL
 * is returned.
 */

ElementType CollectionMax(collectionADT coll)
{
  return coll->max;
}

ElementType CollectionMin(collectionADT coll)
{
  return coll->min;
}

/* 
 * CollectionSuccessor, CollectionPredecessor
 * ------------------------------------------
 * Return the Successor/Predecessor of the given 'elem'.  
 * See the .h file for boundary conditions.
 */

ElementType CollectionSuccessor(collectionADT coll, ElementType elem)
{
  cellT* parent;

  if(coll->max==elem)
    return SENTINEL;
  
  if(elem==SENTINEL)
    return coll->min;
 
  if(coll->root==NULL)
    return 0;

  parent = FindCell(coll, elem);
  if(parent==NULL)
    return SENTINEL;

  if(parent->value==SENTINEL)
    return coll->root->succ->value;
  
  if(elem > parent->value)
    if(parent->right->value == SENTINEL)
      return SENTINEL;
    else
      return parent->right->succ->value; 

  else
    if(parent->left->value == SENTINEL)
      return SENTINEL;
    else
      return parent->left->succ->value;

  
}


ElementType CollectionPredecessor(collectionADT coll, ElementType elem)
{
   cellT* parent;

  if(coll->min==elem)
    return SENTINEL;
  
  if(elem==SENTINEL)
    return coll->max;
 
  if(coll->root==NULL)
    return 0;

  parent = FindCell(coll, elem);
  if(parent==NULL)
    return SENTINEL;

  if(parent->value==SENTINEL)
    return coll->root->pred->value;

  if(elem > parent->value)
    if(parent->right->value == SENTINEL)
      return SENTINEL;
    else
      return parent->right->pred->value; 

  else
    if(parent->left->value == SENTINEL)
      return SENTINEL;
    else
      return parent->left->pred->value;
}




/* 
 * CollectionSearchClosestMatch
 * ----------------------------
 * Finds the element in the collection that is closest 
 * to 'elem' in terms of absolute distance.
 */

ElementType CollectionSearchClosestMatch(collectionADT coll, ElementType elem)
{
  return 0;
}

/* 
 * CollectionMaxInRange, CollectionMinInRange
 * ------------------------------------------
 * Returns the values that are the max/min values in the 
 * range defined by [min, max].  If the range is invalid, 
 * or the collection is empty, SENTINEL is returned.
 */
 
ElementType CollectionMaxInRange(collectionADT coll, 
				 ElementType low, ElementType high)
{
  return 0;  
}

ElementType CollectionMinInRange(collectionADT coll, 
				 ElementType low, ElementType high)
{
  return 0;
}



void mapHelp(cellT* curr, collmapfn mapfn, void *auxdata)
{
  if(curr->value == SENTINEL)
    return;
  
  mapHelp(curr->left,mapfn,auxdata);
  mapfn(curr->value, auxdata);
  mapHelp(curr->right,mapfn,auxdata);
}

/* CollectionMap
 * -------------
 * Maps the given function to every 
 * element in the collection.
 */
 
void CollectionMap(collectionADT coll, collmapfn mapfn, void* auxdata)
{
  cellT* curr = coll->root;
  if((coll==NULL)||(coll->root==NULL))
    return;

  mapHelp(curr,mapfn,auxdata);
}
