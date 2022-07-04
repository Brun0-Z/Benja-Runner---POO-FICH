#include "ScoresMenu.h"
#include <fstream>
#include <iostream>
#include "Game.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Title.h"
using namespace std;

ScoresMenu::ScoresMenu(){
 this->LoadResources(); 
}
	
void ScoresMenu::Update(Game &g){
	if(m_EscapePressed == true) {
		m_EscapePressed = false; g.SetScene(new Title());  //Vuelve al menú principal
	}
	
	vector<structScore> highscore = g.getHighScores(); //Se carga el vector de puntuaciones 
	sort(highscore.begin(),highscore.end()); reverse(highscore.begin(),highscore.end()); //Se las ordena de mayor a menor
	for(int i=0;i<3;++i){
		m_trophies[i].setScale(0.08,0.08);
		m_trophies[i].setPosition(100,300+(i*50)); //Se ponen los tres trofeos (para el podio) 
	}
	
	for (int i=0;i<highscore.size();i++){ //Y se asignan los nombres y los puntajes a cada struct 
		m_names[i].setString(string(highscore[i].m_nick));
		m_scores[i].setString(to_string(highscore[i].m_points));
		m_names[i].setScale(1.5,1);
		m_names[i].setPosition(250,300+(i*50));
		m_scores[i].setScale(1.5,1);
		m_scores[i].setPosition(500,300+(i*50));
	}
}
void ScoresMenu::Draw(RenderWindow &window){ //Se dibuja en pantalla trofeos, textos, etc
	window.clear();
	window.draw(background);
	window.draw(m_textscores);
	window.draw(s_title);
	for(size_t i=0;i<m_trophies.size();++i){
		window.draw(m_trophies[i]);
	}
	for(size_t i=0;i<5;++i){
		window.draw(m_names[i]);
		window.draw(m_scores[i]);
	}
}

void ScoresMenu::ProcessEvent(Event &evt){
	if(evt.type == Event::KeyPressed && evt.key.code == Keyboard::Escape) {
		m_EscapePressed = !m_EscapePressed; 
	}
}

void ScoresMenu::LoadResources(){
	m_font.loadFromFile("fonts/Cartoon.ttf");
	for(int i=0;i<5;++i)  m_names[i].setFont(m_font); 
	for(int i=0;i<5;++i)  m_scores[i].setFont(m_font); 
	m_textscores.setFont(m_font); m_back.setFont(m_font);
	
	m_t1.loadFromFile("sprites/Trophies/gold_trophy.png"); s.setTexture(m_t1); m_trophies.push_back(s);
	m_t2.loadFromFile("sprites/Trophies/silver_trophy.png");s.setTexture(m_t2); m_trophies.push_back(s);
	m_t3.loadFromFile("sprites/Trophies/bronze_trophy.png");s.setTexture(m_t3); m_trophies.push_back(s);
	
	m_background.loadFromFile("sprites/backgroundmenu.jpg"); background.setTexture(m_background);
	
	m_title.loadFromFile("sprites/highscore_title.png"); s_title.setTexture(m_title);
	
	m_textscores.setString("TOP 5");
	m_textscores.setScale(1.2,1.2);
	m_textscores.setPosition(300,250);
	
	background.setScale(0.6,0.8);	background.setColor(Color(255,255,255,80));
	
	s_title.setPosition(200,0);
}
