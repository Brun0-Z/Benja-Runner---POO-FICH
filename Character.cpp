#include "Character.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

Character::Character() : Object() {
	m_textures.resize(8);
	m_textures[0].loadFromFile("sprites/0.png");
	m_textures[1].loadFromFile("sprites/1.png");
	m_textures[2].loadFromFile("sprites/2.png");
	m_textures[3].loadFromFile("sprites/3.png");
	m_textures[4].loadFromFile("sprites/4.png");
	m_textures[5].loadFromFile("sprites/5.png");
	m_textures[6].loadFromFile("sprites/6.png");
	m_textures[7].loadFromFile("sprites/7.png");
	
	m_sprite.setTexture(m_textures[3]); 
	m_sprite.setPosition(100,485); 
	m_sprite.setScale(3,3);
	m_frame = 0;
}

void Character::ChangeState(){
	m_IsAlive = !m_IsAlive;
}

bool Character::CheckState(){
	return (m_IsAlive);
}

void Character::ResetFrame() {
	m_frame = 0;
}

void Character::Update(){
	if (m_clock.getElapsedTime().asMilliseconds()>=100){
				if(m_frame < 7){
				m_frame++;
				m_sprite.setTexture(m_textures[m_frame]);
			}
		else 	{
				if (m_frame == 7){
				ResetFrame();
				m_sprite.setTexture(m_textures[m_frame]);
				m_frame++;
				}
			}
		m_clock.restart();
	}
}


void Character::Draw(RenderWindow &window){
	window.draw(m_sprite);
}
