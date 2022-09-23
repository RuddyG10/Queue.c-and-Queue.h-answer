/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if(q == NULL){ //condition if malloc is null, tit means that there's nothing n the queue.
      return NULL;
    }
    //create a new queue, both head and tail need to be null and the size 0 because it's new.
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements? */
    /* Free queue structure */

    //my answer
    if(q==NULL){ //if there's nothing on the queue, do not do anything.
      return;
    }
    // point to the head of the queue and then release it.
    list_ele_t *element= q->head; 
    free(q);

    //if there's something on that element of the ll, then, travel into the list and release that element.
    while(element != NULL){
      list_ele_t *elementCopy = element;
      element = element->next;
      free(elementCopy);
    }
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_head(queue_t *q, int v)
{
    list_ele_t *newHead;
    /* What should you do if the q is NULL? */
    //if it's null, that queue doesn't exist
    if(q==NULL){
      return false;
    }
      
    newHead = malloc(sizeof(list_ele_t));
      /* What if malloc returned NULL? */
      //if malloc is null there,s nothing in the list.
    if(newHead== NULL){
          return false;
    }
    //point the new value to be the first element of the the list (head).
    newHead->value = v;
    //now the previous head will be the netx element of the new head
    newHead->next = q->head;
    //if there wasnt a head on the original list, then the tail will be that next value
    if(q->head == NULL){
        q->tail = newHead;
    }
    //asing the new head to the original one
    q->head = newHead;
    //add more size on the original list
    q->size++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_tail(queue_t *q, int v)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    //point to the tail of the list
    list_ele_t *newTail;
    //if the queue is null there's nothing to do
    if(q == NULL){
      return false;
    }

    newTail= malloc(sizeof(list_ele_t));
    //if the list doesn't have a tail
    if(newTail == NULL){
      return false;
    }
    //asing the parameter value to be the only value of the list, and the next will be null, making sure that is a tail.
    newTail->value = v;
    newTail->next = NULL;

     //if the queue by parameter doesnt have a tail then is a one-dimentional array with the tail and the head with a same value
    if(q->tail == NULL){
      q->head = newTail;
      q->tail = newTail;
      //increment the size of the queue
      q->size++;
      return true;
    }
    //on the easiest case only asing the new tail to the next value of the original tail (that is null by defect).
    q->tail->next = newTail;
    //now declarate the new value that you insert as the new tail of the whole queue
    q->tail = newTail;
    //increment the size of the queue
    q->size++;
    return true;

    
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If vp non-NULL and element removed, store removed value at *vp.
  Any unused storage should be freed
*/
bool q_remove_head(queue_t *q, int *vp)
{
    /* You need to fix up this code. */
    //if the queue by paramether or the head of that queue is null, dont do anything
    if(q==NULL || q->head == NULL){
      return false;
    }
    //point the actual head to release it
    list_ele_t *prevHead = q->head;
    //if vp isn't null, that will be the value of the list that we create with previous head
    if(vp != NULL){
      *vp = prevHead->value;
    }
    //the new head of the list will be the next value of the prevHead list (in case that the previous condition were true, that value will be vp)
    q->head = prevHead->next;
    //erase that head
    free(prevHead);
    //substract size of the list
    q->size--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{ 
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    //if q is null it doesn't have size
    if(q == NULL){
      return 0;
    }
    //return the size
    return q->size;
}

/*
  Reverse elements in queue.

  Your implementation must not allocate or free any elements (e.g., by
  calling q_insert_head or q_remove_head).  Instead, it should modify
  the pointers in the existing data structure.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    //dont do anything in case that queue or his head were null
    if(q == NULL || q->head == NULL){
      return;
    }
    //point to the head, the next element of the head and the previous element of that head will be null
    //with that we will reverse the elements pasing next to the null.
    list_ele_t *element = q->head;
    list_ele_t *prev = NULL;
    list_ele_t *next = element->next;

    //travel into the list using the next element until there's no element
    while (element->next!=NULL)
    {
      //asing the next element to be the previous element
      element->next =prev;
      prev = element;
      //now the next element will be the original one and the real next element will be the element next of the original one.
      element = next;
      next = element->next;
    }
    //if the element next of the original is null that will be the previous element
    element->next = prev;
    //point the tail direction of the list to be the head direction.
    q->tail=q->head;
    //and that head will have the original element
    q->head =element;
    

}

