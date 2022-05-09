#include "Match.h"
#include "death_scene.h"
#include "Game.h"
#include <sstream>
#include <string>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include "Title.h"
using namespace std;

Match::Match() {
	this->LoadResources();
}

void Match::ProcessEvent (Event & evt) {
	if(evt.type == Event::KeyPressed && evt.key.code == Keyboard::P){
		m_pause = !m_pause;
	}
	if(evt.type == Event::KeyPressed && evt.key.code == Keyboard::Escape){
		m_EscapePressed = !m_EscapePressed;
	}
}

void Match::Update (Game & game) {
	if(!m_pause){
	//if(m_maincharacter.CollideWith(m_obstacle)){
		//m_maincharacter.ChangeState();
		m_tpause.setFillColor({0,0,0,0});
		m_time = m_clock.getElapsedTime();
		m_clock.restart();
		this->m_points++;
		stringstream ss;
		ss<<m_points;
		string auxs = ss.str();
		m_tpoint.setString(auxs);
		
		m_maincharacter.Update();
		
		m_bckspeed.x -= .002;
		m_sprbck.move(m_bckspeed.x,0);
	} else { 
		m_tpause.setFillColor({0,0,0,255});
	}
	
	if(m_EscapePressed) game.SetScene(new Title()); 
}

void Match::Draw (RenderWindow & window) {
	window.clear();
	window.draw(m_sprbck);
	window.draw(m_textpoints);
	window.draw(m_tpoint);
	window.draw(m_tpause);
	m_maincharacter.Draw(window);
}

void Match::LoadResources ( ) {
	m_txtbck.loadFromFile("backgrounds/backgroundgame.png"); m_txtbck.setRepeated(true);
	m_sprbck.setTexture(m_txtbck); m_sprbck.setTextureRect(IntRect(100,0,999999,1000));
	m_sprbck.setScale(2,2.35);
	
	m_font.loadFromFile("fonts/Cartoon.ttf");
	m_textpoints.setFont(m_font); m_textpoints.setFillColor(sf::Color::Black);
	m_textpoints.setString("Points:"); m_textpoints.setPosition(500,50);
	
	m_bckspeed.x = -2;
	
	stringstream ss;
	ss<<m_points;
	string auxs = ss.str();
	m_tpoint.setFont(m_font);
	m_tpoint.setString(auxs);
	m_tpoint.setPosition(675,50);
	m_tpoint.setFillColor(sf::Color::Black);
	
	m_tpause.setFont(m_font);
	m_tpause.setString("PAUSED!");
	m_tpause.setFillColor({0,0,0,0});
	m_tpause.setPosition(300,300);
}

