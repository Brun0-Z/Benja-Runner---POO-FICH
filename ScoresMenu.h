#ifndef SCORES_H
#define SCORES_H
#include "Scene.h"
#include <vector>
#include <string>
#include "structScore.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
using namespace std;

class ScoresMenu : public Scene{
public:
	ScoresMenu(); 
	void Update(Game &game) override; 
	void Draw(RenderWindow &window) override; 
	void ProcessEvent(Event &evt) override;
	void LoadResources() override;
	~ScoresMenu();
private:
	bool m_EscapePressed = false;
	
	Font m_font;
	
	Text m_textscores, m_back;
	
	Texture m_background, m_title, m_t1, m_t2, m_t3;
	
	Sprite s_title, background, s;
	
	Text m_names[5];
	Text m_scores[5];
	vector<Sprite> m_trophies;
};
#endif
