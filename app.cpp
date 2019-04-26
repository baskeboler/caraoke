#include "app.hh"
#include <iostream>
using std::shared_ptr, std::cout, std::endl;

shared_ptr<App> App::_instance{};

shared_ptr<App> App::get_instance() {
  if (!_instance) {
    _instance.reset(new App);
  }
  return _instance;
}

int App::get_screen_width() const { return SCREEN_WIDTH; }
int App::get_screen_height() const { return SCREEN_HEIGHT; }
SDL_Window *App::get_window() const { return gWindow; }
SDL_Renderer *App::get_renderer() const { return gRenderer; }
SDL_Surface *App::get_screen_surface() const { return gScreenSurface; }
SDL_Surface *App::get_hello_world() const { return gHelloWorld; }
TTF_Font *App::get_font() const { return gFont; }
shared_ptr<Texture> App::get_text_texture() const { return gTextTexture; }
Mix_Music *App::get_song() const { return gSong; }

void App::set_screen_width(int arg) { SCREEN_WIDTH = arg; }
void App::set_screen_height(int arg) { SCREEN_HEIGHT = arg; }
void App::set_window(SDL_Window *arg) { gWindow = arg; }
void App::set_renderer(SDL_Renderer *arg) { gRenderer = arg; }
void App::set_screen_surface(SDL_Surface *arg) { gScreenSurface = arg; }
void App::set_hello_world(SDL_Surface *arg) { gHelloWorld = arg; }
void App::set_font(TTF_Font *arg) { gFont = arg; }
void App::set_text_texture(shared_ptr<Texture> arg) { gTextTexture = arg; }
void App::set_song(Mix_Music *arg) { gSong = arg; }

App::~App() {
  cout << "cleaning up resources" << endl;
  // Deallocate surface
  SDL_FreeSurface(gHelloWorld);
  gHelloWorld = nullptr;

  // Destroy window
  SDL_DestroyWindow(gWindow);
  gWindow = nullptr;

  // Quit SDL subsystems
  SDL_Quit();
}

void App::start_timer() { start = apr_time_now(); }
double App::elapsed_seconds() {
  apr_time_t now = apr_time_now();
  int now_msec = apr_time_as_msec(now);
  int start_msec = apr_time_as_msec(start);
  return 1.0 * (now_msec - start_msec) / 1000;
}

void App::set_frames(FrameVec &&vec) { frames = vec; }

void App::update_frame() {
  shared_ptr<TextFrame> current;
  auto elapsed = elapsed_seconds();
  for (auto fr : frames) {
    if (fr->offset_seconds <= elapsed - 2.5) {
      current = fr;
    } else {
      break;
    }
  }
  if (current && current != current_frame) {
    cout << "new frame: " << current->text << endl;
    current_frame = current;
    auto t = new Texture(nullptr, get_renderer());
    t->init(100, 100);
    t->load_from_rendered_text(current->text, {255, 0, 0, 255}, get_font());
    gTextTexture.reset(t);

    auto kd = new KaraokeTextDisplay(current->text.c_str(), {255, 0, 0, 255},
                                     get_font(), get_renderer());
    int x = (get_screen_width() / 2) - (kd->get_w() / 2),
        y = (get_screen_height() / 2) - (kd->get_h() / 2);
    kd->set_x(x);
    kd->set_y(y);
    text_display = std::make_shared<KaraokeTextDisplay>(*kd);
  }
}
shared_ptr<KaraokeTextDisplay> App::get_text_display() { return text_display; }
void App::set_text_display(shared_ptr<KaraokeTextDisplay> t) {
  text_display = t;
}
shared_ptr<TextFrame> App::get_current_frame() { return current_frame; }
