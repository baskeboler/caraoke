#if !defined(APP_H)
#define APP_H
#include "globals.hh"
#include "karaoke_text_display.hh"
#include "text.hh"
#include "texture.hh"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <apr_time.h>
#include <memory>

using std::shared_ptr;

class App {
private:
  static shared_ptr<App> _instance;
  App()
      : SCREEN_HEIGHT(Globals::SCREEN_HEIGHT),
        SCREEN_WIDTH(Globals::SCREEN_WIDTH), gWindow(Globals::gWindow),
        gRenderer(Globals::gRenderer), gScreenSurface(Globals::gScreenSurface),
        gHelloWorld(Globals::gHelloWorld), gFont(Globals::gFont),
        gTextTexture(Globals::gTextTexture), gSong(Globals::gSong) {}
  // Screen dimension constants
  int SCREEN_WIDTH;
  int SCREEN_HEIGHT;
  apr_time_t start;
  // The window we'll be rendering to
  SDL_Window *gWindow;
  SDL_Renderer *gRenderer;

  // The surface contained by the window
  SDL_Surface *gScreenSurface;
  SDL_Surface *gHelloWorld;
  TTF_Font *gFont;
  shared_ptr<Texture> gTextTexture;
  Mix_Music *gSong;
  FrameVec frames;
  shared_ptr<TextFrame> current_frame;
  shared_ptr<KaraokeTextDisplay> text_display;

public:
  static shared_ptr<App> get_instance();
  ~App();
  void set_frames(FrameVec &&vec);
  void update_frame();
  shared_ptr<KaraokeTextDisplay> get_text_display();
  void set_text_display(shared_ptr<KaraokeTextDisplay> t);
  shared_ptr<TextFrame> get_current_frame();
  int get_screen_width() const;
  int get_screen_height() const;
  void start_timer();
  double elapsed_seconds();
  // The window we'll be rendering to
  SDL_Window *get_window() const;
  SDL_Renderer *get_renderer() const;

  // The surface contained by the window
  SDL_Surface *get_screen_surface() const;
  SDL_Surface *get_hello_world() const;
  TTF_Font *get_font() const;
  shared_ptr<Texture> get_text_texture() const;
  Mix_Music *get_song() const;

  void set_screen_width(int arg);
  void set_screen_height(int arg);
  void set_window(SDL_Window *arg);
  void set_renderer(SDL_Renderer *arg);
  void set_screen_surface(SDL_Surface *arg);
  void set_hello_world(SDL_Surface *arg);
  void set_font(TTF_Font *arg);
  void set_text_texture(shared_ptr<Texture> arg);
  void set_song(Mix_Music *arg);
};

#endif // APP_H
