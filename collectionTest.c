/* File : collectionTest.c
 * -----------------------
 * A simple test script to ensure all functions in collection.h work
 */


#include <stdio.h>
#include "collection.h"

void PrintElem(ElementType value, void* auxData);

void InsertTest(collectionADT coll);
void SearchTest(collectionADT coll);
void MaxMinTest(collectionADT coll);
void SuccPredTest(collectionADT coll);

void PrintElem(ElementType value, void* auxData)
{
  printf("%d\n", value);
}

int main()
{
  collectionADT coll = CollectionNew();
  
  InsertTest(coll);   /* Inserts some values into the collection, and prints them out */
  SearchTest(coll);   /* Searches for values in the collection, displays the results  */
  MaxMinTest(coll);   /* Tests the Min/Max and MinInRange/MaxInRange functions        */
  SuccPredTest(coll); /* Tests the Succ/Pred functions and displays the results       */
  CollectionFree(coll);
  
  return 0;
}

void InsertTest(collectionADT coll)
{
  int i,j;
  
  printf("**************************************************************************\n");
  printf("Insert Test\n");
  printf("**************************************************************************\n");
  
  for (i = 0; i < 10; i++)
    {
      CollectionInsert(coll, i);
      CollectionMap(coll, PrintElem, NULL);
      printf("\n");	
    }
  for (i = 20; i > 10; i--)
    CollectionInsert(coll, i);
  
  j = 50;
  for (i = 0; i < 10; i++) {	
    CollectionInsert(coll, j + 3 * i);
    j += i;
  }
  
  CollectionMap(coll, PrintElem, NULL);	
}

void SearchTest(collectionADT coll)
{
  int i;
  
  printf("**************************************************************************\n");
  printf("Search Test\n");
  printf("**************************************************************************\n");
  
  for (i = 0; i <= 100; i+= 5)
    if (CollectionSearch(coll, i)) printf("Found %d\n", i);
    else printf("Couldn't find %d\n", i);
  
  for (i = 0; i < 10; i++)
    printf("Closest value to %d is %d\n", 3* i + 15, CollectionSearchClosestMatch(coll, 3*i + 15));
  
}

void MaxMinTest(collectionADT coll)
{
  printf("**************************************************************************\n");
  printf("Maximum/Minimum Test\n");
  printf("**************************************************************************\n");
  
  
  printf("Maximum is %d\n", CollectionMax(coll));
  printf("Minimum is %d\n", CollectionMin(coll));
  
  printf("Min in range 50 to 150 is %d\n", CollectionMinInRange(coll,50, 150));
  printf("Max in range 50 to 150 is %d\n", CollectionMaxInRange(coll,50, 150));
  printf("Min in range 150 to 50 is %d\n", CollectionMinInRange(coll,150, 50));
  printf("Max in range 150 to 50 is %d\n", CollectionMaxInRange(coll,150, 50));
  
}

void SuccPredTest(collectionADT coll)
{
  int currValue, prevValue;
  prevValue = SENTINEL;
  
  printf("**************************************************************************\n");
  printf("Successor/Predecessor Test\n");
  printf("**************************************************************************\n");
  
  while((currValue = CollectionSuccessor(coll, prevValue)) != SENTINEL) {
    printf("Successor of %d is %d\n", prevValue, currValue);
    prevValue = currValue;
  }
  
  printf("\n\n\n");
  
  prevValue = SENTINEL;
  while((currValue = CollectionPredecessor(coll, prevValue)) != SENTINEL) {
    printf("Predecessor of %d is %d\n", prevValue, currValue);
    prevValue = currValue;
  } 
}
