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