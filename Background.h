#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "Object.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

class Background : public Object {
public:
	Background();
	void LoadTextures();
	void Update(int points);
	void Draw(RenderWindow &window); 
	sf::FloatRect viewFloor();
	Vector2f getSpeed();
	void ChangeLevel(Color c);
private:
	Texture m_texturesday[5], m_texturesnight[5];
	Sprite m_sprites[5];
	Vector2f m_bckspeed;
	bool IsDay = true;
	Sound animal;
	SoundBuffer sbowl, sbrooster;
};

#endif

