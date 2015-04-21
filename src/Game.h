#pragma once
#include <SFML/System.hpp>
#include <vector>
#include "UI.h"

namespace sf
{
	class RenderWindow;
	class Packet;
}
class Game
{
public:
	Game();
	~Game();

	void handleEvent(sf::Event & ev);	
	void handlePacket(sf::Packet & packet);
	void update(float dt);
	void draw(sf::RenderWindow & window);
private:
	std::vector<sf::Int32> m_me;
	std::vector<sf::Int32> m_enemy;
	sf::Int32 m_currentRound;

	UI m_ui;
};

