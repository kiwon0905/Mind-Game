#include "UI.h"

void UI::setFont(sf::Font & font)
{
	UIbaseWidget::m_font = &font;
}

void UI::add(const std::string & id, UIbaseWidget::Ptr widget)
{
	m_widgets[id]=widget;
}

void UI::remove(const std::string & id)
{
	m_widgets.erase(id);
}

void UI::handleEvent(sf::Event & ev)
{
	for (auto widget : m_widgets)
		widget.second->handleEvent(ev);
}

void UI::update(float dt)
{
	for (auto widget : m_widgets)
		widget.second->update(dt);
}

void UI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto & pair : m_widgets)
		target.draw(*pair.second, states);
}