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
    return STATUS_OK;
}
status_t texture_load(texture_t t, char* path, SDL_Renderer* renderer) {
    SDL_Texture* texture = NULL;
    status_t ret = STATUS_OK;
    SDL_Surface * surface = IMG_Load(path);
    if (surface == NULL) {
           printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
           ret = STATUS_ERROR_TEXTURE_LOAD;
    } else {
                //Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface( renderer, surface );
        if( texture == NULL )
        {
            ret = STATUS_ERROR_TEXTURE_CREATE;
            printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
        } else {
            texture_free(t);
            t->mTexture = texture;
            unsigned int format;
            int access, w, h;
            SDL_QueryTexture(texture, &format, &access, &w, &h);
            t->mHeight = h;
            t->mWidth = w;
        }
        
        //Get rid of old loaded surface
        SDL_FreeSurface( surface );
    }
    return ret;
}
status_t texture_render(texture_t t, int x, int y, SDL_Renderer* renderer) {
    SDL_Rect rect = {x, y, t->mWidth, t->mHeight};
    SDL_RenderCopy(renderer, t->mTexture, NULL, &rect);
    return STATUS_OK;
}