#include "scene.hh"
#include <SDL2/SDL.h>
#include <iostream>
using std::cout, std::endl;

Scene::~Scene() {
  cout << "Deleting scene " << this->get_numerical_id() << endl;
}

void Scene::start_scene(SceneName scene_name) {
  cout << "Starting scene " << scene_name << endl;
  SDL_Event e;
  e.type = StartNewScene;
  e.user.data1 = (void *)scene_name;
  e.user.timestamp = SDL_GetTicks();

  SDL_PushEvent(&e);
}

double Scene::elapsed_seconds() {
  apr_time_t now = apr_time_now();
  long now_msec = apr_time_as_msec(now);
  long start_msec = apr_time_as_msec(start);
  return 1.0 * (now_msec - start_msec) / 1000;
}

void Scene::start_timer() { start = apr_time_now(); }
