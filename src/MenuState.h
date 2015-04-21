#pragma once
#include "GameState.h"
#include "UI.h"
#include <SFML/System/Clock.hpp>

namespace sf
{
	class Packet;
}
class MenuState : public GameState
{
public:
	MenuState();
	~MenuState();

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


	UI m_ui;

};

