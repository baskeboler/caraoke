#if !defined(EVENT_HANDLER_H)
#define EVENT_HANDLER_H
#include <SDL2/SDL.h>
#include <string>

using std::string;

class EventHandler {

    static long _id;

    long numerical_id;
    public:

    static long next_id();
    
    EventHandler();
    long get_numerical_id() const;
    virtual void handle_event(SDL_Event& e) = 0; 
    virtual string get_handler_id() const = 0;
    virtual ~EventHandler();
};


#endif // EVENT_HANDLER_H

