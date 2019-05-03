#include "app.hh"
#include "thriller_scene.hh"
#include "title_scene.hh"
#include <iostream>
#include <memory>

using std::shared_ptr, std::cout, std::cerr, std::endl, std::stringstream,
    std::make_shared;

shared_ptr<App> App::_instance{};

App::App()
    : SCREEN_HEIGHT(Globals::SCREEN_HEIGHT),
      SCREEN_WIDTH(Globals::SCREEN_WIDTH), gWindow(Globals::gWindow),
      gRenderer(Globals::gRenderer), gScreenSurface(Globals::gScreenSurface)
{}

bool App::init() {
  // Initialization flag
  bool success = true;
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0) {
    cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
    success = false;
  } else {
    // Initialize SDL_ttf
    if (TTF_Init() < 0) {
      cerr << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError()
           << endl;
      success = false;
    } else {

      if (Mix_Init(MIX_INIT_MP3) < 0 ||
          Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cerr << "SDL_mixer could not initialize! SDL_mixer Error: "
             << Mix_GetError() << endl;
        success = false;
      } else {
        if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_WEBP) < 0) {
          cerr << "SDL_image could not initialize! SDL_image Error: "
               << IMG_GetError() << endl;
          success = false;
        } else {

          // Create window
          SDL_Window *w;
          SDL_Renderer *renderer;
          SDL_CreateWindowAndRenderer(get_screen_width(), get_screen_height(),
                                      SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE,
                                      &w, &renderer);
          set_window(w);
          set_renderer(renderer);
          if (w == NULL) {
            cerr << "Window could not be created! SDL_Error: " << SDL_GetError()
                 << endl;
            success = false;
          } else {
            // Get window surface
            SDL_Surface *s = SDL_GetWindowSurface(w);
            set_screen_surface(s);

            sound_controller = make_shared<SoundController>();
            success = sound_controller->init();
          }
        }
      }
    }
  }

  return success;
}

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
  SDL_SetRenderDrawColor(get_renderer(), 128, 128, 128, 255);
  switch (e.type) {
  case SDL_KEYDOWN: {
    switch (e.key.keysym.sym) {
    case SDLK_s:
      if (sound_controller->is_enabled()) {

        sound_controller->pause_audio();
        cout << "audio paused" << endl;
      } else {
        sound_controller->play_audio();
        cout << "audio enabled" << endl;
      }
      break;
    default:
      break;
    }
    break;
  }
  case SDL_WINDOWEVENT: {
    if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
      cout << "window size changed " << e.window.data1 << ", " << e.window.data2
           << endl;
      set_screen_width(e.window.data1);
      set_screen_height(e.window.data2);
    }
    break;
  }
  case SceneEvents::StartNewScene: {
    if (e.user.data1 == (void *)SceneName::SceneThriller) {
      auto thr = make_shared<ThrillerScene>();
      set_current_scene(thr);
    } else if (e.user.data1 == (void *)SceneName::SceneTitle) {
      auto title = make_shared<TitleScene>(get_renderer());
      set_current_scene(title);
    }
    cout << "Handling StartNewScene event for scene: " << e.user.data1 << endl;
    break;
  }
  default:
    break;
  }

  for (auto h : handlers) {
    h->handle_event(e);
  }
  SDL_UpdateWindowSurface(get_window());
  SDL_RenderPresent(get_renderer());
}