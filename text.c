#include "text.h"
#include <pthread.h>
#include <stdio.h>
#include <jansson.h>

static unsigned int TEXT_FRAME_ID = 1;
static pthread_mutex_t TEXT_FRAME_ID_MUTEX;
static pthread_mutexattr_t TEXT_FRAME_ID_MUTEX_ATTR;

unsigned int text_frame_init() {
  printf("Initializing text frame id\n");
  pthread_mutexattr_init(&TEXT_FRAME_ID_MUTEX_ATTR);
  pthread_mutex_init(&TEXT_FRAME_ID_MUTEX, &TEXT_FRAME_ID_MUTEX_ATTR);
  return 0;
}

unsigned int text_frame_next_id() {
  pthread_mutex_lock(&TEXT_FRAME_ID_MUTEX);
  int ret = TEXT_FRAME_ID++;
  pthread_mutex_unlock(&TEXT_FRAME_ID_MUTEX);
  return ret;
}

text_frame_t text_frame_create(const char * t, unsigned int progress) {
  text_frame_t f = (text_frame_t) malloc(sizeof(struct text_frame_struct));
  f->id = text_frame_next_id();
  f->text = strdup(t);
  f->progress = progress;
  f->count = 0;

  pthread_mutexattr_t attr;
  pthread_mutexattr_init(&attr);
  pthread_mutex_init(&f->mutex, &attr);

  return f;
}
