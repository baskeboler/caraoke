#include "loader.h"
#include <jansson.h>

void debug_frames(list_t l) {
  text_frame_t d;
//   list_foreach(d, l, text_frame_t) { 
//       char* text = d->text;
//       printf("text: %s\n", text); 
//     }
   while(l != NULL) {
       d = (text_frame_t) l->data;
       printf("text: %s\n", d->text);
       l = l->next;
   }
}

list_t load_json(const char *path) {
  list_t ret;
  ret = list_init();

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
    list_t events = list_init();
    json_array_foreach(val, j, offset_node) {
      val2 = json_object_get(offset_node, "offset");
      double offset2 = json_number_value(val2);
      val2 = json_object_get(offset_node, "char_count");
      int char_count = json_integer_value(val2);
      frame_progress_t pr =
          (frame_progress_t)malloc(sizeof(struct frame_progress_struct));
      pr->char_count = char_count;
      pr->offset_seconds = offset2;
      list_append(&events, pr);
    }
    text_frame_t frame = text_frame_create(text, 0);
    frame->offset_seconds = offset;
    frame->events = events;
    list_append(&ret, frame);
  }
  return ret;
}