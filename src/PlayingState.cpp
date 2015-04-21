#include "PlayingState.h"
#include "Application.h"
#include "NetProtocol.h"

PlayingState::PlayingState()
{
}


PlayingState::~PlayingState()
{
}

void PlayingState::onEnter(Application & app)
{
	
}

void PlayingState::handlePackets(Application & app)
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

void PlayingState::handlePacket(Application & app, sf::Packet & packet)
{
	sf::Int32 t;
	packet >> t;
	if (t == Game)
	{
		m_game.handlePacket(packet);
	}

}

void PlayingState::handleEvent(Application & app)
{
	sf::Event ev;

	while (app.getWindow().pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)
			app.quit();
		m_game.handleEvent(ev);
	}
	handlePackets(app);
}
void PlayingState::update(Application & app)
{
	m_game.update(app.TIME_STEP.asSeconds());
}
void PlayingState::draw(Application & app)
{
	sf::RenderWindow & window = app.getWindow();
	window.clear();
	m_game.draw(window);
	window.display();
}
void PlayingState::onExit(Application & app)
{

}
void PlayingState::onObscure(Application & app)
{

}
void PlayingState::onReveal(Application & app)
{

}


