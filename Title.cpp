#include "Game.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "Title.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Config.hpp>
#include <cstdlib>
#include <SFML/Window/Event.hpp>
#include "Instructions.h"
#include "ScoresMenu.h"

using namespace std;   
using namespace sf;



Title::Title() {
	this->LoadResources();
}

void Title::MenuUp(){
	if(m_selecteditem - 1 > 0){
		m_texts[m_selecteditem].setOutlineColor(sf::Color::White);
		m_texts[m_selecteditem].setOutlineThickness(0.f);
		m_texts[m_selecteditem].setFillColor(sf::Color::White);
		
		m_selecteditem--;
		
		m_texts[m_selecteditem].setFillColor(sf::Color::White);
		m_texts[m_selecteditem].setOutlineColor(sf::Color::Black);
		m_texts[m_selecteditem].setOutlineThickness(4.f);
	}
		else{
			if(m_selecteditem == 1) {
				m_texts[m_selecteditem].setOutlineColor(sf::Color::White);
				m_texts[m_selecteditem].setOutlineThickness(0.f);
				m_texts[m_selecteditem].setFillColor(sf::Color::White);
				
				m_selecteditem = 3;
				
				m_texts[m_selecteditem].setFillColor(sf::Color::White);
				m_texts[m_selecteditem].setOutlineColor(sf::Color::Black);
				m_texts[m_selecteditem].setOutlineThickness(4.f);
		}
	}
}
void Title::MenuDown(){
	if(m_selecteditem + 1 < 4){
		m_texts[m_selecteditem].setOutlineColor(sf::Color::White);
		m_texts[m_selecteditem].setOutlineThickness(0.f);
		m_texts[m_selecteditem].setFillColor(sf::Color::White);
		
		m_selecteditem++;
		m_texts[m_selecteditem].setOutlineColor(sf::Color::Black);
		m_texts[m_selecteditem].setOutlineThickness(4.f);
		m_texts[m_selecteditem].setFillColor(sf::Color::White);
	}
		else{
			if(m_selecteditem == 3) {
				m_texts[m_selecteditem].setOutlineColor(sf::Color::White);
				m_texts[m_selecteditem].setOutlineThickness(0.f);
				m_texts[m_selecteditem].setFillColor(sf::Color::White);
				
				m_selecteditem = 1;
				
				m_texts[m_selecteditem].setOutlineColor(sf::Color::Black);
				m_texts[m_selecteditem].setOutlineThickness(4.f);
				m_texts[m_selecteditem].setFillColor(sf::Color::White);
				
		}
	}
}

void Title::Update (Game &game) {
	unsigned char r = rand();
	unsigned char g = rand();
	unsigned char b = rand();
	m_texts[0].setFillColor({r,g,b});
	
	if(m_ReturnPressed && m_selecteditem == 1) {
		m_ReturnPressed = false; m_music.stop(); game.SetScene(new Instructions()); 
	}
	
	if(m_ReturnPressed && m_selecteditem == 2) {
		m_ReturnPressed = false; m_music.stop(); game.SetScene(new ScoresMenu()); 
	}
	
	if(m_ReturnPressed && m_selecteditem == 3) {
		game.saveScores(); game.CloseGame();
	}
}

void Title::LoadResources(){
	m_texture.loadFromFile("sprites/backgroundmenu.jpg");
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(0.6,0.8);
	
	m_music.openFromFile("music/title.ogg"); 
	m_music.setVolume(5);
	m_music.play();
	m_music.setLoop(true);
	
	m_font.loadFromFile("fonts/Cartoon.ttf");
	m_texts[0].setFont(m_font);	m_texts[1].setFont(m_font);	m_texts[2].setFont(m_font);	m_texts[3].setFont(m_font);
	
	
	m_texts[0].setString("   BENJA \n  RUNNER!"); m_texts[0].setOutlineColor(sf::Color::Black); m_texts[0].setOutlineThickness(4.0f);
	m_texts[0].setFillColor({255,0,0,255}); m_texts[0].setPosition(120,110); m_texts[0].setCharacterSize(60);
	
	m_texts[1].setString("PLAY");m_texts[1].setFillColor(sf::Color::White);
	m_texts[1].setPosition(350,300); m_texts[1].setCharacterSize(30);
	
	m_texts[2].setString("HIGHSCORES"); m_texts[2].setFillColor(sf::Color::White);
	m_texts[2].setPosition(275,400); m_texts[2].setCharacterSize(30);
	
	m_texts[3].setString("EXIT"); m_texts[3].setFillColor(sf::Color::White); 
	m_texts[3].setPosition(355,500); m_texts[3].setCharacterSize(30);
	
	m_texts[1].setOutlineColor(sf::Color::Black);
	m_texts[1].setOutlineThickness(4.f);
	m_ReturnPressed = false;
}

void Title::Draw (RenderWindow & window) {
	window.clear();
	window.draw(m_sprite);
	window.draw(m_texts[0]); window.draw(m_texts[1]);window.draw(m_texts[2]); window.draw(m_texts[3]);
}

void Title::ProcessEvent(Event &evt){
	if(evt.type == Event::KeyPressed && evt.key.code == Keyboard::Up) {
		m_ReturnPressed = false; MenuUp();
	}
	if(evt.type == Event::KeyPressed && evt.key.code == Keyboard::Down) {
		m_ReturnPressed = false; MenuDown(); 
	}
	if(evt.type == Event::KeyPressed && evt.key.code == Keyboard::Return) {
		m_ReturnPressed = !m_ReturnPressed;
	}
}
