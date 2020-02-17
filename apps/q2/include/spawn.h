#ifndef __USERPROG__
#define __USERPROG__

typedef struct buffer {
  int tail;
  int head;
  char chars[10];
  lock_t TheLock;
} buffer;

#define FILENAME_TO_RUN "producer.dlx.obj"
#define FILENAME_TO_RUNTOO "consumer.dlx.obj"


#endif
