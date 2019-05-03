#if !defined(TEXT_SPRITE_HH)
#define TEXT_SPRITE_HH
#include "event_handler.hh"
#include "sprite.hh"
#include "texture.hh"

#include <memory>

using std::shared_ptr, std::make_shared;

class TextSprite : public Sprite, public EventHandler {
private:
  shared_ptr<Texture> texture;

public:
  explicit TextSprite(const string &text, SDL_Color color, TTF_Font *font,
                      SDL_Renderer *renderer);
  void render() override;
  string get_handler_id() const override;
  void handle_event(SDL_Event &e) override;
  virtual ~TextSprite();
};

#endif // TEXT_SPRITE_HH
