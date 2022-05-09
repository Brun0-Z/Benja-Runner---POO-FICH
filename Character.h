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
using namespace sf;

class Character : public Object {
public:
	Character();
	void LoadTextures();
	void Update();
	void Draw(RenderWindow &window);
	bool CollideWith(const Object &o) const;
	void ResetFrame();
	void ChangeState();
	bool CheckState();
	bool InFloor();
	void Jump();
	
	void Run();
private:
	int m_frame = 0;
	vector<Texture>m_runtxt;
	vector<Texture>m_dthtxt;
	vector<Texture>m_jumptxt;
	Clock m_clock;
	bool m_IsAlive = true;
	Vector2f m_vel, m_pos;
	bool IsJumping = false;
};

#endif

