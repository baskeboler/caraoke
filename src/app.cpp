#include "app.hh"
#include <iostream>
#include <memory>

using std::shared_ptr, std::cout, std::endl, std::stringstream;

shared_ptr<App> App::_instance{};

App::App()
    : SCREEN_HEIGHT(Globals::SCREEN_HEIGHT),
      SCREEN_WIDTH(Globals::SCREEN_WIDTH), gWindow(Globals::gWindow),
      gRenderer(Globals::gRenderer), gScreenSurface(Globals::gScreenSurface),
      gHelloWorld(Globals::gHelloWorld), gFont(Globals::gFont),
      gTextTexture(Globals::gTextTexture), gSong(Globals::gSong) {}

shared_ptr<App> App::get_instance() {
  if (!_instance) {
    _instance = std::make_shared<App>(std::move(App{}));
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
  SDL_FreeSurface(gScreenSurface);
  gScreenSurface = nullptr;

  SDL_DestroyRenderer(gRenderer);
  gRenderer = nullptr;

  // Destroy window
  SDL_DestroyWindow(gWindow);
  gWindow = nullptr;

  TTF_CloseFont(gFont);
  gFont = nullptr;

  Mix_FreeMusic(gSong);
  gSong = nullptr;

  // Quit SDL subsystems
  SDL_Quit();
}

void App::start_timer() { start = apr_time_now(); }
double App::elapsed_seconds() {
  apr_time_t now = apr_time_now();
  long now_msec = apr_time_as_msec(now);
  long start_msec = apr_time_as_msec(start);
  return 1.0 * (now_msec - start_msec) / 1000;
}

void App::set_frames(FrameVec &&vec) { frames = vec; }

void App::update_frame() {

}
shared_ptr<KaraokeTextDisplay> App::get_text_display() { return text_display; }
void App::set_text_display(shared_ptr<KaraokeTextDisplay> t) {
  text_display = t;
}
shared_ptr<TextFrame> App::get_current_frame() { return current_frame; }

void App::register_handler(shared_ptr<EventHandler> handler) {
  cout << "Registering handler " << handler->get_handler_id() << endl;
  handlers.push_back(handler);
}

void App::unregister_handler(shared_ptr<EventHandler> handler) {
  for (auto i = handlers.begin(); i != handlers.end();) {
    if (*i == handler) {
      cout << "Removed handler " << handler->get_handler_id() << endl;
      i = handlers.erase(i);
    } else {
      ++i;
    }
  }
}

void App::handle_event(SDL_Event &e) {
  // update_frame();
  SDL_SetRenderDrawColor(get_renderer(), 128, 128, 128, 255);
  SDL_RenderClear(get_renderer());
  SDL_BlitSurface(get_hello_world(), NULL, get_screen_surface(), NULL);
  if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
    cout << "window size changed " << e.window.data1 
    << ", " << e.window.data2 <<  endl;
    set_screen_width(e.window.data1);
    set_screen_height(e.window.data2);
  }
  for (auto h : handlers) {
    h->handle_event(e);
  }
  SDL_UpdateWindowSurface(get_window());
  SDL_RenderPresent(get_renderer());
}