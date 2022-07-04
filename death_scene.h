#ifndef DEATH_SCENE_H
#define DEATH_SCENE_H
#include "Scene.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include "InputBox.h"
#include "structScore.h"
#include "Game.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class death_scene : public Scene {
public:
	InputText inp;
	death_scene(int points);
	void ProcessEvent (Event & evt);
	void Update (Game & game);
	void Draw (RenderWindow & window);
	void LoadResources ( );
	void MenuUp();
	void MenuDown();
private:
	structScore aux;
	int m_score;
	Text m_text[6];
	Texture m_tbackground;
	Sprite m_background;
	Font m_font;
	bool m_ReturnPressed = false;
	int m_selecteditem = 3;
};

#endif

