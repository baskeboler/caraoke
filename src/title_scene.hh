#if !defined(TITLE_SCENE_HH)
#define TITLE_SCENE_HH

#include "scene.hh"
#include "texture.hh"
#include <memory>

#include <SDL2/SDL_ttf.h>
class TitleScene : public Scene {
  TTF_Font *font;
  std::shared_ptr<Texture> title_tex;
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

protected:
  void on_scene_enter() override;
  void on_scene_exit() override;
};

#endif // TITLE_SCENE_HH
