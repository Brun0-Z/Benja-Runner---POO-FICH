#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "Object.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>

class Obstacle : public Object {
public:
	Obstacle();
	void Update(float veloc);
	Vector2f getPosition();
	void Activate();
	void CollisionDetected();
	bool ViewCol();
	void CloseSound();
private:
	Texture m_texture[6];
	Vector2f m_bckspeed;
	Clock m_clock1;
	bool col = false;
	int m_frame = 0;
};

#endif

