#ifndef TITLE_H
#define TITLE_H
#include <unistd.h>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Event.hpp>
#define MAX_NUMBER_OF_ITEMS 4
#include "Character.h"
using namespace sf;

class Title : public Scene {
public:
	Title();
	void Update(Game &game) override;
	void Draw(RenderWindow &window) override;
	void ProcessEvent(Event &evt) override;
	void LoadResources() override;
	void MenuUp();
	void MenuDown();
	int GetPressedItem(){return m_selecteditem;}
private:
	Font m_font;
	Text m_texts[4];
	Sprite m_sprite; 
	Texture m_texture;
	Music m_music;
	SoundBuffer m_buffer;
	Sound m_sound;
	bool m_ReturnPressed = false;
	int m_selecteditem = 1;
};
#endif
