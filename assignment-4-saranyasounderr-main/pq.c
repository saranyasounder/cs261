/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Saranya Sounder Rajan
 * Email: sounders@oregonstate.edu
 */

#include <stdlib.h>

#include "pq.h"
#include "dynarray.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq{
struct dynarray* heap;
};

struct node{
  int priority;
  void* value;
};


/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
  struct pq* pq = malloc(sizeof(struct pq));
  pq->heap = dynarray_create();
  return pq;
}

struct node* node_create(int priority, void* value){
  struct node* node = malloc(sizeof(struct node));
  node->priority = priority;
  node->value = value;
  return node;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
	for (int i = 0; i < dynarray_size(pq->heap); i++) {
		struct node* node = dynarray_get(pq->heap, i);
		free(node); 
	}
	dynarray_free(pq->heap);
	free(pq);
}



/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
  if(dynarray_size(pq->heap) > 0) {
		return 0;
	}
	return 1;
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void swap(struct pq* pq, int a_ind, int b_ind) {
    struct node* a = dynarray_get(pq->heap, a_ind);
    struct node* b = dynarray_get(pq->heap, b_ind);
    dynarray_set(pq->heap, a_ind, b);
    dynarray_set(pq->heap, b_ind, a);
}

void pq_insert(struct pq* pq, void* value, int priority) {
    if (pq == NULL || value == NULL) return; // Safety check

    struct node* node = node_create(priority, value);
    if (node == NULL) return; // handle allocation failure

    dynarray_insert(pq->heap, node); // Insert at the end of the heap
    int index = dynarray_size(pq->heap) - 1;

    // Bubble up to maintain heap property
    while (index > 0) {
        int p_ind = (index - 1) / 2; // Parent index
        struct node* p_node = dynarray_get(pq->heap, p_ind);
        if (node->priority < p_node->priority) { // Swap if current node has lower priority
            swap(pq, index, p_ind);
            index = p_ind;
        } else {
            break; // Stop if heap property is satisfied
        }
    }
}




/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
   struct node* node = dynarray_get(pq->heap, 0); 
  return node->value;
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
    struct node* node = dynarray_get(pq->heap, 0); 
  return node->priority;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {
    if (pq_isempty(pq)) {
        return NULL;
    }

    struct node* first_node = dynarray_get(pq->heap, 0);
    void* value = first_node->value;


    int last_index = dynarray_size(pq->heap) - 1;
    struct node* last_node = dynarray_get(pq->heap, last_index);
    dynarray_set(pq->heap, 0, last_node);
    dynarray_remove(pq->heap, last_index); 


    free(first_node);


    int index = 0;
    while (index < dynarray_size(pq->heap)) {
        int left_child = 2 * index + 1;
        int right_child = 2 * index + 2;
        int smallest = index;

        
        if (left_child < dynarray_size(pq->heap) &&
            ((struct node*)dynarray_get(pq->heap, left_child))->priority < ((struct node*)dynarray_get(pq->heap, smallest))->priority) {
            smallest = left_child;
        }

        if (right_child < dynarray_size(pq->heap) &&
            ((struct node*)dynarray_get(pq->heap, right_child))->priority < ((struct node*)dynarray_get(pq->heap, smallest))->priority) {
            smallest = right_child;
        }

        if (smallest != index) {
            swap(pq, index, smallest);
            index = smallest;
        } else {
            break; 
        }
    }

    return value;
}

