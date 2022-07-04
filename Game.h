#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics/RenderWindow.hpp>
#include "Scene.h"
#include "structScore.h"
#include <vector>
using namespace std;
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
	void Add_NewHighscore(structScore m_newscore);
	void InitHighScore();
	void saveScores();
	vector<structScore> getHighScores();
	structScore aux;
	~Game();
private:
	vector<structScore> m_highscores; 
	RenderWindow m_window;
	Scene *m_scene, *m_next_scene = nullptr;
};

#endif
