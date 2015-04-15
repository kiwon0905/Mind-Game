#pragma once
#include "UIWidget.h"

class UILabel :public UIWidget<UILabel>
{
public:
	UILabel();
	UILabel(const std::string & text);
	~UILabel();

	sf::Text & getText();

private:
	sf::Text m_text;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

