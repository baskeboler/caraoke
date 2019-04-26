#if !defined(TEXTURE_H)
#define TEXTURE_H
#include "common.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_types.h>
typedef struct texture_struct {
  // The actual hardware texture
  SDL_Texture *mTexture;

  // Image dimensions
  int mWidth;
  int mHeight;
} * texture_t;

extern texture_t texture_init(int w, int h);
extern status_t texture_free(texture_t t);
extern status_t texture_load_from_rendered_text(texture_t t, char* text, SDL_Color text_color, TTF_Font* font, SDL_Renderer* renderer);
extern status_t texture_render(texture_t t, int x, int y, SDL_Renderer* renderer);
#endif // TEXTURE_H
