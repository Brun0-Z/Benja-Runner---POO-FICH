#ifndef MATCH_H
#define MATCH_H
#include "Scene.h"
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include "Character.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Object.h"
#include "Background.h"
#include "Obstacle.h"
#include <SFML/Audio/Music.hpp>
#include <vector>
#include <SFML/Graphics/View.hpp>
using namespace std;

class Match : public Scene {
public:
	Match();
	void ProcessEvent (Event & evt);
	void Update (Game & game);
	void Draw (RenderWindow & window);
	void LoadResources ();
	void SpawnObstacle();
	void ObstaclesManager();
private:
	Character m_maincharacter;
	vector<Obstacle> m_obstacles;
	Background m_background;
	int m_points = 1, m_waittime = 1;
	View game_view;
	Texture m_txtbck; Sprite m_sprbck;
	bool m_pause = false, m_EscapePressed = false, CanPause = true;
	Clock m_clock1, m_clock2;
	Music m_music;
	Time m_time1, m_time2;
	Text m_textpoints, m_tpoint, m_tpause, m_tescape1, m_tescape2;
	Font m_font;
	Vector2f m_bckspeed;
	SoundBuffer activated;
	Sound m_close;
};

#endif

