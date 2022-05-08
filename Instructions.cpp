#include "Instructions.h"
#include <SFML/Graphics/Color.hpp>
#include "Title.h"
#include <SFML/Window/Event.hpp>
#include "Game.h"
#include "Match.h"

Instructions::Instructions() {
	this->LoadResources();
}

void Instructions::LoadResources(){
	m_tbackground.loadFromFile("backgrounds/backgroundgame.png");
	m_background.setTexture(m_tbackground);
	m_background.setScale(2,2.35);
	m_background.setColor(Color(255,255,255,80));
	
	m_tinst1.loadFromFile("sprites/Instruction1.png");
	m_tinst2.loadFromFile("sprites/Instruction2.png");
	
	m_instru1.setTexture(m_tinst1); m_instru2.setTexture(m_tinst2);
	
	m_instru1.setPosition(40,200); m_instru1.setScale(.4,.4);
	m_instru2.setPosition(420,200); m_instru2.setScale(.4,.4);
	
	m_font.loadFromFile("fonts/Cartoon.ttf");
	for(int i=0;i<4;++i) { 
		m_textinstruction[i].setFont(m_font);
	}
	
	m_textinstruction[0].setString("HOW TO PLAY");m_textinstruction[0].setPosition(100,100); 
	m_textinstruction[0].setFillColor(sf::Color::White); m_textinstruction[0].setCharacterSize(60);
	
	m_textinstruction[1].setString("EVADE OBSTACLES"); m_textinstruction[1].setPosition(40,420);
	m_textinstruction[1].setFillColor(sf::Color::White); m_textinstruction[1].setCharacterSize(25);
	
	m_textinstruction[2].setString("COLLECT COINS");
	m_textinstruction[2].setPosition(450,420);
	m_textinstruction[2].setFillColor(sf::Color::White);
	m_textinstruction[2].setCharacterSize(25);
	
	m_textinstruction[3].setString("PRESS ENTER TO START!!!");
	m_textinstruction[3].setPosition(225,490);
	m_textinstruction[3].setFillColor(sf::Color::White);
	m_textinstruction[3].setCharacterSize(20);
}

void Instructions::ProcessEvent (Event & evt) {
	if(evt.type == Event::KeyPressed && evt.key.code == Keyboard::Escape) {
		m_EscapePressed = !m_EscapePressed; 
	}
	if(evt.type == Event::KeyPressed && evt.key.code == Keyboard::Return) {
		m_ReturnPressed = !m_ReturnPressed;
	}
}

void Instructions::Update (Game & game) {
	if(m_EscapePressed == true) {
		m_EscapePressed = false; game.SetScene(new Title()); 
	}
	if(m_ReturnPressed == true) {
		m_ReturnPressed = false; game.SetScene(new Match());
	}
}

void Instructions::Draw (RenderWindow & window) {
	window.clear();
	window.draw(m_background);
	window.draw(m_instru1); window.draw(m_instru2);
	window.draw(m_textinstruction[0]); 
	window.draw(m_textinstruction[1]);
	window.draw(m_textinstruction[2]);
	window.draw(m_textinstruction[3]);
}

