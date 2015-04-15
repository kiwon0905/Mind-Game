#include "UIButton.h"
#include <iostream>

UIButton::UIButton(const std::string & text, unsigned int height, sf::Color textColor,
	sf::Color outlineColor, sf::Color backgroundColor):
m_pressed(false)
{
	for (std::size_t i = 0; i < Count; ++i)
		m_callbacks.push_back([](){});
	if (m_font)
		m_text.setFont(*m_font);
	m_text.setColor(textColor);


	m_text.setString("p");
	m_background.setSize(sf::Vector2f(m_text.getLocalBounds().width, static_cast<float>(height)));
	m_text.setCharacterSize(height);
	while (m_text.getLocalBounds().top + m_text.getLocalBounds().height >
		m_background.getLocalBounds().top + m_background.getLocalBounds().height)
		m_text.setCharacterSize(m_text.getCharacterSize() - 1);
	m_text.setString(text);
	m_background.setSize(sf::Vector2f(m_text.getLocalBounds().width, static_cast<float>(height)));
	
	
	m_background.setFillColor(backgroundColor);
	m_background.setOutlineColor(outlineColor);
	m_background.setOutlineThickness(3);
}

UIButton::~UIButton()
{
}

sf::Text & UIButton::getText()
{
	return m_text;
}

void UIButton::setCallback(Event ev, Callback callback)
{
	m_callbacks[ev] = callback;
}

bool UIButton::contains(int x, int y) const
{
	return getTransform().transformRect(m_background.getGlobalBounds()).contains(static_cast<float>(x), static_cast<float>(y));
}

void UIButton::handleEvent(sf::Event & ev)
{
	if (ev.type == sf::Event::MouseButtonPressed)
	{
		if (contains(ev.mouseButton.x, ev.mouseButton.y))
		{
			m_callbacks[Press]();
			m_pressed = true;
		}

	}
	else if (ev.type == sf::Event::MouseButtonReleased)
	{
		if (contains(ev.mouseButton.x, ev.mouseButton.y))
			m_callbacks[Click]();
		else if (m_pressed)
			m_callbacks[Release]();
	}

}

void UIButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_background, states);
	target.draw(m_text, states);

}