#if !defined(SOUND_CONTROLLER_HH)
#define SOUND_CONTROLLER_HH

#include <SDL2/SDL.h>

class SoundController {

  SDL_AudioDeviceID dev, dev_out;
  bool enabled;

public:
  SoundController();
  bool init();

  bool pause_audio();
  bool play_audio();

  bool is_enabled() const;

  static void cb(void *userdata, Uint8 *stream, int len);
};

#endif // SOUND_CONTROLLER_HH
