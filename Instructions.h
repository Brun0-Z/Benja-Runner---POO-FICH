#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H
#include "Scene.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include "Character.h"

class Instructions : public Scene {
public:
	Instructions();
	void ProcessEvent (Event & evt) override;
	void Update (Game & game) override;
	void Draw (RenderWindow & window) override;
	void LoadResources() override;
private:
	Font m_font;
	Text m_textinstruction[4];
	Texture m_tinst1,m_tbackground;
	Sprite m_instru1,m_background;
	bool m_EscapePressed = false, m_ReturnPressed = false;
};

#endif

