/* 2013 and onwards Anubhav Saini
 * github/IAmAnubhavSaini
 * 
 */

#ifndef LIST_H
#define LIST_H
#include <stdbool.h>

//our list type that we'll use throughout 
//along with the helper functions: new_item and append
//this is boring, go down to main
typedef struct list list;

struct list {
  void *val;
  list *next;
};

list *new_item(void *v); 
list *copy_item(list *i); 
list *append(list *l, void *v); 
list *concat(list *h, list *t); 
list *copy(list *h); 
void list_free(void *); 


#endif

