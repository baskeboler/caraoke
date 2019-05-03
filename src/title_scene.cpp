#include "title_scene.hh"
#include "app.hh"
#include "common.hh"
#include <numeric>
#include <sstream>

using std::stringstream;

TitleScene::TitleScene(SDL_Renderer *renderer) : renderer(renderer) {
  // start_timer
  font = TTF_OpenFont("Bangers-Regular.ttf", 72);
  title_sprite.reset(
      new TextSprite("Karaoke", {128, 128, 128, 255}, font, renderer));
  // title_sprite->load_from_rendered_text("Karaoke", {128, 128, 128, 255},
  // font);

  update_title_position();
}
void TitleScene::update_title_position() {
  auto app = App::get_instance();
  double w = app->get_screen_width(), h = app->get_screen_height(),
       t_w = title_sprite->get_w(), t_h = title_sprite->get_h();

  title_x = w / 2 - t_w / 2;
  title_y = h / 2 - t_h / 2;
  title_sprite->set_x(title_x);
  title_sprite->set_y(title_y);
}

string TitleScene::get_handler_id() const {
  stringstream ss;
  ss << "title-scene-" << get_numerical_id();
  return ss.str();
}
void TitleScene::handle_event(SDL_Event &e) {
  update();
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
  auto secs = elapsed_seconds();
  double alphaq = lerp(secs, DVec2{0, 15}, DVec2{0, 1});
  SDL_SetRenderDrawColor(renderer, alphaq * 255.0, 0, 0,alphaq *  180.0);
  SDL_RenderClear(renderer);
  // SDL_RenderSetViewport
  title_sprite->render();
}

TitleScene::~TitleScene() {
  TTF_CloseFont(font);
  title_sprite.reset();
}
void TitleScene::update() {
  // auto ticks = elapsed_seconds();
  double secs = elapsed_seconds();
  // num::

  double angle = std::cos(secs) * 15.0;
  double sin_val = std::sin(secs);
  title_sprite->update_pos(secs);
  title_sprite->set_vel(DVec2{0, 100}*sin_val);
  title_sprite->set_angle(angle);
  title_sprite->set_scale(lerp(secs, DVec2{0,15}, DVec2{3,1}));
}
void TitleScene::on_scene_enter() {
  start_timer();
}
void TitleScene::on_scene_exit() {}