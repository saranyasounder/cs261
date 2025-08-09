/*
 * In this file, you should implement an application that compares the
 * performance of a dynamic array and a linked list, as described in the
 * README. Don't forget to include your name and @oregonstate.edu email
 * address below.
 *
 * Name: Saranya Sounder Rajan
 * Email: sounders@oregonstate.edu
 */

#include <stdlib.h>
#include <stdio.h>

#include "dynarray.h"
#include "list.h"
#include "time.h"

#define TEST_DATA_SIZE 1000000

/*
 * This function generates and an array of random integers of size n.
 */
int *generate_random_array(int n)
{
  int *arr = malloc(n * sizeof(int));
  int i;

  for (i = 0; i < n; i++)
  {
    arr[i] = rand();
  }

  return arr;
}

int main(int argc, char const *argv[])
{
  int *test_data = generate_random_array(TEST_DATA_SIZE);
  clock_t start, end;
  double totalTimeD, maxTimeD, totalTimeL, maxTimeL;
  /*
   * You should write code here to insert the data in test_data into a
   * dynamic array using the dynamic array interface you implemented.  As
   * you're doing this, measure two things:
   *   1. The total amount of time it takes to insert all the data into the
   *      dynamic array.
   *   2. The maximum amount of time it takes to insert any single element into
   *      the dynamic array.
   * To help with this, you can use the C functions time() and difftime()
   * from time.h.  Don't forget to include time.h above!
   */
  struct dynarray *testDyn = dynarray_create();
  totalTimeD = 0;
  maxTimeD = 0;

  for (int i = 0; i < TEST_DATA_SIZE; i++)
  {
    start = clock(); //strating timer
    dynarray_insert(testDyn, &test_data[i]);
    end = clock(); //ending timer

    double insertTimeD = (((double)(end - start)) / CLOCKS_PER_SEC); //measuring insert time
    totalTimeD = totalTimeD + insertTimeD;
    if (insertTimeD > maxTimeD)
    {
      maxTimeD = insertTimeD; //updating maxTimeD
    }
  }
  printf("For dynamic arrays:\n\n");
  printf("Total amount of time to insert all data: %lf\n", totalTimeD);
  printf("The maximum amount of time it takes to insert any single element into the dynamic array: %lf\n\n", maxTimeD);

  /*
   * You should write code here to insert the data in test_data into a
   * linked list using the linked list interface you implemented.  As
   * you're doing this, measure two things:
   *   1. The total amount of time it takes to insert all the data into the
   *      linked list.
   *   2. The maximum amount of time it takes to insert any single element into
   *      the linked list.
   * Again, you can use the C functions time() and difftime() from time.h to
   * help with this.
   *
   * How do the times associated with the dynamic array compare to the times
   * associated with the linked list?  How does this change if you modify the
   * value of TEST_DATA_SIZE above?
   */

  struct list *testList = list_create();
  totalTimeL = 0;
  maxTimeL = 0;

  for (int i = 0; i < TEST_DATA_SIZE; i++)
  {
    start = clock();
    list_insert(testList, &test_data[i]);
    end = clock();

    double insertTimeL = (((double)(end - start)) / CLOCKS_PER_SEC);
    totalTimeL = totalTimeL + insertTimeL;
    if (insertTimeL > maxTimeL)
    {
      maxTimeL = insertTimeL;
    }
  }
  printf("For linked lists:\n\n");
  printf("Total amount of time to insert all data: %lf\n", totalTimeL);
  printf("The maximum amount of time it takes to insert any single element into the dynamic array: %lf\n", maxTimeL);
  dynarray_free(testDyn);
  list_free(testList);
  free(test_data);
  return 0;
}
