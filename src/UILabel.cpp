#include "UILabel.h"

UILabel::UILabel()
{
	if (m_font)
		m_text.setFont(*m_font);
}

UILabel::UILabel(const std::string & text) : UILabel()
{
	m_text.setString(text);
}

UILabel::~UILabel()
{
}

sf::Text & UILabel::getText()
{
	return m_text;
}

void UILabel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_text, states);
}