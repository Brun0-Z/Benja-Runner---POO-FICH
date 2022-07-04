#ifndef OBSTACLE_H
#define OBSTACLE_H
#include "Object.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Obstacle : public Object {
public:
	Obstacle();
	void Update(float veloc);
	Vector2f getPosition();
	void ResetPos();
	bool out_window(Obstacle &o);
private:
	Vector2f m_bckspeed;
	Clock m_clock1, m_clock2;
};

#endif

