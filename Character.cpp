#include "Character.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>

Character::Character() : Object(){
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
	m_pos = m_sprite.getPosition();
	m_sprite.setScale(3,3);
	m_frame = 0;
}


void Character::ChangeState(){
	m_IsAlive = !m_IsAlive; //Se usa para cambiar el estado del pj al chocar con un obstáculo
}

bool Character::CheckState(){
	return (m_IsAlive); //Se fija si el personaje está vivo para seguir corriendo el juego
}

void Character::ResetFrame() {
	m_frame = 0; //Vuelve al frame 0 (solo de caminar, por ahora)
}

void Character::Update(){
	if (m_clock.getElapsedTime().asMilliseconds()>=90){ //Cambio de animación
				if(m_frame < 7){
				m_frame++;
				m_sprite.setTexture(m_textures[m_frame]);
			}
		else{
				ResetFrame();
				m_sprite.setTexture(m_textures[m_frame]);
				m_frame++;
				}
		m_clock.restart();
	}
	m_vel.y += .4;
	m_pos.y += m_vel.y;
	
	m_sprite.setPosition(m_vel.x, m_pos.y);
	
	if(m_pos.y >=485){
		m_vel.y = 0;
		m_pos.y = 485;
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) m_vel.y = -10;
	}
}


void Character::Draw(RenderWindow &window){
	window.draw(m_sprite);
}
