#pragma once
#include <SFML/System.hpp>
#include <vector>
#include "UI.h"

class Application;
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

	void init(Application & app);
	void handleEvent(sf::Event & ev);	
	void handlePacket(sf::Packet & packet);
	void update(float dt);
	void draw(sf::RenderWindow & window);
private:
	void setValue(bool me, sf::Int32 round, sf::Int32 value);

	std::vector<sf::Int32> m_me;
	std::vector<sf::Int32> m_enemy;
	sf::Int32 m_currentRound;

	UI m_ui;
};

