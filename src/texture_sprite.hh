#if !defined(TEXTURE_SPRITE_HH)
#define TEXTURE_SPRITE_HH

#include "event_handler.hh"
#include "sprite.hh"
#include "texture.hh"
#include <memory>
#include <sstream>
#include <string>
using std::shared_ptr, std::make_shared, std::string;

class TextureSprite : public Sprite, public EventHandler {
private:
  shared_ptr<Texture> texture;

public:
  TextureSprite(const string &path);
  void render() override;

  string get_handler_id() const override ;
  void handle_event(SDL_Event& e)  override;
  virtual ~TextureSprite();
};

#endif // TEXTURE_SPRITE_HH
