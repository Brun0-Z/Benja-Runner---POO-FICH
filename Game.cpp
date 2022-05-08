#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Title.h"
using namespace sf;

Game::Game() : m_window(VideoMode(800,600),"Benja Runner"){	
	m_window.setFramerateLimit(60);
	m_scene = new Title();
}

void Game::Run ( ) {
	Event e;
	while(m_window.isOpen()) {
		while(m_window.pollEvent(e)) {
			if(e.type == sf::Event::Closed){
				m_window.close();	}
			else m_scene->ProcessEvent(e);
		}
		
		m_scene->Update(*this);
		m_scene->Draw(m_window);
		m_window.display();
		
		if (m_next_scene) {
			delete m_scene;
			m_scene = m_next_scene ;
			m_next_scene = nullptr;
		}
	}
}

void Game::CloseGame() {
	m_window.close();
}

void Game::SetScene (Scene * next_scene) {
	m_next_scene = next_scene;
}

Game::~Game(){
	delete m_scene;
	delete m_next_scene;
}
	
