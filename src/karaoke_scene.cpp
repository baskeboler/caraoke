#include "karaoke_scene.hh"

#include "app.hh"
#include "audio.hh"
#include "loader.hh"
#include "texture_sprite.hh"
#include <sstream>
using std::stringstream, std::string, std::make_shared, std::shared_ptr,
    std::cerr;

string KaraokeScene::get_handler_id() const { return handler_id; }

void KaraokeScene::handle_event(SDL_Event &e) {
  switch (e.type) {
  case SDL_KEYDOWN: {
    switch (e.key.keysym.sym) {
    case SDLK_ESCAPE: {
      start_scene(SceneName::SceneTitle);
      break;
    }
    default:
      break;
    }
  }

  default:
    break;
  }
  validate_window(e);
  update_frame();
  render();
}

void KaraokeScene::render() {
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderClear(renderer);
  bg->render();
  time_texture->render(32, 32);
  text_display->render();
}

bool KaraokeScene::init() {
  bool success = true;
  auto app = App::get_instance();
  stringstream ss;
  ss << "Karaoke-scene-" << get_numerical_id();
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
    // auto t = std::make_shared<Texture>(nullptr, renderer);
    // t->init(100, 100);
    // t->load_from_rendered_text("The quick brown fox jumps over the lazy dog",
    //                            textColor, font);
    // text_texture = t;
    // auto bg = std::make_shared<Texture>(nullptr, renderer);
    // bg->init(100, 100);
    // bg->load("bg.jpeg");
    text_display = std::make_shared<KaraokeTextDisplay>(
        "Micheal Jackson - Karaoke", textColor, big_font, renderer);
  }
  bg = make_shared<TextureSprite>("bg2.jpg");
  bg->set_x(0);
  bg->set_y(0);

  update_position();
  FrameVec l = load_json(info.json_path.c_str());
  frames = std::move(l);

  const char *path = info.song_path.c_str();
  song = audio_load_music((char *)path);
  Mix_PlayMusic(song, 1);
  start_timer();

  time_texture = make_shared<Texture>(nullptr, renderer);
  time_texture->init(100, 100);
  time_texture->load_from_rendered_text(string("00:00"), {255, 255, 255, 255},
                                        font);
  last_time_update = 0;

  return success;
}

void KaraokeScene::update_time_display(double dsecs) {
  int secs = dsecs, mins = secs / 60;

  if (secs > last_time_update) {

    char time_str[16];
    snprintf(time_str, 15, "%02d:%02d", mins, secs % 60);
    time_texture->free();
    time_texture->load_from_rendered_text(time_str, {255, 255, 255, 255}, font);
    last_time_update = secs;
  }
}

KaraokeScene::~KaraokeScene() {
  TTF_CloseFont(font);
  TTF_CloseFont(big_font);
  Mix_FreeMusic(song);
}

void KaraokeScene::set_frames(FrameVec &&vec) { frames = vec; }

void KaraokeScene::update_frame() {
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
  update_time_display(elapsed);
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
shared_ptr<KaraokeTextDisplay> KaraokeScene::get_text_display() {
  return text_display;
}
void KaraokeScene::set_text_display(shared_ptr<KaraokeTextDisplay> t) {
  text_display = t;
}
shared_ptr<TextFrame> KaraokeScene::get_current_frame() {
  return current_frame;
}

void KaraokeScene::validate_window(SDL_Event &e) {
  if (e.type == SDL_WINDOWEVENT &&
      e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
    auto app = App::get_instance();
    auto w = app->get_screen_width(), h = app->get_screen_height();
    set_w(w);
    set_h(h);
    update_position();
  }
}
void KaraokeScene::update_position() {
  auto w = get_w(), h = get_h();
  auto t_w = text_display->get_w(), t_h = text_display->get_h();
  text_display->set_x(w / 2 - t_w / 2);
  text_display->set_y(h / 2 - t_h / 2);

  auto bg_w = bg->get_w(), bg_h = bg->get_h();
  bg->set_x(w / 2 - bg_w / 2);
  bg->set_y(w / 2 - bg_h / 2);
}

void KaraokeScene::on_scene_enter() { init(); }
void KaraokeScene::on_scene_exit() { Mix_HaltMusic(); }