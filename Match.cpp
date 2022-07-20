#include "Match.h"
#include "death_scene.h"
#include "Game.h"
#include <sstream>
#include <string>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include "Title.h"
#include <cstdlib>
#include "Obstacle.h"
#include <SFML/System/Sleep.hpp>
#include <algorithm>
#include <iostream>
#include <SFML/Graphics/Color.hpp>
using namespace std;

Match::Match() {
	this->LoadResources();
	game_view.reset(FloatRect(0,80, 500, 500)); //Esto es la vista del juego. Es como una cámara. Los valores asignados son como un zoom para el juego
}

void Match::ProcessEvent (Event & evt) {
	if(evt.type == Event::KeyPressed && evt.key.code == Keyboard::P && CanPause == true or evt.type == Event::KeyPressed && evt.key.code == Keyboard::Escape && CanPause == true){
		m_pause = !m_pause; //Se pausa el juego
	}

}

void Match::ObstaclesManager(){ //Esta función asigna el tiempo de esperas entre generación de trampas de acuerdo al puntaje actual
	switch(this->m_points){
	case 300 : 
		m_waittime = .75;
	break;
	case 600 :
		m_waittime = .5;
	break;
	case 1200 : 
		m_waittime = .25;
	break;
	case 1800 : 
		m_waittime = .1;
	break;
	}
}

void Match::SpawnObstacle(){ //Para el spawn de trampas
	m_time1 = m_clock1.getElapsedTime(); //Se toma un tiempo
	if(m_time1.asSeconds() >= m_waittime && m_obstacles.size() < 5){ //Si el tiempo es mayor o igual al de espera, y no hay más de 3 trampas en pantalla
		int m_rand = rand()%8; //Se hace un random entre 0 y 8
		if(m_rand > 2){ //Si el número es mayor a 2 (vease 3,4,5...). OBS: podría usarse otro condicional, como que sea un número par/impar, etc.
			Obstacle m_obs; //Se crea el obstáculo
			m_obstacles.push_back(m_obs); //Y se agrega al vector de obstáculos
		}
		m_clock1.restart(); //Se hace reset del reloj para la siguiente llamada
	}
}

bool out_window(Obstacle &o){ //Esta función sirve para ver si el obstáculo en cuestión está fuera de pantalla. 
	Vector2f pos = o.getPosition(); //Se toma la posición actual del sprite (aunque solo interesa la posición en x, porque en y siempre es la misma)
	if(pos.x <= -100) return true; //El -100 es arbitrario. Debería usarse el borde derecho de la trampa respecto al 0 en x de la pantalla
	return false; //Si no está fuera de pantalla, no se tiene que hacer nada
}

