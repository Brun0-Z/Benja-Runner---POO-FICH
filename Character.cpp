#include "Character.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

Character::Character() : Object(){
	LoadTextures();
}
void Character::LoadTextures(){
	
	m_runtxt.resize(8);
	m_runtxt[0].loadFromFile("sprites/runanm/0.png");
	m_runtxt[1].loadFromFile("sprites/runanm/1.png");
	m_runtxt[2].loadFromFile("sprites/runanm/2.png");
	m_runtxt[3].loadFromFile("sprites/runanm/3.png");
	m_runtxt[4].loadFromFile("sprites/runanm/4.png");
	m_runtxt[5].loadFromFile("sprites/runanm/5.png");
	m_runtxt[6].loadFromFile("sprites/runanm/6.png");
	m_runtxt[7].loadFromFile("sprites/runanm/7.png");
	
	m_dthtxt.resize(9);
	m_dthtxt[0].loadFromFile("sprites/deathanm/0.png");
	m_dthtxt[1].loadFromFile("sprites/deathanm/1.png");
	m_dthtxt[2].loadFromFile("sprites/deathanm/2.png");
	m_dthtxt[3].loadFromFile("sprites/deathanm/3.png");
	m_dthtxt[4].loadFromFile("sprites/deathanm/4.png");
	m_dthtxt[5].loadFromFile("sprites/deathanm/5.png");
	m_dthtxt[6].loadFromFile("sprites/deathanm/6.png");
	m_dthtxt[7].loadFromFile("sprites/deathanm/7.png");
	m_dthtxt[8].loadFromFile("sprites/deathanm/8.png");
	
	m_jumptxt.resize(8);
	m_jumptxt[0].loadFromFile("sprites/jumpanm/0.png");
	m_jumptxt[1].loadFromFile("sprites/jumpanm/1.png");
	m_jumptxt[2].loadFromFile("sprites/jumpanm/2.png");
	m_jumptxt[3].loadFromFile("sprites/jumpanm/3.png");
	m_jumptxt[4].loadFromFile("sprites/jumpanm/4.png");
	m_jumptxt[5].loadFromFile("sprites/jumpanm/5.png");
	m_jumptxt[6].loadFromFile("sprites/jumpanm/6.png");
	m_jumptxt[7].loadFromFile("sprites/jumpanm/7.png");
	
	m_sprite.setTexture(m_runtxt[0]);
	m_sprite.setPosition(0,485); 
	m_pos = m_sprite.getPosition();
	m_sprite.setScale(3,3);
}


void Character::ChangeState(){
	m_IsAlive = !m_IsAlive; //Se usa para cambiar el estado del pj al chocar con un obstáculo
}

bool Character::CheckState(){
	return (m_IsAlive); //Se fija si el personaje está vivo para seguir corriendo el juego
}

bool Character::InFloor(){
	return (m_pos.y >= 485);
}

void Character::ResetFrame() {
	m_frame = 0; //Vuelve al frame 0 
}


void Character::Update(){
	m_vel.y += .4;
	m_pos.y += m_vel.y;
	
	if(InFloor()){
		m_vel.y = 0;
		m_pos.y = 485;
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) Jump();
		else Run();
	}
	
	if(IsJumping){
		if(m_clock.getElapsedTime().asMilliseconds() >= 150){
			if(m_frame < 7){
				m_sprite.setTexture(m_jumptxt[m_frame]);
				m_frame++;
			}
			m_clock.restart();
		}
	}
	m_sprite.setPosition(0, m_pos.y);
}

void Character::Jump(){
	m_vel.y = -15;
	IsJumping = true;
	m_frame = 0;
}


void Character::Run(){
		if(m_clock.getElapsedTime().asMilliseconds() >= 90){
			if(m_frame < 7){
				m_sprite.setTexture(m_runtxt[m_frame]);
				m_frame++;
			}
			else{
				ResetFrame();
				m_sprite.setTexture(m_runtxt[m_frame]);
				m_frame++;
			}
		m_clock.restart();
		}
	}



void Character::Draw(RenderWindow &window){
	window.draw(m_sprite);
}
