/* 2013 and onwards Anubhav Saini
 * github/IAmAnubhavSaini
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "list.h"
#include "gc.h"

list *
  cook_list_item(void){
    list *new_item = (list*) malloc(sizeof(list));
    if(new_item == NULL){
      exit(1);
    }
    new_item->val = NULL;
    new_item->next = NULL;
    return new_item;
}

list *
  new_item(void *v) {
    list *o = cook_list_item();
    o->val = v;
    gc_register((void *)o, LIST);
    return o;
}

list *
  copy_item(list *l) {
    list *o = cook_list_item();
    o->val = l->val;
    o->next = l->next;
    return o;
}

list *
  append(list *l, void *v) {
    list *ni = new_item(v);
    if (l == NULL) {
      return ni;
    }
    list *curr;
    for (curr = l; curr->next != NULL; curr = curr->next)
      ;
    curr->next = ni;
    return l;
}

list *
  concat(list *h, list *t) {
    list *curr;
    for (curr = h; curr->next != NULL; curr = curr->next)
      ;
    curr->next = t;
    return h;	
}

//shallow copy
list *
  copy(list *l) {
    list *o = NULL;
    list *curr;
    for (curr = l; curr != NULL; curr = curr->next) {
      o = append(o, curr->val);
    }
    return o; 
}

//objs flag set to true will also free the objects in the list
void
  list_free(void *_l) {
    list *l = _l;
    free(l); 
}


