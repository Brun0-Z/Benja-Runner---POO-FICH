#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Title.h"
#include <fstream>
#include <iostream>
using namespace std;
using namespace sf;

Game::Game() : m_window(VideoMode(800,600),"Benja Runner"){	
	m_window.setFramerateLimit(60); //Fijar el límite de FPS en 60
	this->InitHighScore(); //Invoca a la función que abre el archivo de puntos
	m_scene = new Title(); //Y pone que la primer escena sea la del título(menu)
	
}

void Game::Run ( ) {
	Event e; //Se crea un evento
	while(m_window.isOpen()) { //Mientras esté abierta la ventana
		while(m_window.pollEvent(e)) { //y mientras se puedan ejecutar eventos
			if (e.type == sf::Event::Closed){ //si se aprieta la cruz 
				this->saveScores(); //se guardan los scores
				this->m_window.close(); //y se cierra la ventana
			}
			else m_scene->ProcessEvent(e); //si es un evento de otro tipo, lo procesa
		}
		
		m_scene->Update(*this); //La escena hace un update 
		m_scene->Draw(m_window); //y dibuja la ventana
		m_window.display(); //para mostrarla
		
		if (m_next_scene) { //si se intenta pasar a otra escena
			delete m_scene; //borra la actual
			m_scene = m_next_scene ; //y se hace el cambio de escena
			m_next_scene = nullptr; //no sin antes invalidar el puntero de siguiente escena
		}
	}
}

void Game::CloseGame() {
	m_window.close(); //Cierra la ventana 
}

void Game::SetScene (Scene * next_scene) {
	m_next_scene = next_scene; //La función recibe un puntero a la siguinte escena, y se encarga de guardarlo en la variable local
}


void Game::InitHighScore ( ) {
fstream m_archivo("bin/HighScores.bin",ios::binary|ios::in|ios::ate); //Se abre el archivo de puntajes, en binario, para lectura 
if(!m_archivo){ //Si no se puede abrir
	cerr << "Initializing binary..." ; 
	fstream newarchivo("bin/HighScores.bin",ios::trunc|ios::binary|ios::out); //Lo crea
	
	for (int i = 0; i < 5; i++){ //Se crean 5 posiciones con
		char caux[3] = "--"; //Un char de tamaño 3 
		structScore aux(caux,0); //Se crea una puntuación, con el nombre auxiliar y puntuación cero
		m_highscores.push_back(aux); //Se agrega la puntuación al vector de puntajes
		newarchivo.write(reinterpret_cast<char*>(&aux),sizeof(structScore)); //Se escribe en el archivo la puntuación
	}
	newarchivo.close();
}
int can = m_archivo.tellg()/sizeof(structScore); //Se calcula la cantidad de puntajes a leer
m_archivo.seekg(0); //Y se vuelve a la pos 0

structScore aux; //Se hace una puntuación auxiliar
for(int i=0; i<can;++i){ //Y un for que va desde cero a la cantidad de puntajes
	m_archivo.read(reinterpret_cast<char*>(&aux),sizeof(structScore)); //se los lee
	m_highscores.push_back(aux); //se los guarda en el vector
	if(m_highscores.size()>5){ //Y si se pasa de 5 puntajes tira error
		cerr << "Incorrect amount of scores";
	}
}
m_archivo.close();
}


void Game::Add_NewHighscore(structScore m_newscore){ //Para agregar un score, se recibe un puntaje
	for(int i=0;i<m_highscores.size();++i) { //Y se recorre el vector
		if(m_highscores[i] < m_newscore){ //Si encuentra un puntaje menor al recibido
			m_highscores.push_back(m_newscore); //Se hace push_back con el nuevo puntaje
			sort(m_highscores.begin(),m_highscores.end()); //Se hace un sort para ordenarlos
			reverse(m_highscores.begin(),m_highscores.end()); //Y un reverse para ponerlos de menor a mayor
			m_highscores.pop_back(); //Eliminando el último de la lista (porque si no son 6)
			saveScores();//y se guarda en el archivo
			break; //Hace un break después de encontrar el primer puntaje menor porque si no seguiría recorriendo el vector
		}
	}
}

vector<structScore> Game::getHighScores(){ //Función que devuelve el vector de puntuaciones (usado en la pantalla de puntuaciones)
	saveScores();
	return this->m_highscores;
}

void Game::saveScores(){
	ofstream file("bin/HighScores.bin",ios::ate|ios::binary|ios::out|ios::trunc); //Se abre el archivo para escritura 
	
	for(size_t i=0; i<m_highscores.size();++i){ //Se recorre el vector de puntajes
		structScore aux = m_highscores[i]; //se crea un struct auxiliar que toma los valores del puntaje de la posición i
		file.write(reinterpret_cast<char*>(&aux),sizeof(structScore)); //para finalmente guardarlo en el archivo
	}
	
	file.close(); //se cierra el archivo
}

Game::~Game(){ //el destructor de juego borra la escena y la siguiente escena
	delete m_scene; 
	delete m_next_scene;
}
	
