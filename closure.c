/* 2013 and onwards Anubhav Saini
 * github/IAmAnubhavSaini
 * 
 * declared in this file
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

#include <stdlib.h>
#include <unistd.h>
#include "list.h"
#include "closure.h"
#include "gc.h"

envobj *
env_item(void *var, ssize_t size) {
  envobj *env = malloc(sizeof(envobj));
  env->val = var;
  env->size = size;
  gc_register((void *)env, ENVOBJ);
  return env;
}

void *
unbox(list *l) {
  //envobj *env = (envobj *)l->val;
  //return env->val; 
  return ((envobj*)l->val)->val;
}

closure *
bind(closure *c, void *(*fn)(list *), envobj *env) {
  closure *cl;
  if (c == NULL) {
    cl = malloc(sizeof(closure)); 
    if (cl == NULL) {
      exit(1);
    }
    cl->env = NULL;
    cl->fn = fn;
    gc_register((void *)cl, CLOSURE);
  }
  else {
    cl = c;
  }
  cl->env = append(cl->env, (void *)env); 
  return cl;
}

void *
call(closure *c, envobj *env) {
  list *copylist = copy(c->env);
  copylist = append(copylist, (void *)env);
  return c->fn(copylist);
}

//helper functions (syntactic sugar...erm...i guess...)
//these make using closures easier
envobj *
lift_int(int a) {
  int *v = malloc(sizeof(int));
  *v = a;
  gc_register((void *)v, STANDARD);
  envobj *o = env_item((void *)v, sizeof(int)); 
  return o;
}

void
envobj_free(void *_obj) {
  envobj *obj = _obj;
  free(obj);
}

list *
lift_list(list *l, ssize_t s) {
  list *o = NULL;
  list *curr;

  for (curr = l; curr != NULL; curr = curr->next) {
     envobj *lifted = env_item(curr->val, s); 
     o = append(o, (void *)lifted);
  }
  return o;
}

void
closure_free(void *_c) {
  closure *c = _c;
  free(c);
}
