#include "UITextBox.h"

#include <iostream>
UITextBox::UITextBox(unsigned int width, unsigned int height, sf::Color outline, sf::Color background):
m_active(false), 
m_elapsed(0),
m_blinkVisible(false),
m_background(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)))
{
	if (m_font)
		m_text.setFont(*m_font);
	m_text.setColor(sf::Color::Black);

	m_background.setFillColor(background);
	m_background.setOutlineColor(outline);

	m_text.setString("p");
	m_text.setCharacterSize(height);
	while (m_text.getLocalBounds().top + m_text.getLocalBounds().height > 
		m_background.getLocalBounds().top + m_background.getLocalBounds().height)
		m_text.setCharacterSize(m_text.getCharacterSize()-1);
	m_text.setString("");


	m_background.setOutlineThickness(3);

	m_blink.setSize(sf::Vector2f(2, height * .9f));
	m_blink.setFillColor(sf::Color::Black);
}

UITextBox::~UITextBox()
{
}

void UITextBox::setString(const std::string & s)
{
	m_string = s;
}
#include <iostream>
void UITextBox::handleEvent(sf::Event & ev)
{
	if (ev.type == sf::Event::MouseButtonPressed )
	{
		bool previousActive = m_active;
		m_active = contains(ev.mouseButton.x, ev.mouseButton.y);
	
		if (m_active && !previousActive)
			m_blinkVisible = true;
	}



	if (ev.type == sf::Event::TextEntered && m_active)
	{
		char code = static_cast<char>(ev.text.unicode);
		
		if (code == 13)//enter
		{
			//onEnter(buffer);
			//buffer.clear();
		}

		else if (code != '\b')
			m_string.push_back(code);
		else if (code == '\b')
		{
			if (m_string.size()>0)
				m_string.pop_back();
		}
	}
}

void UITextBox::update(float dt)
{
	m_text.setString(m_string);
	if (m_text.getLocalBounds().left + m_text.getLocalBounds().width > 
		m_background.getLocalBounds().left + m_background.getLocalBounds().width)
	{
		m_string.pop_back();
		m_text.setString(m_string);
	}
	m_blink.setPosition(m_text.getPosition().x + m_text.getLocalBounds().width + 3, 
		m_text.getPosition().y + m_background.getSize().y * .05f );

	if (m_active)
	{
		m_elapsed += dt;
		if (m_elapsed > 0.5)
		{
			m_elapsed = 0;
			m_blinkVisible = !m_blinkVisible;
		}
	}

}

void UITextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_background, states);
	target.draw(m_text, states);
	
	if (m_active && m_blinkVisible)
		target.draw(m_blink, states);
}

sf::Text & UITextBox::getText()
{
	return m_text;
}

sf::RectangleShape & UITextBox::getRect()
{
	return m_background;
}

bool UITextBox::contains(int x, int y) const
{
	return getTransform().transformRect(m_background.getGlobalBounds()).contains(static_cast<float>(x), static_cast<float>(y));
}