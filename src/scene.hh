#if !defined(SCENE_HH)
#define SCENE_HH

#include "event_handler.hh"
#include "sprite.hh"

class Scene: public EventHandler, public Sprite {


public:

    virtual ~Scene();
};

#endif // SCENE_HH
