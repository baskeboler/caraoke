#include "sdl_utils.hh"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include "app.hh"
#include <iostream>

using std::cout, std::cerr, std::endl;

bool sdl_init() {
  // Initialization flag
  bool success = true;
  auto app = App::get_instance();
  // Initialize SDL
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
          SDL_CreateWindowAndRenderer(
              app->get_screen_width(), app->get_screen_height(),
              SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, &w, &renderer);
          app->set_window(w);
          app->set_renderer(renderer);
          if (w == NULL) {
            cerr << "Window could not be created! SDL_Error: " << SDL_GetError()
                 << endl;
            success = false;
          } else {
            // Get window surface
            SDL_Surface *s = SDL_GetWindowSurface(w);
            app->set_screen_surface(s);
          }
        }
      }
    }
  }

  return success;
}
