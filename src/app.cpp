#include "app.hh"
#include "thriller_scene.hh"
#include "title_scene.hh"
#include <iostream>
#include <memory>

using std::shared_ptr, std::cout, std::endl, std::stringstream,
    std::make_shared;

shared_ptr<App> App::_instance{};

App::App()
    : SCREEN_HEIGHT(Globals::SCREEN_HEIGHT),
      SCREEN_WIDTH(Globals::SCREEN_WIDTH), gWindow(Globals::gWindow),
      gRenderer(Globals::gRenderer), gScreenSurface(Globals::gScreenSurface)
// gHelloWorld(Globals::gHelloWorld), gFont(Globals::gFont),
// gTextTexture(Globals::gTextTexture), gSong(Globals::gSong)
{}

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

void App::set_screen_width(int arg) { SCREEN_WIDTH = arg; }
void App::set_screen_height(int arg) { SCREEN_HEIGHT = arg; }
void App::set_window(SDL_Window *arg) { gWindow = arg; }
void App::set_renderer(SDL_Renderer *arg) { gRenderer = arg; }
void App::set_screen_surface(SDL_Surface *arg) { gScreenSurface = arg; }

App::~App() {
  cout << "cleaning up resources" << endl;
  // Deallocate surface
  SDL_FreeSurface(gScreenSurface);
  gScreenSurface = nullptr;

  SDL_DestroyRenderer(gRenderer);
  gRenderer = nullptr;

  // Destroy window
  SDL_DestroyWindow(gWindow);
  gWindow = nullptr;

  // Quit SDL subsystems
  SDL_Quit();
}

void App::set_current_scene(shared_ptr<Scene> scene) {
  if (scene) {
    if (current_scene) {
      unregister_handler(current_scene);
      current_scene->on_scene_exit();
    }
    current_scene = scene;
    current_scene->on_scene_enter();
    register_handler(scene);
  }
}
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
  // SDL_RenderClear(get_renderer());
  // SDL_BlitSurface(get_hello_world(), NULL, get_screen_surface(), NULL);
  if (e.type == SDL_WINDOWEVENT &&
      e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
    cout << "window size changed " << e.window.data1 << ", " << e.window.data2
         << endl;
    set_screen_width(e.window.data1);
    set_screen_height(e.window.data2);
  }
  if (e.type == SceneEvents::StartNewScene) {
    // SceneName sname = e.user.data1;
    if (e.user.data1 == (void *)SceneName::SceneThriller) {
      auto thr = make_shared<ThrillerScene>();
      // thr->init();
      set_current_scene(thr);
    } else if (e.user.data1 == (void *)SceneName::SceneTitle) {
      auto title = make_shared<TitleScene>(get_renderer());
      set_current_scene(title);
    }
    cout << "Handling StartNewScene event for scene: " << e.user.data1 << endl;
  }
  for (auto h : handlers) {
    h->handle_event(e);
  }
  SDL_UpdateWindowSurface(get_window());
  SDL_RenderPresent(get_renderer());
}