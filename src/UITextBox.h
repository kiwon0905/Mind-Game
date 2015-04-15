#pragma once
#include "UIWidget.h"

class UITextBox : public UIWidget<UITextBox>
{
public:
	UITextBox(unsigned int width, unsigned int height, sf::Color outline = sf::Color::Transparent, sf::Color background = sf::Color::White);
	~UITextBox(); 

	virtual void handleEvent(sf::Event & ev);
	virtual void update(float dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setString(const std::string & s);
	sf::Text & getText();
private:
	bool contains(int x, int y) const;

	std::string m_string;
	sf::Text m_text;
	sf::RectangleShape m_background;
	sf::RectangleShape m_blink;
	bool m_blinkVisible;
	bool m_active;
	float m_elapsed;

};

