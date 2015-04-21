#include "Game.h"


Game::Game():
m_currentRound(1)
{
	m_me.resize(10);
	m_enemy.resize(10);	
	
	UITextBox::Ptr enterTextBox = UITextBox::create(40, 20);
	enterTextBox->setPosition({ 180, 500 });
	m_ui.add("enterTextBox", enterTextBox);

	float y = 100.f;
	for (std::size_t i = 0; i < 10; ++i)
	{
		UILabel::Ptr label = UILabel::create(std::to_string(i)+")    ");
		label->setPosition(100.f, y);
		label->getText().setCharacterSize(20);
		label->getText().setStyle(sf::Text::Underlined);
		y += 30.f;
		m_ui.add("label" + std::to_string(i), label);
	}
	
	y = 100.f;
	for (std::size_t i = 0; i < 10; ++i)
	{
		UILabel::Ptr label = UILabel::create(std::to_string(i)+")    ");
		label->setPosition(250.f, y);
		label->getText().setCharacterSize(20);
		label->getText().setStyle(sf::Text::Underlined);
		y += 30.f;
		m_ui.add("label2" + std::to_string(i), label);
	}

}

Game::~Game()
{

}

void Game::handleEvent(sf::Event & ev)
{
	m_ui.handleEvent(ev);
}
void Game::handlePacket(sf::Packet & packet)
{

}
void Game::update(float dt)
{
	m_ui.update(dt);
}
void Game::draw(sf::RenderWindow & window)
{
	window.draw(m_ui);
}