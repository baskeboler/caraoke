#include "texture.h"

texture_t texture_init(int w, int h) { 
    texture_t ret = (texture_t) malloc(sizeof(struct texture_struct));
    ret->mHeight = h;
    ret->mWidth = w;
    ret->mTexture = NULL;
    return ret;
}

status_t texture_free(texture_t t) {
    if (t->mTexture) {
        SDL_DestroyTexture(t->mTexture);
        t->mTexture = NULL;
    }
    return STATUS_OK;
}

status_t texture_load_from_rendered_text(texture_t t, char* text, SDL_Color text_color, TTF_Font* font, SDL_Renderer* renderer) {
    texture_free(t);
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, text_color);
    if (surface == NULL) {
        // error
    } else { 
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == NULL) {
            //
        } else {
            int access, w, h;
            unsigned int format;
            SDL_QueryTexture(texture, &format, &access, &w, &h);
            t->mTexture = texture;
            t->mHeight = h;
            t->mWidth = w;
        }
        SDL_FreeSurface(surface);
    }
    return t->mTexture != NULL;
}