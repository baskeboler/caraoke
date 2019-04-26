#include "karaoke_text_display.hh"
#include <iostream>
using std::cout, std::cerr, std::endl;


KaraokeTextDisplay::KaraokeTextDisplay(): Sprite() {}
KaraokeTextDisplay::~KaraokeTextDisplay() {}
KaraokeTextDisplay::KaraokeTextDisplay(const char * text, SDL_Color color, TTF_Font* font, SDL_Renderer* renderer): 
    KaraokeTextDisplay() 
{
    this->renderer = renderer;
    this->texture.reset(new Texture(nullptr, renderer));
    this->texture->init(100, 100);
    this->texture->load_from_rendered_text(text, color, font);
    this->set_w(this->texture->get_w());
    this->set_h(this->texture->get_h());
}
    

void KaraokeTextDisplay::render() {
    // cout << "KaraokeTextDisplay::render" << endl;
    this->texture->render(get_x(), get_y());
}