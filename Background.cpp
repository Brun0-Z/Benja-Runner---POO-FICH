#include "Background.h"
#include <SFML/System/Vector2.hpp>

Background::Background() {
	LoadTextures(); //Se invoca a la función de cargar texturas
	m_bckspeed.x = -4; //Y se fija la velocidad inicial del fondo
}

void Background::LoadTextures() {
	sbowl.loadFromFile("music/Owl.ogg");
	sbrooster.loadFromFile("music/Rooster.ogg");
	animal.setVolume(5); 
	
	for(int i=0;i<5;++i) {  
		m_texturesday[i].loadFromFile("sprites/day/"+to_string(i)+".png"); //Se cargan los png en el vector de texturas
		m_texturesday[i].setRepeated(true); //Y se le asigna a todos el SetRepeated para que se repita a lo largo del juego
		
		m_texturesnight[i].loadFromFile("sprites/night/"+to_string(i)+".png"); //Se cargan los png en el vector de texturas
		m_texturesnight[i].setRepeated(true); //Y se le asigna a todos el SetRepeated para que se repita a lo largo del juego
		
		m_sprites[i].setTexture(m_texturesday[i]);  //En el vector de sprites, se setea a cada sprite con la respectiva textura
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

void Background::Update(int points){
	float maxmovbckspeed = -15; //se asigna un valor máximo a la velocidad (podría ser atributo de la clase)
	
	if(m_bckspeed.x > maxmovbckspeed) //en cada update, compara la velocidad actual del fondo. Mientras sea mayor a la máxima (porque es negativo en eje x), sigue decreciendo
		m_bckspeed.x -= .003f;
	
	for(int i=0;i<5;++i) {  
		m_sprites[i].move((m_bckspeed.x*(i+1))/4,0); //Y para el efecto parallax, cada parte del fondo se mueve a velocidad distinta.
	}
	
	if(points % 300 == 0 && points != 0){
			if(IsDay == true){
				animal.setBuffer(sbowl); animal.play();
			for(int i=0;i<5;++i) m_sprites[i].setTexture(m_texturesnight[i]);
			}
			if(IsDay == false){
				animal.setBuffer(sbrooster); animal.play();
			for(int i=0;i<5;++i) m_sprites[i].setTexture(m_texturesday[i]);
			}
			m_sprites[3].setTexture(m_texturesday[3]);
			IsDay = !IsDay;
		}
}

	
//	switch(points){
//	case 500 : 
//		for(int i=0;i<5;++i)  m_sprites[i].setTexture(m_texturesnight[i]); 
//		break;
//	case 2000 : 
//		for(int i=0;i<5;++i)  m_sprites[i].setTexture(m_texturesday[i]); 
//		break;
//	case 5000 : 
//		for(int i=0;i<5;++i)  m_sprites[i].setTexture(m_texturesnight[i]); 
//		break;
//	case 8000 : 
//		for(int i=0;i<5;++i)  m_sprites[i].setTexture(m_texturesday[i]); 
//		break;
//	}	

void Background::Draw(RenderWindow &window) {
	for(int i=0;i<5;++i) { 
		window.draw(m_sprites[i]); //El fondo simplemente dibuja el vector de sprites propio
	}
}


