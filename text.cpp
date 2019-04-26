#include "text.hh"
#include <pthread.h>
#include <jansson.h>
#include <iostream>
using std::cerr;
using std::endl;
static unsigned int TEXT_FRAME_ID = 1;
static pthread_mutex_t TEXT_FRAME_ID_MUTEX;
static pthread_mutexattr_t TEXT_FRAME_ID_MUTEX_ATTR;

void TextFrame::init() {
  cerr << "Initializing text frame id" << endl;
  pthread_mutexattr_init(&TEXT_FRAME_ID_MUTEX_ATTR);
  pthread_mutex_init(&TEXT_FRAME_ID_MUTEX, &TEXT_FRAME_ID_MUTEX_ATTR);
}

unsigned int text_frame_next_id() {
  pthread_mutex_lock(&TEXT_FRAME_ID_MUTEX);
  int ret = TEXT_FRAME_ID++;
  pthread_mutex_unlock(&TEXT_FRAME_ID_MUTEX);
  return ret;
}

TextFrame::TextFrame(const char * t, unsigned int progress) {
  // text_frame_t f = (text_frame_t) malloc(sizeof(struct text_frame_struct));
  id = text_frame_next_id();
  text = t;
  progress = progress;
  count = 0;

  pthread_mutexattr_t attr;
  pthread_mutexattr_init(&attr);
  pthread_mutex_init(&mutex, &attr);

}
