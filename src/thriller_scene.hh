#if !defined(THRILLER_SCENE_HH)
#define THRILLER_SCENE_HH

#include "event_handler.hh"
#include "karaoke_text_display.hh"
#include "sprite.hh"
#include "text.hh"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <apr_time.h>
#include <memory>

#include "texture_sprite.hh"
using std::string;
class ThrillerScene : public EventHandler, public Sprite {

  Mix_Music *song;
  FrameVec frames;
  TTF_Font* font;
  SDL_Renderer* renderer;
  shared_ptr<TextFrame> current_frame;
  shared_ptr<KaraokeTextDisplay> text_display, text_progress;
  shared_ptr<TextureSprite> bg;
  shared_ptr<Texture> text_texture;
  string handler_id;
  apr_time_t start;

public:
  void start_timer();
  double elapsed_seconds();
  void set_frames(FrameVec &&vec);
  void update_frame();
  shared_ptr<KaraokeTextDisplay> get_text_display();
  void set_text_display(shared_ptr<KaraokeTextDisplay> t);
  shared_ptr<TextFrame> get_current_frame();
  bool init();
  string get_handler_id() const override;
  void handle_event(SDL_Event &e) override;
  void render() override;
  virtual ~ThrillerScene();
};

#endif // THRILLER_SCENE_HH
