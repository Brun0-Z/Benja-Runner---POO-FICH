#include "death_scene.h"
#include "structScore.h"
#include <string>
#include <cstring>
#include "Match.h"
#include "Title.h"
#include <cctype>
using namespace std;

death_scene::death_scene(int points) : inp(m_font){ //Se encarga de crear la escena a partir del puntaje de la partida. inp es el inputbox que recibe una fuente
	m_score = points; //Se guarda el puntaje de la partida
	char fname[4] = "AAA"; //Se crea un nombre auxiliar AAA
	for (int i = 0; i < 3; i++) //Y para cada posición del char 
	{
		aux.m_nick[i]=fname[i]; //Se las guarda en el struct auxiliar
	}
	aux.m_points = 0; //El mismo struct auxiliar tiene puntaje 0
	LoadResources(); //Se cargan los recursos
}

void death_scene::ProcessEvent (Event & evt) { 
	inp.processEvent(evt); //El inputbox procesa el evento(si es de su interés, es un ingreso por teclado)
	
	if(evt.type == Event::KeyPressed && evt.key.code == Keyboard::Return) { //Si se aprieta enter, se cambia el valor del bool al respecto
		m_ReturnPressed = !m_ReturnPressed;
	}
	if(evt.type == Event::KeyPressed && evt.key.code == Keyboard::Up) { //Si se aprieta alguna de las flechas, se recorren las opciones seleccionables
		m_ReturnPressed = false; MenuUp();
	}
	if(evt.type == Event::KeyPressed && evt.key.code == Keyboard::Down) { //idem
		m_ReturnPressed = false; MenuDown(); 
	}
	
}

void death_scene::MenuUp(){ //Básicamente, da contorno a las letras seleccionables de acuerdo a cuál está elegida en el momento
	if(m_selecteditem == 4){
		m_text[m_selecteditem].setOutlineColor(sf::Color::White);
		m_text[m_selecteditem].setOutlineThickness(0.f);
		m_text[m_selecteditem].setFillColor(sf::Color::White);
		
		m_selecteditem--;
		
		m_text[m_selecteditem].setFillColor(sf::Color::White);
		m_text[m_selecteditem].setOutlineColor(sf::Color::Black);
		m_text[m_selecteditem].setOutlineThickness(4.f);
	}
	else{
		if(m_selecteditem == 3) {
			m_text[3].setOutlineColor(sf::Color::White);
			m_text[3].setOutlineThickness(0.f);
			m_text[3].setFillColor(sf::Color::White);
			
			m_selecteditem = 4;
			
			m_text[m_selecteditem].setFillColor(sf::Color::White);
			m_text[m_selecteditem].setOutlineColor(sf::Color::Black);
			m_text[m_selecteditem].setOutlineThickness(4.f);
		}
	}
}
void death_scene::MenuDown(){ //Básicamente, da contorno a las letras seleccionables de acuerdo a cuál está elegida en el momento
	if(m_selecteditem == 3){
		m_text[m_selecteditem].setOutlineColor(sf::Color::White);
		m_text[m_selecteditem].setOutlineThickness(0.f);
		m_text[m_selecteditem].setFillColor(sf::Color::White);
		
		m_selecteditem++;
		
		m_text[m_selecteditem].setOutlineColor(sf::Color::Black);
		m_text[m_selecteditem].setOutlineThickness(4.f);
		m_text[m_selecteditem].setFillColor(sf::Color::White);
	}
	else{
		if(m_selecteditem == 4) {
			m_text[m_selecteditem].setOutlineColor(sf::Color::White);
			m_text[m_selecteditem].setOutlineThickness(0.f);
			m_text[m_selecteditem].setFillColor(sf::Color::White);
			
			m_selecteditem = 3;
			
			m_text[m_selecteditem].setOutlineColor(sf::Color::Black);
			m_text[m_selecteditem].setOutlineThickness(4.f);
			m_text[m_selecteditem].setFillColor(sf::Color::White);
		}
	}
}

void death_scene::Update (Game & game) {
	if(m_ReturnPressed && m_selecteditem == 3) { //Si se selecciona la opción Retry
		m_ReturnPressed = false; 
		string str = inp.getValue(); //Se guarda en un string auxiliar lo que se haya ingresado en la inputbox
		if(str == "" || str.size() != 3)str = "AAA"; //Si llega a ser vacía, se pone un nombre auxiliar AAA 
		strcpy(aux.m_nick,str.c_str()); //Se copia en el struct auxiliar el nombre ingresado por teclado
		structScore add(aux.m_nick,this->m_score); //Se crea entonces l struct correspondiente
		game.Add_NewHighscore(add); //Y se invoca a la función de guardar el puntaje
		game.SetScene(new Match());  //Y directamente se inicia otra partida
	}
	
	if(m_ReturnPressed && m_selecteditem == 4) { //Si se selecciona Menú, idem a lo de arriba, salvo que en vez de una partida, va al menu
		m_ReturnPressed = false;  
		string str = inp.getValue(); 
		if(str == "" || str.size() != 3)str = "AAA";
		for(int i=0;i<str.size();++i) {
			str[i] = toupper(str[i]);
		}
		strcpy(aux.m_nick,str.c_str());
		structScore add(aux.m_nick,this->m_score);
		game.Add_NewHighscore(add); 
		game.SetScene(new Title()); 
	}
	inp.update();
}

void death_scene::Draw (RenderWindow & window) { //Se dibujan los textos y el fondo
	window.clear();
	window.draw(m_background);
	for(int i=0;i<5;++i) { 
		window.draw(m_text[i]);
	}
	window.draw(inp);
}

void death_scene::LoadResources ( ) { //Se cargan imágenes, fondos, se asignan posiciones, etc
	m_tbackground.loadFromFile("sprites/backgroundgame.png");
	m_background.setTexture(m_tbackground);
	m_background.setScale(2,2.35);
	m_background.setColor(Color(255,255,255,80));
	
	m_font.loadFromFile("fonts/Cartoon.ttf"); //Como se usa el mismo fondo en todo el juego, podría ser atributo de la clase juego
	for(int i=0;i<6;++i) { 
		m_text[i].setFont(m_font);
	}
	
	inp.setMaxChars(3);
	inp.setScale(1.8,1.8);
	inp.setPosition(320,380);
	inp.setFillColor({128,128,128});
	inp.setSingleWord(true);
	
	m_text[0].setString("Game Over");
	m_text[1].setString("Your score: "+std::to_string(m_score));
	m_text[2].setString("Insert your name");
	m_text[3].setString("Retry");
	m_text[4].setString("Menu");
	m_text[5].setString("Too short!");
	
	m_text[0].setScale(2.2,2.2);
	m_text[0].setPosition(150,100); //mas a la izq
	
	m_text[1].setPosition(200,250); //mas a la der
	
	m_text[2].setPosition(200,350); //mas a la der
	
	m_text[3].setScale(1.5,1.5);
	m_text[3].setPosition(125,520); //mas izq, mas abajo, mas grande, seleccionable
	m_text[3].setOutlineColor(sf::Color::Black);
	m_text[3].setOutlineThickness(4.f);
	m_text[3].setFillColor(sf::Color::White);
	
	m_text[4].setScale(1.5,1.5);
	m_text[4].setPosition(475,520); //mas der, mas abajo, mas grande, seleccionable
}

