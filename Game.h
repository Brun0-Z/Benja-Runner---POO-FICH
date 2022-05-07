#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics/RenderWindow.hpp>
#include "Scene.h"
using namespace sf;

class Game {
public:
	Game();
	void Run();
	void ProcessEvents();
	void Update();
	void Draw();
	void SetScene(Scene *next_scene);
	void CloseGame();
	void Pause();
	~Game();
private:
	RenderWindow m_window;
	Scene *m_scene, *m_next_scene = nullptr;
};

#endif
