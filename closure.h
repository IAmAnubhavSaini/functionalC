/* 2013 - onwards Anubhav Saini
 * github/IAmAnubhavSaini
 * 
 * declared and defined in this file
 * struct closure
 * struct envobj
 * env_item
 * unbox
 * bind
 * call
 * lift_int
 * envobj_free
 * lift_list
 * closure_free
 * 
 * contains forked code from Charles Cary
 * this code: github.com/iamanubhavsaini/functionalC
 */
 
#ifndef CLOSURE_H
#define CLOSURE_H
#include <unistd.h>
#include "list.h"

typedef struct closure closure;

struct closure {
  void *(*fn)(list *);
  list *env;
};

typedef struct envobj envobj;

struct envobj {
  void *val;
  ssize_t size;
};

envobj *env_item(void *var, ssize_t s);
void *unbox(list *l); 
closure *bind(closure *c, void *(*fn)(list *), envobj *env);
void *call(closure *c, envobj *env);
envobj *lift_int(int a); 
list *lift_list(list *l, ssize_t s); 
void envobj_free(void *);
void closure_free(void *);

#endif 
