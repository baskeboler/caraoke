#include "texture_sprite.hh"
#include "app.hh"

TextureSprite::TextureSprite(const string &path) {
  texture = make_shared<Texture>(nullptr, App::get_instance()->get_renderer());
  texture->init(100, 100);
  texture->load(path);
  set_w(texture->get_w());
  set_h(texture->get_h());
}
void TextureSprite::render() { texture->render(get_x(), get_y()); }

TextureSprite::~TextureSprite() {}

string TextureSprite::get_handler_id() const {
  std::stringstream ss;
  ss << "texture-sprite-" << get_numerical_id();
  return ss.str();
}

void TextureSprite::handle_event(SDL_Event &e) { render(); }