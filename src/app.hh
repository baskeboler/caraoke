#if !defined(APP_H)
#define APP_H
#include "globals.hh"
#include "scene.hh"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

using std::cout, std::endl;
using std::map;
using std::shared_ptr;
using std::vector;
class App {
private:
  static shared_ptr<App> _instance;
  // Screen dimension constants
  int SCREEN_WIDTH;
  int SCREEN_HEIGHT;
  SDL_Window *gWindow;
  SDL_Renderer *gRenderer;

  // The surface contained by the window
  SDL_Surface *gScreenSurface;
  vector<shared_ptr<EventHandler>> handlers;

  shared_ptr<Scene> current_scene;

public:
  App();

public:
  static shared_ptr<App> get_instance();
  ~App();
  int get_screen_width() const;
  int get_screen_height() const;
  SDL_Window *get_window() const;
  SDL_Renderer *get_renderer() const;
  SDL_Surface *get_screen_surface() const;
  void set_screen_width(int arg);
  void set_screen_height(int arg);
  void set_window(SDL_Window *arg);
  void set_renderer(SDL_Renderer *arg);
  void set_screen_surface(SDL_Surface *arg);

  void register_handler(shared_ptr<EventHandler> handler);

  void unregister_handler(shared_ptr<EventHandler> handler);

  void handle_event(SDL_Event &e);

  shared_ptr<Scene> get_current_scene() { return current_scene; }

  void set_current_scene(shared_ptr<Scene> scene);
};

#endif // APP_H
