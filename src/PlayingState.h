#pragma once

#include "GameState.h"
#include "Game.h"

#include <string>

class Application;
namespace sf
{
	class Packet;
}

class PlayingState : public GameState
{
public:
	PlayingState();
	~PlayingState();

	virtual void onEnter(Application & app);
	virtual void handleEvent(Application & app);
	virtual void update(Application & app);
	virtual void draw(Application & app);
	virtual void onExit(Application & app);
	virtual void onObscure(Application & app);
	virtual void onReveal(Application & app);

private:
	void handlePackets(Application & app);
	void handlePacket(Application & app, sf::Packet & packet);

	class Game m_game;
};

