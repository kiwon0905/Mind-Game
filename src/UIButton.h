#pragma once
#include <functional>
#include <vector>
#include "UIWidget.h"

class UIButton : public UIWidget<UIButton>
{
public:
	typedef std::function<void()> Callback;
	enum Event
	{
		Press,
		Click,
		Release,
		Count
	};
	UIButton(const std::string & text, unsigned int height, sf::Color textColor = sf::Color::Black,
		sf::Color outlineColor = sf::Color::Transparent, sf::Color backgroundColor = sf::Color::Transparent);
	~UIButton();

	sf::Text & getText();
	void setCallback(Event ev, Callback callback);

	virtual void handleEvent(sf::Event & ev);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	bool contains(int x, int y) const;
	bool m_pressed;
	sf::Text m_text;
	sf::RectangleShape m_background;
	std::vector<Callback> m_callbacks;
};

