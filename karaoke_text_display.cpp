#include "karaoke_text_display.hh"
#include <iostream>
using std::cout, std::cerr, std::endl;

KaraokeTextDisplay::KaraokeTextDisplay() : Sprite() {}
KaraokeTextDisplay::~KaraokeTextDisplay() {}
KaraokeTextDisplay::KaraokeTextDisplay(const char *text, SDL_Color color,
                                       TTF_Font *font, SDL_Renderer *renderer)
    : KaraokeTextDisplay() {
  this->font = font;
  this->renderer = renderer;
  this->texture_black.reset(new Texture(nullptr, renderer));
  this->texture_black->init(100, 100);
  this->texture_black->load_from_rendered_text(text, color, font);
  this->set_w(this->texture_black->get_w());
  this->set_h(this->texture_black->get_h());
  this->timestamp = apr_time_now();
  this->progress = 0;
}

void KaraokeTextDisplay::update() {
  auto now = apr_time_now();
  double offset =
      1.0 * (apr_time_as_msec(now) - apr_time_as_msec(timestamp)) / 1000;

  if (text_frame) {
    offset += text_frame->offset_seconds;
    auto p = text_frame->get_current_text_progress(offset);
    if (p.length() != progress) {
      cout << "progress: " << p << endl;
      progress = p.length();
      texture_red.reset(new Texture(nullptr, renderer));
      texture_red->init(100, 100);
      texture_red->load_from_rendered_text(p, {255, 0, 0, 255}, font);
    }
  }
}
void KaraokeTextDisplay::render() {
  // cout << "KaraokeTextDisplay::render" << endl;
  this->texture_black->render(get_x(), get_y());
  if (texture_red) {
    this->texture_red->render(get_x(), get_y());
  }
}

void KaraokeTextDisplay::set_frame(shared_ptr<TextFrame> f) { text_frame = f; }