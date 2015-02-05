#define __THREAD_POOL // Activate thread pool support

// HELPERS
#define __CAT(arg1, arg2) arg1 ## arg2
#define CAT(arg1, arg2) __CAT(arg1, arg2)
#define NAME(arg1) CAT(arg1, __LINE__)
#define MKFN(fn,...) MKFN_N(fn,##__VA_ARGS__,9,8,7,6,5,4,3,2,1,0)(__VA_ARGS__)
#define MKFN_N(fn,n0,n1,n2,n3,n4,n5,n6,n7,n8,n,...) fn##n

#define THREAD_RUN(...) MKFN(THREAD_RUN,##__VA_ARGS__)

#define THREAD_NEW(arg) pthread_t arg;
#define THREAD_JOIN(arg) pthread_join(arg, NULL);

#ifdef __THREAD_POOL

//Thread pool support. Starts threads when available
extern pthread_mutex_t thread_pool_wait_lock;
extern unsigned int    thread_pool_cnt;
extern pthread_cond_t  thread_pool_cond;

// Increments available thread counter. Called at the end of each thread.
#define THREAD_POOL_DONE() \
pthread_mutex_lock(&thread_pool_wait_lock); \
thread_pool_cnt++; \
pthread_cond_signal(&thread_pool_cond); \
pthread_mutex_unlock(&thread_pool_wait_lock);

// Inititializes thread pool
#define THREAD_POOL_INIT() \
  pthread_mutex_t thread_pool_wait_lock; \
  unsigned int    thread_pool_cnt = 4; \
  pthread_cond_t  thread_pool_cond;

// Sets available threads
#define THREAD_POOL_SET(number) { thread_pool_cnt = number; };

// Waits until threads are available and decrements available thread counter.
#define THREAD_POOL_WAIT() \
pthread_mutex_lock(&thread_pool_wait_lock); \
while(thread_pool_cnt <= 0) { \
  pthread_cond_wait(&thread_pool_cond, &thread_pool_wait_lock); \
} \
thread_pool_cnt--; \
pthread_mutex_unlock(&thread_pool_wait_lock);

#else // __THREAD_POOL
// No thread pool support. Always starts new thread
#define THREAD_JOIN(arg) pthread_join(arg, NULL);
#define THREAD_POOL_WAIT()
#define THREAD_POOL_INIT()
#define THREAD_POOL_DONE()
#endif

#define THREAD_RUN2(thread_name, function) \
THREAD_POOL_WAIT() \
  void NAME(__pthread_wrapper)(void) {\
  do {function();} while(0); \
  THREAD_POOL_DONE(); \
}; \
pthread_create(&thread_name, NULL, (void*)NAME(__pthread_wrapper), NULL);

#define THREAD_RUN3(thread_name, function, arg1) \
THREAD_POOL_WAIT() \
typedef struct { \
  typeof(arg1)* _arg1; \
} NAME(__pthread_struct); \
void NAME(__pthread_wrapper)(NAME(__pthread_struct)* data) {\
  do {function(*data->_arg1);} while(0); \
  THREAD_POOL_DONE(); \
}; \
NAME(__pthread_struct) NAME(__data); \
NAME(__data)._arg1 = &arg1; \
pthread_create(&thread_name, NULL, (void*)NAME(__pthread_wrapper), &NAME(__data));

#define THREAD_RUN4(thread_name, function, arg1, arg2) \
THREAD_POOL_WAIT() \
typedef struct { \
  typeof(arg1)* _arg1; \
  typeof(arg2)* _arg2; \
} NAME(__pthread_struct); \
void NAME(__pthread_wrapper)(NAME(__pthread_struct)* data) {\
  do {function(*data->_arg1, *data->_arg2);} while(0); \
  THREAD_POOL_DONE(); \
}; \
NAME(__pthread_struct) NAME(__data); \
NAME(__data)._arg1 = &arg1; \
NAME(__data)._arg2 = &arg2; \
pthread_create(&thread_name, NULL, (void*)NAME(__pthread_wrapper), &NAME(__data));

