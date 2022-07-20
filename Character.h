#ifndef CHARACTER_H
#define CHARACTER_H
#include <SFML/Graphics/RenderWindow.hpp>
#include "Object.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
using namespace std;
using namespace sf;

class Character : public Object {
public:
	Character();
	void LoadTextures();
	void Update(sf::FloatRect platform_bounds);
	void ResetFrame();
	void ChangeState();
	bool CheckState();
	void Jump();
	void DeathSound();
	void Run(float anmvel);
	float m_anmvel = 0; float m_maxanmvel;
private:
	int m_frame = 0;
	vector<Texture>m_runtxt;
	vector<Texture>m_dthtxt;
	vector<Texture>m_jumptxt;
	Clock m_clock;
	FloatRect player_bounds;
	bool m_IsAlive = true, IsJumping = false;
	Vector2f m_vel, m_pos;
	SoundBuffer damage;
	Sound m_damage;
};

#endif

