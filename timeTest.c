/* File : timeTest.c
 * -----------------
 * Evaluates the speed of the collection's operations by performing a total
 * of 50000 operatios (note that they do not correspond to the frequencies
 * listed in the handout.. it's your job to tweak this file yourself to
 * get the required frequencies.)
 */


#include "collection.h"
#include <time.h>
#include <stdio.h>

static void PerformOperations();

int main()
{
  clock_t start, stop, diff;

  start = clock();
  PerformOperations();
  stop = clock();
  diff = stop - start;
  printf("Time taken is %f seconds\n", (double)diff/CLOCKS_PER_SEC);
  return 0;
}

void PerformOperations()
{
  int i, value;
  collectionADT coll = CollectionNew();
  
  /* 7500 inserts */
  
  for (i = 0; i < 5000; i++)
    CollectionInsert(coll, i);
  for (i = 7500; i > 5000; i--)
    CollectionInsert(coll, i);
  
  
  /* 15000 searches */
  
  for (i = 0; i < 75000; i++)
    CollectionSearch(coll, i);
  for (i = 7500; i >= 0; i--)
    CollectionSearch(coll, i);
  
  
  /* 2500 search closests */
  
  for (i = 0; i < 2500 ; i++)
    CollectionSearchClosestMatch(coll, i * 3);
  
  /* 2500 Max/Min calls */
  
  for (i = 0; i < 2500; i++) {
    value = CollectionMax(coll);
    value = CollectionMin(coll);
    
  }
  
  /* 7500 Min/MaxInRange calls */
  for (i = 0; i < 7500; i++) {
    value = CollectionMinInRange(coll, i, 2 * i);
    value = CollectionMaxInRange(coll, i, 2 * i);
  }
  
  /* 2500 Pred/Succ calls */
  for (i = 0; i < 2500; i++) {
    value = CollectionPredecessor(coll, i);
    value = CollectionSuccessor(coll, value);
  }
  
  CollectionFree(coll);
}



