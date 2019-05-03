#include "sound_controller.hh"
#include <iostream>

using std::cout, std::endl;

SoundController::SoundController() : enabled(false) {}

bool SoundController::init() {
  SDL_AudioSpec want, want_out, have, have_out;
  SDL_zero(want);
  want.freq = 44100;
  want.format = AUDIO_S16SYS;
  want.channels = 1;
  want.samples = 1024;
  want.callback = SoundController::cb;
  want.userdata = &dev_out;

  SDL_zero(want_out);
  want_out.freq = 44100;
  want_out.format = AUDIO_S16SYS;
  want_out.channels = 1;
  want_out.samples = 1024;
  want_out.callback = nullptr;

  cout << "audio out: " << SDL_GetAudioDeviceName(0, 0) << endl;
  cout << "audio in: " << SDL_GetAudioDeviceName(0, 1) << endl;

  dev = SDL_OpenAudioDevice(SDL_GetAudioDeviceName(0, 1), 1, &want, &have, 0);
  dev_out = SDL_OpenAudioDevice(SDL_GetAudioDeviceName(0, 0), 0, &want_out,
                                &have_out, 1);

  if (have.format != want.format) {
    SDL_Log("We didn't get the format we asked for");
    return false;
  }

  play_audio();
  return true;
}

void SoundController::cb(void *userdata, Uint8 *stream, int len) {
//   cout << "callback at " << SDL_GetTicks() << endl;

  SDL_AudioDeviceID *data = (SDL_AudioDeviceID *)userdata;
  SDL_QueueAudio(*data, stream, len);
}

bool SoundController::pause_audio() {
  SDL_PauseAudioDevice(dev, 1);
  if (dev == 0) {
    SDL_Log("Failed to open audio: %s", SDL_GetError());
    return false;
  }
  SDL_PauseAudioDevice(dev_out, 1);
  if (dev_out == 0) {
    SDL_Log("Failed to open audio: %s", SDL_GetError());
    return false;
  }
  enabled = false;
  return true;
}
bool SoundController::play_audio() {
  SDL_PauseAudioDevice(dev, 0);
  if (dev == 0) {
    SDL_Log("Failed to open audio: %s", SDL_GetError());
    return false;
  }
  SDL_PauseAudioDevice(dev_out, 0);
  if (dev_out == 0) {
    SDL_Log("Failed to open audio: %s", SDL_GetError());
    return false;
  }
  enabled = true;
  return true;
}

bool SoundController::is_enabled() const { return enabled; }