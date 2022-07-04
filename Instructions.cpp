#include "Instructions.h"
#include <SFML/Graphics/Color.hpp>
#include "Title.h"
#include <SFML/Window/Event.hpp>
#include "Game.h"
#include "Match.h"

Instructions::Instructions() {
	this->LoadResources(); //Se cargan los recursos
}

void Instructions::LoadResources(){ //Imágenes, fuentes, etc
	m_tbackground.loadFromFile("sprites/backgroundgame.png");
	m_background.setTexture(m_tbackground);
	m_background.setScale(2,2.35);
	m_background.setColor(Color(255,255,255,80));
	
	m_tinst1.loadFromFile("sprites/Instruction1.png");
	
	m_instru1.setTexture(m_tinst1);
	
	m_instru1.setPosition(100,200); m_instru1.setScale(.4,.4);
	
	m_font.loadFromFile("fonts/Cartoon.ttf");
	for(int i=0;i<4;++i) { 
		m_textinstruction[i].setFont(m_font);
	}
	
	m_textinstruction[0].setString("HOW TO PLAY");m_textinstruction[0].setPosition(100,100); 
	m_textinstruction[0].setFillColor(sf::Color::White); m_textinstruction[0].setCharacterSize(60);
	
	m_textinstruction[1].setString("PRESS: \nW OR UP TO JUMP\nS OR DOWN TO FALL\nP TO PAUSE\nEVADE OBSTACLES"); m_textinstruction[1].setPosition(450,200);
	m_textinstruction[1].setFillColor(sf::Color::White); m_textinstruction[1].setCharacterSize(18);
	
	m_textinstruction[3].setString("PRESS ENTER TO START!!!");
	m_textinstruction[3].setPosition(100,520);
	m_textinstruction[3].setFillColor(sf::Color::White);
	m_textinstruction[3].setCharacterSize(30);
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
		m_EscapePressed = false; game.SetScene(new Title()); //Si se aprieta escape, vuelve al menú
	}
	if(m_ReturnPressed == true) {
		m_ReturnPressed = false; game.SetScene(new Match()); //Si se aprieta enter, va a la partida
	}
}

void Instructions::Draw (RenderWindow & window) {
	window.clear();
	window.draw(m_background);
	window.draw(m_instru1);
	for(int i=0;i<4;++i) { 
		window.draw(m_textinstruction[i]);
	}
}

