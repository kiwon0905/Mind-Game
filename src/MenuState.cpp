#include "MenuState.h"
#include "Application.h"

#include <iostream>

MenuState::MenuState()
{
}


MenuState::~MenuState()
{
}

void MenuState::onEnter(Application & app)
{
	app.getWindow().create(sf::VideoMode(800, 600), "Mind Game");

}
void MenuState::handleEvent(Application & app)
{
	sf::Event ev;

	while (app.getWindow().pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)
			app.quit();
		m_UI.handleEvent(ev);

	}
	handlePackets(app);

}
void MenuState::update(Application & app)
{
	m_UI.update(app.TIME_STEP.asSeconds());



}
void MenuState::draw(Application & app)
{
	sf::RenderWindow & window = app.getWindow();
	window.clear();
	window.draw(m_UI);
	window.display();
}
void MenuState::onExit(Application & app)
{

}
void MenuState::onObscure(Application & app)
{

}
void MenuState::onReveal(Application & app)
{

}

void MenuState::handlePackets(Application & app)
{
	sf::TcpSocket & socket = app.getSocket();

	sf::Packet packet;
	sf::Socket::Status s = socket.receive(packet);

	while (s == sf::Socket::Done)
	{
		handlePacket(app, packet);
		packet.clear();
		s = socket.receive(packet);
	}
}

void MenuState::handlePacket(Application & app, sf::Packet & packet)
{

}