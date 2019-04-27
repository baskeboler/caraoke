#if !defined(TEXTURE_H)
#define TEXTURE_H
#include "common.hh"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_types.h>
#include <memory>
#include <string>

using std::shared_ptr;
using std::string;

class Texture {
  private:
  // The actual hardware texture
  SDL_Texture* mTexture;
  SDL_Renderer* mRenderer;

  // Image dimensions
  int mWidth;
  int mHeight;
  
  public:
  int get_w() const;
  int get_h() const;
  Texture(SDL_Texture* tex, SDL_Renderer* ren);
  void init(int w, int h);
  void free();
  void load(const string& path);
  void load_from_rendered_text( const string& text, SDL_Color text_color, TTF_Font* font);
  void render(int x, int y);
};


#endif // TEXTURE_H
