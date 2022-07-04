#include "Background.h"
#include <SFML/System/Vector2.hpp>

Background::Background() {
	LoadTextures(); //Se invoca a la función de cargar texturas
	m_bckspeed.x = -4; //Y se fija la velocidad inicial del fondo
}

void Background::LoadTextures() {
	for(int i=0;i<5;++i) {  
		m_textures[i].loadFromFile("sprites/"+to_string(i)+".png"); //Se cargan los png en el vector de texturas
		m_textures[i].setRepeated(true); //Y se le asigna a todos el SetRepeated para que se repita a lo largo del juego
		
		m_sprites[i].setTexture(m_textures[i]);  //En el vector de sprites, se setea a cada sprite con la respectiva textura
		m_sprites[i].setTextureRect(IntRect(100,0,999999,256)); //Y el rectángulo de visión tiene que tener un tamaño aleatorio para que se repita a lo ancho
		m_sprites[i].setScale(2,2.35); //se le pone una escala a la imagen
	}
	m_sprites[3].setTextureRect(IntRect(100,0,999999,15)); //para el sprite del piso, se asigna una altura distinta
	m_sprites[3].setPosition(0,560); //y una posición en y inicial
}

sf::FloatRect Background::viewFloor(){
	return m_sprites[3].getGlobalBounds(); //para ver las colisiones con el piso
}

Vector2f Background::getSpeed(){
	return m_bckspeed; //para ver la velocidad actual del piso
}

void Background::Update(){
	float maxmovbckspeed = -15; //se asigna un valor máximo a la velocidad (podría ser atributo de la clase)
	
	if(m_bckspeed.x > maxmovbckspeed) //en cada update, compara la velocidad actual del fondo. Mientras sea mayor a la máxima (porque es negativo en eje x), sigue decreciendo
		m_bckspeed.x -= .003f;
	
	for(int i=0;i<5;++i) {  
		m_sprites[i].move((m_bckspeed.x*(i+1))/4,0); //Y para el efecto parallax, cada parte del fondo se mueve a velocidad distinta.
	}
}

void Background::Draw(RenderWindow &window) {
	for(int i=0;i<5;++i) { 
		window.draw(m_sprites[i]); //El fondo simplemente dibuja el vector de sprites propio
	}
}


