#include "sdl_utils.hh"
#include "texture.hh"
#include <iostream>
#include "app.hh"

using std::cout, std::cerr, std::endl;

bool sdl_init() {
  // Initialization flag
  bool success = true;
  auto app = App::get_instance();
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    success = false;
  } else {
    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
      printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n",
             TTF_GetError());
      success = false;
    } else {
      if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n",
               Mix_GetError());
        success = false;
      } else {
        if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_WEBP) < 0) {
          printf("SDL_image could not initialize! SDL_image Error: %s\n",
                 IMG_GetError());
          success = false;
        } else {

          // Create window
          SDL_Window * w; SDL_Renderer * renderer;
          SDL_CreateWindowAndRenderer(app->get_screen_width(), app->get_screen_height(), SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE,
          &w, &renderer);
          app->set_window(w);
          app->set_renderer(renderer);
          if (w == NULL) {
            cerr << "Window could not be created! SDL_Error: " <<
                   SDL_GetError() << endl;
            success = false;
          } else {
            // Get window surface
            app->set_screen_surface(SDL_GetWindowSurface(app->get_window()));
          }
        }
      }
    }
  }

  return success;
}

bool loadMedia() {
  // Loading success flag
  bool success = true;
  auto app = App::get_instance();
  app->set_font(TTF_OpenFont("Bangers-Regular.ttf", 28));
  if (app->get_font() == nullptr) {
    printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
    success = false;
  } else {
    // Render text
    SDL_Color textColor = {255, 0, 0, 255};
    auto t = std::make_shared<Texture>(nullptr, app->get_renderer());
    t->init(100, 100);
    t->load_from_rendered_text(
            "The quick brown fox jumps over the lazy dog",
            textColor, app->get_font());
    app->set_text_texture(t);
  }
  app->set_hello_world(IMG_Load("bg.jpeg"));
  if (app->get_hello_world() == nullptr) {
    cerr << "Unable to load image bg.jpeg! SDL Error: " << 
           SDL_GetError() << endl;
    success = false;
  }

  return success;
}

