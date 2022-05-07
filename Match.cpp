#include "Match.h"
#include "death_scene.h"
#include "Game.h"
#include <sstream>
#include <string>
#include <SFML/Graphics/Rect.hpp>
using namespace std;

Match::Match() {
	m_txtbck.loadFromFile("backgrounds/backgroundgame.png"); m_txtbck.setRepeated(true);
	m_sprbck.setTexture(m_txtbck); m_sprbck.setTextureRect(IntRect(100,0,999999,1000));
	m_sprbck.setScale(2,2.35);
	
	m_font.loadFromFile("fonts/Cartoon.ttf");
	m_textpoints.setFont(m_font);
	m_textpoints.setString("Points:"); m_textpoints.setPosition(100,100);
	

	
	stringstream ss;
	ss<<m_points;
	string auxs = ss.str();
	m_tpoint.setFont(m_font);
	m_tpoint.setString(auxs);
	m_tpoint.setPosition(275,100);
}

void Match::ProcessEvent (Event & evt) {
	
}

void Match::Update (Game & game) {
	//if(m_maincharacter.CollideWith(m_obstacle)){
		//m_maincharacter.ChangeState();
		m_time = m_clock.getElapsedTime();
		m_clock.restart();
		this->m_points++;
		stringstream ss;
		ss<<m_points;
		string auxs = ss.str();
		m_tpoint.setString(auxs);
		
		m_maincharacter.Update();
		
		m_sprbck.move(-5,0);
}

void Match::Draw (RenderWindow & window) {
	window.clear();
	window.draw(m_sprbck);
	window.draw(m_textpoints);
	window.draw(m_tpoint);
	m_maincharacter.Draw(window);
}

void Match::LoadResources ( ) {
	
}

