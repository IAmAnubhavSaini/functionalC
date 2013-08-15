/* 2013 and onwards Anubhav Saini
 * github/IAmAnubhavSaini
 * 
 */

#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H
#include "list.h"
#include "closure.h"

void iter(list *l, void (*fn)(void *, void *), void *args); 

list *map(list *l, void *(*fn)(void *, void *), void *args); 
//map for lifted types
list *lmap(list *l, closure *cl); 

list *filter(list *l, bool (*fn)(void *, void *), void *args); 

list *range(int start, int end); 
list  *  range1skip(int start, int end);
list  *  rangeChar(char start, char end);
#endif

