#ifndef TEXT_H
#define TEXT_H

#include <pthread.h>
#include <string>
#include <vector>
#include <memory>
using std::shared_ptr;
using std::vector;
using std::string;

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

  TextFrame(const char * t, unsigned int progress);
  void advance(unsigned int n);
  string get_current_text_progress(double offset);

  void init();
  void destroy();
};

// extern text_frame_t text_frame_create(const char * t, unsigned int progress);
// extern unsigned int text_frame_advance(text_frame_t frame, unsigned int n);
// extern unsigned int text_frame_init();
// extern unsigned int text_frame_destroy();

typedef vector<shared_ptr<TextFrame>> FrameVec;


#endif /* TEXT_H */