#define THREAD_RUN5(thread_name, function, arg1, arg2, arg3) \
THREAD_POOL_WAIT() \
typedef struct { \
  typeof(arg1)* _arg1; \
  typeof(arg2)* _arg2; \
  typeof(arg3)* _arg3; \
} NAME(__pthread_struct); \
void NAME(__pthread_wrapper)(NAME(__pthread_struct)* data) {\
  do {function(*data->_arg1, *data->_arg2, *data->_arg3);} while(0); \
  THREAD_POOL_DONE(); \
}; \
NAME(__pthread_struct) NAME(__data); \
NAME(__data)._arg1 = &arg1; \
NAME(__data)._arg2 = &arg2; \
NAME(__data)._arg3 = &arg3; \
pthread_create(&thread_name, NULL, (void*)NAME(__pthread_wrapper), &NAME(__data));

#define THREAD_RUN6(thread_name, function, arg1, arg2, arg3, arg4) \
THREAD_POOL_WAIT() \
typedef struct { \
  typeof(arg1)* _arg1; \
  typeof(arg2)* _arg2; \
  typeof(arg3)* _arg3; \
  typeof(arg4)* _arg4; \
} NAME(__pthread_struct); \
void NAME(__pthread_wrapper)(NAME(__pthread_struct)* data) {\
  do {function(*data->_arg1, *data->_arg2, *data->_arg3, *data->_arg4);} while(0); \
  THREAD_POOL_DONE(); \
}; \
NAME(__pthread_struct) NAME(__data); \
NAME(__data)._arg1 = &arg1; \
NAME(__data)._arg2 = &arg2; \
NAME(__data)._arg3 = &arg3; \
NAME(__data)._arg4 = &arg4; \
pthread_create(&thread_name, NULL, (void*)NAME(__pthread_wrapper), &NAME(__data));

#define THREAD_RUN7(thread_name, function, arg1, arg2, arg3, arg4, arg5) \
THREAD_POOL_WAIT() \
typedef struct { \
  typeof(arg1)* _arg1; \
  typeof(arg2)* _arg2; \
  typeof(arg3)* _arg3; \
  typeof(arg4)* _arg4; \
  typeof(arg5)* _arg5; \
} NAME(__pthread_struct); \
void NAME(__pthread_wrapper)(NAME(__pthread_struct)* data) {\
  do {function(*data->_arg1, *data->_arg2, *data->_arg3, *data->_arg4, *data->_arg5);} while(0); \
  THREAD_POOL_DONE(); \
}; \
NAME(__pthread_struct) NAME(__data); \
NAME(__data)._arg1 = &arg1; \
NAME(__data)._arg2 = &arg2; \
NAME(__data)._arg3 = &arg3; \
NAME(__data)._arg4 = &arg4; \
NAME(__data)._arg5 = &arg5; \
pthread_create(&thread_name, NULL, (void*)NAME(__pthread_wrapper), &NAME(__data));

#define THREAD_RUN8(thread_name, function, arg1, arg2, arg3, arg4, arg5, arg6) \
THREAD_POOL_WAIT() \
typedef struct { \
  typeof(arg1)* _arg1; \
  typeof(arg2)* _arg2; \
  typeof(arg3)* _arg3; \
  typeof(arg4)* _arg4; \
  typeof(arg5)* _arg5; \
  typeof(arg6)* _arg6; \
} NAME(__pthread_struct); \
void NAME(__pthread_wrapper)(NAME(__pthread_struct)* data) {\
  do {function(*data->_arg1, *data->_arg2, *data->_arg3, *data->_arg4, *data->_arg5, *data->arg6);} while(0); \
  THREAD_POOL_DONE(); \
}; \
NAME(__pthread_struct) NAME(__data); \
NAME(__data)._arg1 = &arg1; \
NAME(__data)._arg2 = &arg2; \
NAME(__data)._arg3 = &arg3; \
NAME(__data)._arg4 = &arg4; \
NAME(__data)._arg5 = &arg5; \
NAME(__data)._arg6 = &arg6; \
pthread_create(&thread_name, NULL, (void*)NAME(__pthread_wrapper), &NAME(__data));
