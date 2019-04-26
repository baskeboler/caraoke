#if !defined(KARAOKE_TEXT_DISPLAY_H)
#define KARAOKE_TEXT_DISPLAY_H

#include "sprite.hh"
#include "text.hh"
#include "texture.hh"
#include <SDL2/SDL.h>
#include <apr_time.h>
#include <memory>

using std::shared_ptr;

class KaraokeTextDisplay : public Sprite {
  shared_ptr<TextFrame> text_frame;
  shared_ptr<Texture> texture_black, texture_red;
  SDL_Renderer *renderer;
  TTF_Font *font;
  int progress = 0;
  apr_time_t timestamp;

public:
  KaraokeTextDisplay();
  KaraokeTextDisplay(const char *text, SDL_Color color, TTF_Font *font,
                     SDL_Renderer *renderer);
  void update();
  void set_frame(shared_ptr<TextFrame> f);
  virtual void render();
  virtual ~KaraokeTextDisplay();
};
#endif // KARAOKE_TEXT_DISPLAY_H
