#include "loader.hh"
#include <jansson.h>
#include <iostream>
using std::endl, std::cout;

void debug_frames(vector<TextFrame>& l) {
  // text_frame_t d;
//   list_foreach(d, l, text_frame_t) { 
//       char* text = d->text;
//       printf("text: %s\n", text); 
//     }
  for(auto&& frame : l)
  {
    cout << "text: " << frame.text << endl;    
  }
  
}

vector<TextFrame> load_json(const char *path) {
  vector<TextFrame> ret;
  // ret = list_init();

  json_error_t err;
  json_t *json = json_load_file(path, 0, &err);

  int i, j;
  json_t *json_frame, *val, *offset_node, *val2;
  json_array_foreach(json, i, json_frame) {
    val = json_object_get(json_frame, "text");
    const char *text = json_string_value(val);
    val = json_object_get(json_frame, "offset");
    double offset = json_number_value(val);
    printf("[text] %f -- %s\n", offset, text);
    val = json_object_get(json_frame, "event_offsets");
    // vector< events = list_init();
    TextFrame frame(text, 0);
    frame.offset_seconds = offset;
    json_array_foreach(val, j, offset_node) {
      val2 = json_object_get(offset_node, "offset");
      double offset2 = json_number_value(val2);
      val2 = json_object_get(offset_node, "char_count");
      int char_count = json_integer_value(val2);
      FrameProgress pr;
      pr.char_count = char_count;
      pr.offset_seconds = offset2;
      frame.events.push_back(pr);
    }
    // text_frame_t frame = text_frame_create(text, 0);
    // frame->events = events;
    ret.push_back(frame);
  }
  return ret;
}