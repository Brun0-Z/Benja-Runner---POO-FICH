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

class Match : public Scene {
public:
	Match();
	void ProcessEvent (Event & evt);
	void Update (Game & game);
	void Draw (RenderWindow & window);
	void LoadResources ( );
	void EndGame(); 
private:
	Character m_maincharacter;
	int m_points = 0;
	Texture m_txtbck; Sprite m_sprbck;
	bool m_pause = false, m_EscapePressed = false;
	Clock m_clock;
	Time m_time;
	Text m_textpoints, m_tpoint, m_tpause;
	Font m_font;
	Vector2f m_bckspeed;
};

#endif

