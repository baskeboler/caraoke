#include "text_sprite.hh"
#include <sstream>

using std::make_shared, std::shared_ptr;

TextSprite::TextSprite(const string &text, SDL_Color color, TTF_Font *font,
                       SDL_Renderer *renderer) {
  //   Sprite()
  texture = make_shared<Texture>(nullptr, renderer);
  texture->load_from_rendered_text(text, color, font);
  set_w(texture->get_w());
  set_h(texture->get_h());
  set_x(0);
  set_y(0);
}

void TextSprite::render() { texture->render(get_x(), get_y(), get_angle()); }

string TextSprite::get_handler_id() const {
  std::stringstream ss;
  ss << "text-sprite-" << get_numerical_id();
  return ss.str();
}
void TextSprite::handle_event(SDL_Event &e) {}
TextSprite::~TextSprite() { texture->free(); }