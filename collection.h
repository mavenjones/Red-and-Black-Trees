/*
 * File: collection.h
 * ------------------
 * The collectionADT represents an abstract data set which can be used
 * to store any scalar type.  In addition to basic functionality (Insert, Search, etc).
 * the collection also exports more interesting functions, including functions that search
 * in a specific range and successor/predecessor functions.
 */

#ifndef __collection__
#define __collection__

/* This is simply a flag used to indicate failure of certain search operations */

#define SENTINEL -1

/* 
 *  Any data type that works correctly with relational operators (<, >, =, etc) 
 *  can be used as the ElementType.  However, we also enforce the constraint that the
 *  data type take on only non-negative values. 
 */

typedef unsigned int ElementType;

/*
 * Type: collmapfn
 * ---------------
 * This defines the type of mapping functions 
 * that can be sent to the mapping facility
 * of the collection.  A very simple (and extremely 
 * useful!) mapping function is one that
 * simply prints out the value of the element.
 */

typedef void (*collmapfn)(ElementType elem, void* auxdata);

/* 
 * Type: collectionADT
 * -------------------
 * The definition of the ADT itself.  Notice that 
 * the definition is incomplete -- you should fill 
 * in the definition in your .c file.
 */

typedef struct collectionCDT *collectionADT;

/* 
 * Functions: CollectionNew, CollectionFree
 * -----------------------------------------
 * CollectionNew allocates and initializes a brand 
 * new collection data type.  CollectionFree releases 
 * all memory associated with the collection.
 */

collectionADT CollectionNew();
void CollectionFree(collectionADT coll);

/*
 * Function: CollectionInsert
 * --------------------------
 * CollectionInsert inserts the element 'elem' 
 * into the collection, taking care to ensure
 * that such a value does NOT already exist in 
 * the collection.  (That is, the collection
 * never has duplicate values).
 */

void CollectionInsert(collectionADT coll, ElementType elem);

/*
 * Function: CollectionSearch
 * --------------------------
 * CollectionSearch attempts to find the given 
 * element 'elem' in the collection. The function
 * returns a boolean indicating whether the search 
 * attempt was successful.
 */ 

int CollectionSearch(collectionADT coll, ElementType elem);

/*
 * Function: CollectionSearchClosestMatch
 * --------------------------------------
 * This function looks for the element 'elem' in the 
 * collection.  If it is not present, the value closest to 
 * it (in terms of absolute distance) is returned.  For example,
 * if the collection contained (1, 3, 6) and we called this 
 * function with 4 as 'elem', we should get 3 as the answer.  
 * On the other hand, if we called this function with 5 as 'elem', 
 * we would get 6 as the answer.
 */

ElementType CollectionSearchClosestMatch(collectionADT coll, ElementType elem);

/*
 * Funtion: CollectionMax, CollectionMin
 * -----------------------------
 * These functions return the maximum/minimum elements 
 * in the collection, respectively.  Duh.
 */

ElementType CollectionMax(collectionADT coll);
ElementType CollectionMin(collectionADT coll);

/*
 * Functions: CollectionMaxInRange, CollectionMinInRange
 * -------------------------------------------
 * CollectionMaxInRange returns the largest value k (if any) 
 * in the collection that satisfies the constraint that 
 * min <= k <= max.  If no such value is found, the default 
 * value SENTINEL is returned.  CollectionMinInRange, similarly, 
 * returns the smallest value k (if any) in the collection which 
 * lies in the range [elem1, elem2].
 * 
 * Note that if min > max, then no value in the collection 
 * will ever satisfy the range constraint -- in this case 
 * SENTINEL should be returned.
 */

ElementType CollectionMaxInRange(collectionADT coll, ElementType min, ElementType max);
ElementType CollectionMinInRange(collectionADT coll, ElementType min, ElementType max);

/*
 * Functions: CollectionSuccessor/CollectionPredecessor
 * ----------------------------------------------------
 * These functions return the successor/predecessor of 
 * given element 'elem' in the collection
 * respectively.  
 *  
 * For simplicity of boundary conditions, we enforce 
 * the following constraints : 
 *    
 *     i) Successor(Maximum())   = SENTINEL
 *    ii) Successor(SENTINEL)    = Minimum()
 *   iii) Predecessor(Minimum()) = SENTINEL
 *    iv) Predecessor(SENTINEL)  = Maximum()
 *	
 * Therefore by repeatedly calling Successor, starting with 
 * SENTINEL, we can get every value in the collection in 
 * sorted order.  Similarly repeatedly calling Predecessor
 * starting with SENTINEL will give us every value in 
 * the collection in reverse sorted order.
 */

ElementType CollectionSuccessor(collectionADT coll, ElementType elem);
ElementType CollectionPredecessor(collectionADT coll, ElementType elem);

/*	
 * Function: CollectionMap
 * -----------------------
 * Applies the given function 'mapfn' to every element 
 * in the collection. 'auxdata' is any auxiliary data 
 * the client wishes to pass through to the mapping
 * function.
 */

void CollectionMap(collectionADT coll, collmapfn mapfn, void *auxdata);

#endif
