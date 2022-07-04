#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "Object.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Background : public Object {
public:
	Background();
	void LoadTextures();
	void Update();
	void Draw(RenderWindow &window); 
	sf::FloatRect viewFloor();
	Vector2f getSpeed();
private:
	Texture m_textures[5];
	Sprite m_sprites[5];
	Vector2f m_bckspeed;
};

#endif