void Match::Update (Game & game) {
	if(!m_pause){ //Mientras el juego no está pausado
		if(m_music.getStatus() == sf::Sound::Paused) m_music.play();
		
		m_tpause.setFillColor({0,0,0,0}); //Se ponen en invisible los textos referente a la pausa
		m_tescape1.setFillColor({0,0,0,0});
		m_tescape2.setFillColor({0,0,0,0});
		
		m_maincharacter.Update(m_background.viewFloor()); //Se invoca el update del jugador pasandole el rectángulo del piso

		
		if(m_maincharacter.CheckState() == true){
		m_background.Update(this->m_points/5); //Se invoca el update del fondo 
		this->SpawnObstacle(); //Se llama a la funcion para invocar obstáculo
		
		float veloc = m_background.getSpeed().x; //Se guarda la velocidad actual del fondo para pasarsela al vector de trampas
		for(int i=0;i<m_obstacles.size();++i) {	
			if(out_window(m_obstacles[i])) m_obstacles.erase(m_obstacles.begin() + i); //Se fija si la trampa está fuera de pantalla y la borra si lo está
			m_obstacles[i].Update(veloc); //Se hace el update de cada trampa de acuerdo a la velocidad del fondo, para moverse a la par
		}
		
		this->m_points++; //Aumenta la puntuación en 1 en cada update 
		string auxs = to_string(m_points/5); //Se pasa el puntaje a string y se lo guarda. Se divide la cantidad de puntos por 5 (porque si no el juego iría muy rápido en cuanto a puntuaciones. Decisión arbitraria.Si el juego tiene 60 FPS, son 60 puntos en un segundo.
		m_tpoint.setString(auxs); //Y este string se usa para mostrar en pantalla	
		
		for(Obstacle obs : m_obstacles){  //Para cada obstáculo
			if(m_maincharacter.CollideWith(obs)) { //Si el personaje choca con uno
				CanPause = false;
				m_close.play();
				m_music.stop();  
				m_maincharacter.ChangeState();
				m_maincharacter.DeathSound();
				obs.CollisionDetected();
				m_clock2.restart();
				}
			}
		}
			else{
			for(int i=0;i<m_obstacles.size();++i) { 
				if(m_obstacles[i].ViewCol() == true){
					m_obstacles[i].Activate();
				}
				break;
			}
			if(m_clock2.getElapsedTime().asSeconds() >= 1){
				game_view.reset(FloatRect(0,0,800,600));
				game.SetScene(new death_scene(this->m_points/5)); //Se pasa a la pantalla de Game Over pasándole los puntos divididos por 5
			}
		}
	}
	else { 
		m_music.pause(); //Si se pausa el juego, se pausa la música y se muestran los textos de pausa
		m_tpause.setFillColor({255,0,0,255});
		m_tescape1.setFillColor({0,0,0,255});
		m_tescape2.setFillColor({0,0,0,255});
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y)){ //Si está pausado y se aprieta la Y, se vuelve al menú principal. No se guardan los puntos
			m_music.stop(); game_view.reset(FloatRect(0,0,800,600)); game.SetScene(new Title()); //Se recupera el view general (no hay zoom por así decirlo)
		}
	}
}


void Match::Draw (RenderWindow & window) { //Se dibujan las cosas en pantalla
	window.clear();
	window.setView(game_view);
	m_background.Draw(window);
	window.draw(m_textpoints);
	window.draw(m_tpoint);
	for(int i=0;i<m_obstacles.size();++i) { m_obstacles[i].Draw(window); }
	m_maincharacter.Draw(window);
	window.draw(m_tpause);
	window.draw(m_tescape1);
	window.draw(m_tescape2);
}

void Match::LoadResources ( ) { //Se cargan imágenes, fuentes, se asignan posiciones, etc
	m_font.loadFromFile("fonts/Cartoon.ttf");
//	m_textpoints.setFont(m_font); m_textpoints.setFillColor(sf::Color::Black);
//	m_textpoints.setString("Points:"); m_textpoints.setPosition(160,150);
//	
	activated.loadFromFile("music/Beartrap.ogg");
	m_close.setBuffer(activated);	
	m_close.setVolume(30);
	
	m_music.openFromFile("music/ingame.ogg"); 
	m_music.setVolume(10);
	m_music.play();
	m_music.setLoop(true);
	
	stringstream ss;
	ss<<m_points;
	string auxs = ss.str();
	m_tpoint.setFont(m_font);
	m_tpoint.setScale(.5,.5);
	m_tpoint.setString(auxs);
	m_tpoint.setPosition(25,100);
	m_tpoint.setFillColor(sf::Color::Black);
	
	m_tpause.setFont(m_font);
	m_tpause.setString("PAUSED!");
	m_tpause.setFillColor({0,0,0,0});
	m_tpause.setPosition(150,300);
	
	m_tescape1.setFont(m_font);
	m_tescape1.setScale(.35,.35);
	m_tescape1.setString("Y to exit to main menu \n P/Escape to resume");
	m_tescape1.setFillColor({0,0,0,0});
	m_tescape1.setPosition(150,500);
	
	m_tescape2.setFont(m_font);
	m_tescape2.setScale(.35,.35);
	m_tescape2.setString("(If you leave the run, you will loss your progress!)");
	m_tescape2.setFillColor({0,0,0,0});
	m_tescape2.setPosition(50,550);
}


