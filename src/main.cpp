#include "app.hh"
#include "audio.hh"
#include "globals.hh"
#include "karaoke_text_display.hh"
#include "loader.hh"
#include "rectangle.hh"
#include "sdl_utils.hh"
#include "text.hh"
#include "texture.hh"
#include "thriller_scene.hh"
#include "title_scene.hh"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <apr_time.h>
#include <iostream>
#include <stdio.h>

using std::cout, std::cerr, std::endl;

/**
 *
 *
 **/
int print_frame(TextFrame *f) {
  pthread_mutex_lock(&f->mutex);
  cout << "textframe(id=" << f->id << ", " << f->text << ", " << f->progress
       << endl;
  pthread_mutex_unlock(&f->mutex);
  return 0;
}

/**
 *
 */
int main(int argc, char **argv) {
  shared_ptr<App> app = App::get_instance();
  // Initialize SDL
  if (!sdl_init()) {
    cerr << "Failed to init SDL" << endl;
  } else {

    auto scene = std::make_shared<TitleScene>(app->get_renderer());
    // scene->init();
    app->set_current_scene(scene);
    bool quit = false;
    SDL_Event e;
    auto usertype = SDL_RegisterEvents(1);
    cout << "usertype: " << usertype << endl;
    while (!quit) {
      while (SDL_PollEvent(&e) != 0) {
        switch (e.type) {
        case SDL_QUIT: {
          quit = true;
          break;
        }
        case SDL_KEYDOWN: {
          switch (e.key.keysym.sym) {
          case SDLK_q: {
            quit = true;
            break;
          }
          default:
            break;
          }
          break;
        }
        default:
          break;
        }
        app->handle_event(e);
        SDL_UpdateWindowSurface(app->get_window());
        SDL_RenderPresent(app->get_renderer());
      }
      e.type = usertype;
      e.user.timestamp = SDL_GetTicks();
      SDL_Delay(17);
      SDL_PushEvent(&e);
    }
  }
}
