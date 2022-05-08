#ifndef CHARACTER_H
#define CHARACTER_H
#include <SFML/Graphics/RenderWindow.hpp>
#include "Object.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>
#include <SFML/System/Vector2.hpp>
using namespace std;


class Character : public Object {
public:
	Character();
	void ResetFrame();
	void Update();
	void Draw(RenderWindow &window);
	bool CollideWith(const Object &o) const;
	void ChangeState();
	bool CheckState();
private:
	int m_frame;
	vector<Texture>m_textures;
	Clock m_clock;
	bool m_IsAlive = true;
	bool m_CanJump = true;
	Vector2f m_vel, m_pos;
};

#endif

