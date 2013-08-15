/* 2013 and onwards Anubhav Saini
 * github/IAmAnubhavSaini
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "functional.h"
#include "closure.h"

//some standard functional programming functions
void  iter(list *l, void (*fn)(void *, void *), void *args) {
  list *curr;
  for (curr = l; curr != NULL; curr = curr->next) {
    (*fn)(curr->val, args); 
  }
}

list  *  map(list *l, void *(*fn)(void *, void *), void *args) {
  list *o = NULL;
  list *curr;
  for (curr = l; curr != NULL; curr = curr->next) {
    o = append(o, (*fn)(curr->val, args));
  }
  return o;
}

list  *  lmap(list *l, closure *cl) {
  list *o = NULL;
  list *curr;
  for (curr = l; curr != NULL; curr = curr->next) {
    o = append(o, call(cl, (envobj *)curr->val)); 
  }
  return o;
}

list  *  filter(list *l, bool (*fn)(void *, void *), void *args) {
  list *o = NULL;
  list *curr;
  for (curr = l; curr != NULL; curr = curr->next) {
    if ((*fn)(curr->val, args)) {
      o = append(o, copy_item(curr->val));
    }
  }
  return o;
}

//not lazy
list  *  range(int start, int end) {
  list *temp = NULL;
  int i;
  int *aloc;
  for (i = start; i <= end; i+=1) {
    aloc= malloc(sizeof(int));
    *aloc = i;  
    temp = append(temp, (void *)aloc);
  }
  return temp;
}

list  *  range1skip(int start, int end){
  list *temp = NULL;
  int i, *pi;
  for( i = start; i <= end; i+=2){
    pi = (int *) malloc(sizeof(int));
	*pi = i;
	temp = append(temp, (void*)pi);
  }
  return temp;
}

list  *  rangeChar(char start, char end){
  list *temp = NULL;
  char curr, *pcurr;
  if(start < 0x21 || end > 0x7F){
    return NULL;
  }
  for( curr = start; curr <= end; curr += 1){
    pcurr = (char *)malloc(sizeof(char));
	*pcurr = curr;
	temp = append(temp, (void*)pcurr);
  }
  return temp;
}