#include "Object.h"

Object::Object() {
}

void Object::Draw (RenderWindow &window) {
	window.draw(m_sprite);
}

bool Object::CollideWith (const Object & o) const {
	auto r1 = this->m_sprite.getGlobalBounds();
	auto r2 = o.m_sprite.getGlobalBounds();
	return r1.intersects(r2);
}

