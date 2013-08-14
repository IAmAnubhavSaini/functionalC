/* 2013 - onwards Anubhav Saini
 * github/IAmAnubhavSaini
 * 
 * declared and defined in this file
 * print_int
 * odd
 * dbl
 * add
 * main
 *
 * contains forked code from Charles Cary
 * this code: github.com/iamanubhavsaini/functionalC
 */

#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "functional.h"
#include "closure.h"
#include "gc.h"

// a function to play with iter
void
print_int(void *v, void *args) {
  printf("%d\n", (int)(*(int *)v));
}

//returns true if int v is odd, false otherwise
bool
odd(void *v, void *args) {
  return (bool)(*((int *)v) % 2);
}

//returns twice int v
//boy is this terrible
void *
dbl(void *v, void *args) {
  int *o = malloc(sizeof(int)); 
  *o = *((int *)v) * 2;
  return o;
}

//we'll use this to play with closures
void *
add(list *l) {
  int *a = unbox(l);
  int *b = unbox(l->next);
  int *o = malloc(sizeof(int));
  *o = *a + *b;
  return o; 
}

int
main(int argc, char **argv) {
  
  gc_init(); //initialize the garbage collector

  iter(map(range(0, 10), dbl,NULL), print_int, NULL);
  iter(filter(range(0, 10), odd, NULL), print_int, NULL); 
  
  //Darker magic?  Not really...
  closure *addtwo = bind(NULL, add, lift_int(2));
  closure *addten = bind(NULL, add, lift_int(10));

  printf("%d\n", *(int *)call(addtwo, lift_int(3)));
  printf("%d\n", *(int *)call(addten, lift_int(3)));

  //all together now, with pseudo types everywhere woopie!!!
  list *vars = lift_list(range(0, 10), sizeof(int));
  list *res = lmap(vars, addtwo);
  iter(res, print_int, NULL);

  gc_print(); //show eveything currently in the garbage collector

  gc_collect(); //you can guess what this does

  gc_print(); //anything left?
  
  //NOTE: The garbage collector is a work in progress.  
  //wer're not tracking everything yet and 
  //the collector doesn't necessarily avoid double frees!
  //BEWARE!!!

  exit(0);
}
