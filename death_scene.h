#ifndef DEATH_SCENE_H
#define DEATH_SCENE_H
#include "Scene.h"

class death_scene : public Scene {
public:
	death_scene(int points);
	void ProcessEvent (Event & evt);
	void Update (Game & game);
	void Draw (RenderWindow & window);
	void LoadResources ( );
private:
};

#endif

