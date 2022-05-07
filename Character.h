#ifndef CHARACTER_H
#define CHARACTER_H
#include <SFML/Graphics/RenderWindow.hpp>
#include "Object.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>
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
	Sprite m_sprite;
	vector<Texture>m_textures;
	Clock m_clock;
	bool m_IsAlive = true;
};

#endif

