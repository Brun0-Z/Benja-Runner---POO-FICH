#ifndef OBJECT_H
#define OBJECT_H
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <string>
#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
using namespace std;
using namespace sf;

class Object {
public:
	Object();
	void Draw(RenderWindow &window);
	bool CollideWith(const Object &o) const;
protected:
	Texture m_texture;
	Sprite m_sprite;
};

#endif
