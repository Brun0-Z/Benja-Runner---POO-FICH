#include "Object.h"

Object::Object() { //Constructor que no recibe nada

}

Object::Object(string fname) { //Constructor que recibe el nombre del archivo
	m_texture.loadFromFile(fname);
	m_sprite.setTexture(m_texture);
}

void Object::Draw (RenderWindow &window) { //Cada objeto debe saber dibujarse
	window.draw(m_sprite);
}

bool Object::CollideWith (const Sprite & s) const { //Y acá están las colisiones con un Sprite (piso)
	auto r1 = this->m_sprite.getGlobalBounds();
	auto r2 = s.getGlobalBounds();
	return r1.intersects(r2);
}

bool Object::CollideWith (const Object & o) const { //Y acá las colisiones con un objeto (pj-trampa)
	auto r1 = this->m_sprite.getGlobalBounds();
	auto r2 = o.m_sprite.getGlobalBounds();
	return r1.intersects(r2);
}

