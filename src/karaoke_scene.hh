#if !defined(KARAOKE_SCENE_HH)
#define KARAOKE_SCENE_HH

#include "karaoke_text_display.hh"
#include "scene.hh"
#include "song_info.hh"
#include "text.hh"
#include "texture_sprite.hh"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <apr_time.h>
#include <memory>
using std::string;
class KaraokeScene : public Scene {

  Mix_Music *song;
  FrameVec frames;
  TTF_Font *font, *big_font;
  SDL_Renderer *renderer;
  shared_ptr<TextFrame> current_frame;
  shared_ptr<KaraokeTextDisplay> text_display, text_progress;
  shared_ptr<TextureSprite> bg;
  shared_ptr<Texture> text_texture, time_texture;
  string handler_id;
  int last_time_update;
  SongInfo info;

public:
  KaraokeScene(SongInfo &info) : info(info) {}
  void set_frames(FrameVec &&vec);
  void update_frame();
  shared_ptr<KaraokeTextDisplay> get_text_display();
  void set_text_display(shared_ptr<KaraokeTextDisplay> t);
  shared_ptr<TextFrame> get_current_frame();
  bool init();
  string get_handler_id() const override;
  void handle_event(SDL_Event &e) override;
  void render() override;
  virtual ~KaraokeScene();

private:
  void validate_window(SDL_Event &e);
  void update_position();
  void update_time_display(double secs);

protected:
  void on_scene_enter() override;
  void on_scene_exit() override;
};

#endif // KARAOKE_SCENE_HH
