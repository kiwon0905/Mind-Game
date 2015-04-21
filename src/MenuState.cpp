#include "MenuState.h"
#include "PlayingState.h"
#include "Application.h"

#include <Windows.h>
#include <iostream>
#include "NetProtocol.h"
MenuState::MenuState()
{
}


MenuState::~MenuState()
{
}

void MenuState::onEnter(Application & app)
{
	sf::Font & consolas = *app.getFonts().get("C:/Windows/Fonts/consola.ttf");
	m_ui.setFont(consolas);


	char szHostName[255];
	::gethostname(szHostName, 255);
	struct hostent *host_entry;
	host_entry = ::gethostbyname(szHostName);
	std::string ip = ::inet_ntoa(*(struct in_addr *)*host_entry->h_addr_list);
	UILabel::Ptr ipLabel = UILabel::create(ip);
	ipLabel->setPosition(80, 50);
	m_ui.add("ipLabel", ipLabel);

	UITextBox::Ptr inviteTextBox = UITextBox::create(110, 20);
	inviteTextBox->setPosition(80, 200);
	inviteTextBox->setString("localhost");
	inviteTextBox->getRect().setOutlineColor(sf::Color::Blue);
	inviteTextBox->getRect().setOutlineThickness(2);
	m_ui.add("inviteTextBox", inviteTextBox);

	UIButton::Ptr inviteButton = UIButton::create("Invite", 20, sf::Color::White);
	inviteButton->setPosition(200, 200);
	auto onInvitePress = [this]()
	{
		m_ui.get<UIButton>("inviteButton")->getText().setColor(sf::Color::Yellow);
	};
	auto onInviteClick = [this, &app]()
	{
		m_ui.get<UIButton>("inviteButton")->getText().setColor(sf::Color::White);

		sf::String ip = m_ui.get<UITextBox>("inviteTextBox")->getText().getString();

		//if (app.getSocket().getRemotePort == 0)
			app.getSocket().connect(ip.toAnsiString(), app.PORT);
	};
	auto onInviteRelease = [this]()
	{
		m_ui.get<UIButton>("inviteButton")->getText().setColor(sf::Color::White);
	};
	inviteButton->setCallback(UIButton::Press, onInvitePress);
	inviteButton->setCallback(UIButton::Click, onInviteClick);
	inviteButton->setCallback(UIButton::Release, onInviteRelease);
	m_ui.add("inviteButton", inviteButton);


	UITextBox::Ptr joinTextBox = UITextBox::create(110, 20);
	joinTextBox->setPosition(80, 250);
	joinTextBox->getRect().setOutlineColor(sf::Color::Blue);
	joinTextBox->getRect().setOutlineThickness(2);
	m_ui.add("joinTextBox", joinTextBox);

	UIButton::Ptr joinAcceptButton = UIButton::create("Accept", 20, sf::Color::White);
	joinAcceptButton->setPosition(200, 250);
	auto onJoinAcceptPress = [this]()
	{
		m_ui.get<UIButton>("joinAcceptButton")->getText().setColor(sf::Color::Yellow);
	};
	auto onJoinAcceptClick = [this, &app]()
	{
		m_ui.get<UIButton>("joinAcceptButton")->getText().setColor(sf::Color::White);

		if (app.getSocket().getRemotePort() != 0)
		{
			sf::Packet packet;
			packet << Accept;
			app.getSocket().send(packet);
			app.push(new PlayingState);
		}

	};
	auto onJoinAcceptRelease = [this]()
	{
		m_ui.get<UIButton>("joinAcceptButton")->getText().setColor(sf::Color::White);
	};
	joinAcceptButton->setCallback(UIButton::Press, onJoinAcceptPress);
	joinAcceptButton->setCallback(UIButton::Click, onJoinAcceptClick);
	joinAcceptButton->setCallback(UIButton::Release, onJoinAcceptRelease);
	m_ui.add("joinAcceptButton", joinAcceptButton);


	UIButton::Ptr joinDeclineButton = UIButton::create("Decline", 20, sf::Color::White);
	joinDeclineButton->setPosition(260, 250);
	auto onJoinDeclinePress = [this]()
	{
		m_ui.get<UIButton>("joinDeclineButton")->getText().setColor(sf::Color::Yellow);
	};
	auto onJoinDeclineClick = [this, &app]()
	{
		m_ui.get<UIButton>("joinDeclineButton")->getText().setColor(sf::Color::White);
		m_ui.get<UITextBox>("joinTextBox")->setString("");
		if (app.getSocket().getRemotePort() != 0)
		{
			sf::Packet packet;
			packet << Decline;
			app.getSocket().send(packet);
			app.getSocket().disconnect();
		}

	};
	auto onJoinDeclineRelease = [this]()
	{
		m_ui.get<UIButton>("joinDeclineButton")->getText().setColor(sf::Color::White);
	};
	joinDeclineButton->setCallback(UIButton::Press, onJoinDeclinePress);
	joinDeclineButton->setCallback(UIButton::Click, onJoinDeclineClick);
	joinDeclineButton->setCallback(UIButton::Release, onJoinDeclineRelease);
	m_ui.add("joinDeclineButton", joinDeclineButton);





	UIButton::Ptr exitButton = UIButton::create("Exit", 20, sf::Color::White);
	exitButton->setPosition(200, 300);
	auto onExitPress = [this]()
	{
		m_ui.get<UIButton>("exitButton")->getText().setColor(sf::Color::Blue);
	};
	auto onExitClick = [&app]()
	{
		app.quit();
	};
	auto onExitRelease = [this]()
	{
		m_ui.get<UIButton>("exitButton")->getText().setColor(sf::Color::White);
	};
	exitButton->setCallback(UIButton::Press, onExitPress);
	exitButton->setCallback(UIButton::Click, onExitClick);
	exitButton->setCallback(UIButton::Release, onExitRelease);
	m_ui.add("exitButton", exitButton);


	

}
void MenuState::handleEvent(Application & app)
{
	sf::Event ev;

	while (app.getWindow().pollEvent(ev))
	{
		if (ev.type == sf::Event::Closed)
			app.quit();
		m_ui.handleEvent(ev);

	}
	if (app.getSocket().getRemotePort() != 0)
		handlePackets(app);

}
void MenuState::update(Application & app)
{
	m_ui.update(app.TIME_STEP.asSeconds());

	sf::TcpSocket & opponent = app.getSocket();

	static sf::IpAddress prev = sf::IpAddress::None;
	static sf::IpAddress now = sf::IpAddress::None; 


	if (app.c == 'y' &&	sf::Socket::Done == app.getListener().accept(app.getSocket()))
	{
		std::cout <<"remote ip: "<< app.getSocket().getRemoteAddress() << "port: " << app.getSocket().getRemotePort() << "\n";

		m_ui.get<UITextBox>("joinTextBox")->setString(app.getSocket().getRemoteAddress().toString());

	}


}
void MenuState::draw(Application & app)
{
	sf::RenderWindow & window = app.getWindow();
	window.clear();
	window.draw(m_ui);
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
	sf::Int32 t;
	packet >> t;
	if (t == Accept)
	{
		std::cout << "invitation accepted\n";
		app.push(new PlayingState);
	}

	else if (t == Decline)
	{
		std::cout << "invitation declined\n";
		app.getSocket().disconnect();
	}

}