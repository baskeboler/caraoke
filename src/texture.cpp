#include "texture.hh"
// #include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <iostream>

Texture::Texture(SDL_Texture *tex, SDL_Renderer *ren)
    : mTexture(tex), mRenderer(ren), mWidth(0), mHeight(0) {}

void Texture::init(int w, int h) {
  this->mHeight = h;
  this->mWidth = w;
  this->mTexture = nullptr;
}

int Texture::get_w() const { return mWidth; }
int Texture::get_h() const { return mHeight; }
void Texture::free() {
  if (mTexture) {
    SDL_DestroyTexture(mTexture);
    mTexture = nullptr;
  }
}
Texture::~Texture() { free(); }
void Texture::load_from_rendered_text(const string &text, SDL_Color text_color,
                                      TTF_Font *font) {
  free();
  SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), text_color);
  if (surface == NULL) {
    // error
  } else {
    SDL_Texture *texture = SDL_CreateTextureFromSurface(mRenderer, surface);
    if (texture == NULL) {
      //
    } else {
      int access, w, h;
      unsigned int format;
      SDL_QueryTexture(texture, &format, &access, &w, &h);
      mTexture = texture;
      mHeight = h;
      mWidth = w;
    }
    SDL_FreeSurface(surface);
  }
}
void Texture::load(const string &path) {
  SDL_Texture *texture = NULL;
  status_t ret = STATUS_OK;
  SDL_Surface *surface = IMG_Load(path.c_str());
  if (surface == NULL) {
    std::cerr << "Unable to load image " << path
              << "! SDL_image Error: " << IMG_GetError() << std::endl;
    ret = STATUS_ERROR_TEXTURE_LOAD;
  } else {
    // Create texture from surface pixels
    texture = SDL_CreateTextureFromSurface(mRenderer, surface);
    if (texture == NULL) {
      std::cerr << "Unable to create texture from " << path
                << "! SDL Error: " << SDL_GetError() << std::endl;
    } else {
      free();
      mTexture = texture;
      unsigned int format;
      int access, w, h;
      SDL_QueryTexture(texture, &format, &access, &w, &h);
      mHeight = h;
      mWidth = w;
    }

    // Get rid of old loaded surface
    SDL_FreeSurface(surface);
  }
}
void Texture::render(int x, int y, double angle, double scale) {
  SDL_Rect rect = {x, y, mWidth, mHeight};
  SDL_RenderSetScale(mRenderer, scale, scale);
  SDL_RenderCopyEx(mRenderer, mTexture, NULL, &rect, angle, nullptr,
                   SDL_RendererFlip::SDL_FLIP_NONE);

  SDL_RenderSetScale(mRenderer,1,1);
}