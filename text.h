#ifndef TEXT_H
#define TEXT_H

#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "list.h"

typedef struct frame_progress_struct { 
  double offset_seconds;
  unsigned int char_count;
} * frame_progress_t;

typedef struct text_frame_struct {
  int id;
  char * text;
  double offset_seconds;
  unsigned int count;
  unsigned int progress;
  list_t events;
  pthread_mutex_t mutex;
} * text_frame_t;

extern text_frame_t text_frame_create(const char * t, unsigned int progress);
extern unsigned int text_frame_advance(text_frame_t frame, unsigned int n);
extern unsigned int text_frame_init();
extern unsigned int text_frame_destroy();


#endif /* TEXT_H */
