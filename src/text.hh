#ifndef TEXT_H
#define TEXT_H

#include <memory>
#include <pthread.h>
#include <string>
#include <vector>
using std::shared_ptr;
using std::string;
using std::vector;

struct FrameProgress {
  double offset_seconds;
  unsigned int char_count;
};

struct TextFrame {
  int id;
  string text;
  double offset_seconds;
  unsigned int count;
  unsigned int progress;
  vector<FrameProgress> events;
  pthread_mutex_t mutex;

public:
  TextFrame(const char *t, unsigned int progress);
  void advance(unsigned int n);
  string get_current_text_progress(double offset);

  void init();
  void destroy();
};

typedef vector<shared_ptr<TextFrame>> FrameVec;

#endif /* TEXT_H */
