#if !defined(SCENE_HH)
#define SCENE_HH

#include "event_handler.hh"
#include "sprite.hh"

enum SceneEvents { StartNewScene = SDL_USEREVENT + 1 };

enum SceneName { SceneTitle, SceneThriller };

class Scene : public EventHandler, public Sprite {

protected:
  virtual void on_scene_enter() = 0;
  virtual void on_scene_exit() = 0;

public:
  virtual ~Scene();
  static void start_scene(SceneName scene_name);

  friend class App;
};

#endif // SCENE_HH
