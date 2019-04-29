#include "thriller_scene.hh"
#include "app.hh"
#include "audio.hh"
#include "loader.hh"
#include "texture_sprite.hh"
#include <sstream>
using std::stringstream, std::string, std::make_shared, std::shared_ptr,
    std::cerr;

string ThrillerScene::get_handler_id() const { return handler_id; }

void ThrillerScene::handle_event(SDL_Event &e) {
  validate_window(e);
  update_frame();
  render();
}

void ThrillerScene::render() {
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderClear(renderer);
  bg->render();
  text_display->render();
}

bool ThrillerScene::init() {
  bool success = true;
  auto app = App::get_instance();
  stringstream ss;
  ss << "thriller-scene-" << get_numerical_id();
  handler_id = ss.str();
  renderer = app->get_renderer();
  auto w = app->get_screen_width(), h = app->get_screen_height();
  set_w(w);
  set_h(h);
  font = TTF_OpenFont("Bangers-Regular.ttf", 28);
  big_font = TTF_OpenFont("Bangers-Regular.ttf", 48);
  if (font == nullptr || big_font == nullptr) {
    cerr << "Failed to load lazy font! SDL_ttf Error: " << TTF_GetError();
    success = false;
  } else {

    // Render text
    SDL_Color textColor = {255, 0, 0, 255};
    auto t = std::make_shared<Texture>(nullptr, renderer);
    t->init(100, 100);
    t->load_from_rendered_text("The quick brown fox jumps over the lazy dog",
                               textColor, font);
    text_texture = t;
    auto bg = std::make_shared<Texture>(nullptr, renderer);
    bg->init(100, 100);
    bg->load("bg.jpeg");
    text_display = std::make_shared<KaraokeTextDisplay>(
        "Micheal Jackson - Thriller", textColor, big_font,
        renderer);
  }
  bg = make_shared<TextureSprite>("bg.jpeg");
  bg->set_x(0);
  bg->set_y(0);
  FrameVec l = load_json("song.json");
  frames = std::move(l);
  const char *path = "song.mp3";
  song = audio_load_music((char *)path);
  Mix_PlayMusic(song, 1);
  start_timer();
  return success;
}

void ThrillerScene::start_timer() { start = apr_time_now(); }

ThrillerScene::~ThrillerScene() {}

double ThrillerScene::elapsed_seconds() {
  apr_time_t now = apr_time_now();
  long now_msec = apr_time_as_msec(now);
  long start_msec = apr_time_as_msec(start);
  return 1.0 * (now_msec - start_msec) / 1000;
}

void ThrillerScene::set_frames(FrameVec &&vec) { frames = vec; }

void ThrillerScene::update_frame() {
  auto app = App::get_instance();
  shared_ptr<TextFrame> current = nullptr;
  auto elapsed = elapsed_seconds();
  for (auto fr : frames) {
    if (fr->offset_seconds <= elapsed) {
      current = fr;
    } else {
      break;
    }
  }
  if (current && current != current_frame) {
    cout << "new frame: " << current->text << endl;
    current_frame = current;

    auto kd = new KaraokeTextDisplay(current->text.c_str(),
                                     {255, 255, 255, 255}, font, renderer);
    kd->set_frame(current);
    int x = (app->get_screen_width() / 2) - (kd->get_w() / 2),
        y = (app->get_screen_height() / 2) - (kd->get_h() / 2);
    kd->set_x(x);
    kd->set_y(y);

    text_display = std::make_shared<KaraokeTextDisplay>(*kd);
  } else {
    text_display->update();
  }
}
shared_ptr<KaraokeTextDisplay> ThrillerScene::get_text_display() {
  return text_display;
}
void ThrillerScene::set_text_display(shared_ptr<KaraokeTextDisplay> t) {
  text_display = t;
}
shared_ptr<TextFrame> ThrillerScene::get_current_frame() {
  return current_frame;
}

void ThrillerScene::validate_window(SDL_Event &e) {
  if (e.type == SDL_WINDOWEVENT &&
      e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
    auto app = App::get_instance();
    auto w = app->get_screen_width(), h = app->get_screen_height();
    set_w(w);
    set_h(h);
    update_position();
  }
}
void ThrillerScene::update_position() {
  auto w = get_w(), h = get_h();
  auto t_w = text_display->get_w(), t_h = text_display->get_h();
  text_display->set_x(w / 2 - t_w / 2);
  text_display->set_y(h / 2 - t_h / 2);

  auto bg_w = bg->get_w(), bg_h = bg->get_h();
  bg->set_x(w / 2 - bg_w / 2);
  bg->set_y(w / 2 - bg_h / 2);
}