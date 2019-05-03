#if !defined(TITLE_SCENE_HH)
#define TITLE_SCENE_HH

#include "scene.hh"
#include "text_sprite.hh"
#include "texture.hh"
#include <SDL2/SDL_ttf.h>
#include <memory>
class TitleScene : public Scene {
  TTF_Font *font;
  std::shared_ptr<TextSprite> title_sprite;

  SDL_Renderer *renderer;
  int title_x, title_y;

public:
  TitleScene(SDL_Renderer *renderer);
  string get_handler_id() const override;
  void handle_event(SDL_Event &e) override;
  void render() override;
  virtual ~TitleScene();

private:
  void update_title_position();
  void update();

protected:
  void on_scene_enter() override;
  void on_scene_exit() override;
};

#endif // TITLE_SCENE_HH
