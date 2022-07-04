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
#include <cmath>
using namespace std;

Character::Character() : Object(){
	LoadTextures();
}
void Character::LoadTextures(){
	
	m_runtxt.resize(8);
	for(int i=0;i<m_runtxt.size();++i) { 
		m_runtxt[i].loadFromFile("sprites/runanm/"+to_string(i)+".png"); //Se cargan las animaciones de correr
	}
	
	m_jumptxt.resize(8);
	for(int i=0;i<m_runtxt.size();++i) { 
		m_jumptxt[i].loadFromFile("sprites/jumpanm/"+to_string(i)+".png"); //Se cargan las animaciones de saltar
	}
	
	m_sprite.setTexture(m_runtxt[0]); //Se asigna la textura inicial de correr
	m_sprite.setPosition(10,485);  //Se le da una posici�n al sprite (ya que no se mueve en la partida)
	m_pos = m_sprite.getPosition(); //Se guarda la pos del sprite
	m_sprite.setScale(3,3); //Y se le da un tama�o
}

void Character::ResetFrame() {
	m_frame = 0; //Vuelve al frame 0 
}

void Character::Update(sf::FloatRect platform_bounds){ //El update del personaje recibe el rect�ngulo correspondiente al piso
	m_vel.y += .33333333; //en cada update, se agrega velocidad en y. Es decir, gravedad (hacia abajo)
	m_pos.y += m_vel.y; //Y la pos se corresponde a esta velocidad agregada
	
	if(m_anmvel >= -30) //En este caso, anmvel se usa para hacer que la animaci�n de correr se ejecute m�s r�pido con el paso del tiempo
	m_anmvel -= 0.01; 
	
	m_sprite.setPosition(m_pos); //se le setea la posici�n de acuerdo al cambio que hay con respecto a la velocidad en y
	player_bounds = m_sprite.getGlobalBounds(); //Se guarda el rect�ngulo de colisi�n
	
	if(player_bounds.intersects(platform_bounds)){ //Si el pj est� sobre el suelo
		m_vel.y = 0; //La vel en y es 0 (porque si no atravesar�a)
		m_pos.y = platform_bounds.top - (player_bounds.height); m_sprite.setPosition(m_pos.x,m_pos.y); //y se cambia la pos de acuerdo al rect�ngulo del piso, seteando as� la pos del pj
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){ //Solo se puede saltar estando en el piso
			Jump();
		}
		else Run(m_anmvel); //Mientras no est� saltando, el pj corre
	}
	
	if(IsJumping){ //Si est� saltando (o no est� sobre el suelo)
		if(m_clock.getElapsedTime().asMilliseconds() >= 90){ //Se tiene un clock que administra los tiempos entre animaciones
			if(m_frame < 7){ //Recorre todos los frames de la animacion de salto
				m_sprite.setTexture(m_jumptxt[m_frame],true); //Y los setea al sprite. El true sirve para acoplar el bound del sprite al tama�o de la textura (util para colisiones)
				m_frame++;
			}
			m_clock.restart(); //Se hace restart del clock para volver a contar 90 milisegundos
			}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){ //Si se est� saltando y se presiona S o flecha hacia abajo, baja m�s r�pido
			m_vel.y += .5;
		}
	}
}

void Character::Jump(){ 
	m_vel.y = -15; //Al saltar, se pone velocidad negativa en y (hacia arriba)
	IsJumping = true; //IsJumping se vuelve verdadero
	ResetFrame(); //Y se llama a ResetFrame para que se ejecute la animaci�n de salto desde el primer frame
}

void Character::Run(float anmvel){ //Para correr, se recibe la velocidad de animaci�n actual
		if(m_clock.getElapsedTime().asMilliseconds() >= 90+anmvel){ //Al principio son 90 milisegundos entre frame, pero luego va bajando
			if(m_frame < 7){ //Mientras no est� en el �ltimo frame 
				m_sprite.setTexture(m_runtxt[m_frame],true); //Setea el sprite con esa textura y con reajuste del rect�ngulo de colisi�n
				m_frame++;
			}
			else{
				ResetFrame(); //Si est� en el �ltimo frame, vuelve al 0
				m_sprite.setTexture(m_runtxt[m_frame],true); //Setea el sprite con textura 0
				m_frame++;
			}
		m_clock.restart(); //Y se resetea el reloj
		}
	}
