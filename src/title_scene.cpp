#include "title_scene.hh"
#include "app.hh"
#include <sstream>
using std::stringstream;

TitleScene::TitleScene(SDL_Renderer *renderer) : renderer(renderer) {
  font = TTF_OpenFont("Bangers-Regular.ttf", 72);
  title_tex = std::make_shared<Texture>(nullptr, renderer);
  title_tex->load_from_rendered_text("Karaoke", {128, 128, 128, 255}, font);

  update_title_position();
}
void TitleScene::update_title_position() {
  auto app = App::get_instance();
  auto w = app->get_screen_width(), h = app->get_screen_height(),
       t_w = title_tex->get_w(), t_h = title_tex->get_h();

  title_x = w / 2 - t_w / 2;
  title_y = h / 2 - t_h / 2;
}

string TitleScene::get_handler_id() const {
  stringstream ss;
  ss << "title-scene-" << get_numerical_id();
  return ss.str();
}
void TitleScene::handle_event(SDL_Event &e) {

  switch (e.type) {
  case SDL_WINDOWEVENT: {
    if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
      update_title_position();
    }
  }
  case SDL_KEYDOWN: {
    switch (e.key.keysym.sym) {
    case SDLK_SPACE:
      start_scene(SceneName::SceneThriller);
    default:
      break;
    }
    break;
  }
  default:
    break;
  }
  render();
}
void TitleScene::render() {

  SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
  SDL_RenderClear(renderer);
  title_tex->render(title_x, title_y);
}

TitleScene::~TitleScene() {
  TTF_CloseFont(font);
  title_tex->free();
}

void TitleScene::on_scene_enter() {}
void TitleScene::on_scene_exit() {}