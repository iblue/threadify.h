/* gcc -pthread -o example example.c */
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "threadify.h"

// Initializes the thread pool variables. Has to be called outside of any
// function. If you are using multiple files, this should be used in the file
// containing your main() function only.
THREAD_POOL_INIT();

// Example function 1
void foo(int a, int b, int c) {
  printf("foo: started with arguments %d, %d, %d\n", a, b, c);
  sleep(3);
  printf("foo: done\n");
}

// Example function 2
void bar() {
  printf("bar: started\n");
  sleep(2);
  printf("bar: done\n");
}

// Example function 3
void baz() {
  printf("baz: started\n");
  sleep(1);
  printf("baz: done\n");
}

void main() {
  // Sets the maximum number of threads. If the maximum number is reached,
  // before new threads are created we will wait for an existing thread to
  // terminate.
  // In a real world case this should be set to the number of CPU cores.
  THREAD_POOL_SET(2);

  int x=1, y=2, z=27;

  // Initialize some thread variables.
  THREAD_NEW(thread1);
  THREAD_NEW(thread2);
  THREAD_NEW(thread3);

  // Run threads. The first argument is the threads name, the second is the
  // function to be called, the next values are the argument that are passed to
  // the function.
  // Important: Function arguments must be lvalues (meaning expressions that we
  // can create a pointer on). `a` is an lvalue, because &a exists. `23` is not
  // an lvalue, because `&23` is not possible.
  THREAD_RUN(thread1, foo, x, y, z);
  THREAD_RUN(thread2, bar);
  THREAD_RUN(thread3, baz);

  // Wait for threads to terminate, before terminating the program.
  THREAD_JOIN(thread1);
  THREAD_JOIN(thread2);
  THREAD_JOIN(thread3);
}
