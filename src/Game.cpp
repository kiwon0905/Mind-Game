#include "Game.h"
#include "Application.h"
#include "NetProtocol.h"

#include <iostream>

Game::Game():
m_currentRound(1),
m_remainingPoints(100)
{
}

Game::~Game()
{

}

void Game::init(Application & app)
{
	for (std::size_t i = 0; i < 10; ++i)
	{
		m_me.push_back(-1);
		m_enemy.push_back(-1);
	}


	UILabel::Ptr youLabel = UILabel::create("You");
	youLabel->setPosition(100.f, 70.f);
	youLabel->getText().setCharacterSize(20);
	m_ui.add("youLabel", youLabel);

	UILabel::Ptr opponentLabel = UILabel::create("Oppponent");
	opponentLabel->setPosition(200.f, 70.f);
	opponentLabel->getText().setCharacterSize(20);
	m_ui.add("opponentLabel", opponentLabel);
	float y = 100.f;
	for (std::size_t i = 0; i < 10; ++i)
	{
		std::string s = std::to_string(i + 1) + ")    ";
		s.resize(6);
		UILabel::Ptr label = UILabel::create(s);
		label->setPosition(100.f, y);
		label->getText().setCharacterSize(20);
		label->getText().setStyle(sf::Text::Underlined);
		y += 30.f;
		m_ui.add("label" + std::to_string(i+1), label);
	}

	y = 100.f;
	for (std::size_t i = 0; i < 10; ++i)
	{
		std::string s = std::to_string(i + 1) + ")    ";
		s.resize(6);
		UILabel::Ptr label = UILabel::create(s);
		label->setPosition(250.f, y);
		label->getText().setCharacterSize(20);
		label->getText().setStyle(sf::Text::Underlined);
		y += 30.f;
		m_ui.add("olabel" + std::to_string(i+1), label);
	}

	UITextBox::Ptr submitTextBox = UITextBox::create(40, 20);
	submitTextBox->setPosition({ 150, 500 });
	m_ui.add("submitTextBox", submitTextBox);

	UIButton::Ptr submitButton = UIButton::create("submit", 20, sf::Color::White);
	submitButton->setPosition(200.f, 500.f);
	m_ui.add("submitButton", submitButton);

	auto onSubmitPress = [this]()
	{
		m_ui.get<UIButton>("submitButton")->getText().setColor(sf::Color::Yellow);
	};
	auto onSubmitClick = [this, &app]()
	{
		m_ui.get<UIButton>("submitButton")->getText().setColor(sf::Color::White);
		
		if (m_currentRound > 10)
			return;
		if (m_currentRound == 1 || m_enemy[m_currentRound - 2] != -1)
		{
			sf::Int32 n;
	
	
			try
			{
				n = std::stoi(m_ui.get<UITextBox>("submitTextBox")->getText().getString().toAnsiString());
				if (n > m_remainingPoints || n<0)
					return;
			}
			catch (...){ std::cout << "fucked"; return; }
			sf::Packet packet;
			packet << Packet::Game << m_currentRound << n;
			m_remainingPoints -= n;
			m_ui.get<UILabel>("remainingPoints")->getText().setString("Remaining Points: " + std::to_string(m_remainingPoints));
			setValue(true, m_currentRound, n);
			app.getSocket().send(packet);
			++m_currentRound;

			if (m_remainingPoints == 0)
			{
				m_ui.get<UITextBox>("submitTextBox")->setString("0");
			}
		}
	};
	auto onSubmitRelease = [this]()
	{
		m_ui.get<UIButton>("submitButton")->getText().setColor(sf::Color::White);
	};
	submitButton->setCallback(UIButton::Press, onSubmitPress);
	submitButton->setCallback(UIButton::Click, onSubmitClick);
	submitButton->setCallback(UIButton::Release, onSubmitRelease);

	UILabel::Ptr remainingPoints = UILabel::create("Remaining Points: 100");
	remainingPoints->setPosition(100.f, 400.f);
	remainingPoints->getText().setCharacterSize(20);
	m_ui.add("remainingPoints", remainingPoints);

	m_checkMark = app.getTextures().get("Check.png").get();
	m_xMark = app.getTextures().get("X.png").get();
	m_checks.resize(10);
}

void Game::handleEvent(sf::Event & ev)
{
	m_ui.handleEvent(ev);
}
void Game::handlePacket(sf::Packet & packet)
{

	sf::Int32 round=0, n=0;
	packet >> round >> n;
	//if ()
	setValue(false, round, n);
	std::cout << "Opponent round: " << round << " n: " << n << "\n";
}
void Game::update(float dt)
{
	m_ui.update(dt);
}
void Game::draw(sf::RenderWindow & window)
{
	window.draw(m_ui);
	for (auto & s : m_checks)
		window.draw(s);
}

void Game::setValue(bool me, sf::Int32 round, sf::Int32 value)
{
	if (me)
	{	
		m_me[round - 1] = value;
		std::string s = m_ui.get<UILabel>("label" + std::to_string(round))->getText().getString();


		if (round == 10)
			s.insert(3, std::to_string(value));
		else
		s.insert(2, std::to_string(value));
		s.resize(6);
		UILabel::Ptr label = m_ui.get<UILabel>("label" + std::to_string(round));
		label->getText().setString(s);

		if (m_enemy[round-1] != -1)
		{
			if (m_me[round - 1] > m_enemy[round - 1])
			{
				m_checks[round - 1].setTexture(*m_checkMark);			
				m_checks[round - 1].setScale(.05f, .05f);
			}
			else if (m_me[round - 1] < m_enemy[round - 1])
			{
				m_checks[round - 1].setTexture(*m_xMark);
				m_checks[round - 1].setScale(.1f, .1f);
			}
			m_checks[round - 1].setPosition(70.f, label->getPosition().y);

		}
	}

	//set enemy value
	else
	{
		m_enemy[round - 1] = value;
		std::string s = m_ui.get<UILabel>("olabel" + std::to_string(round))->getText().getString();

		if (round == 10)
			s.insert(3, std::to_string(value));
		else
			s.insert(2, std::to_string(value));
		s.resize(6);
		UILabel::Ptr label = m_ui.get<UILabel>("olabel" + std::to_string(round));
		label->getText().setString(s);
	
		if (m_me[round - 1] != -1)
		{
			if (m_me[round - 1] > m_enemy[round - 1])
			{
				m_checks[round - 1].setTexture(*m_checkMark);
				m_checks[round - 1].setScale(.05f, .05f);
			}
			else if (m_me[round - 1] < m_enemy[round - 1])
			{
				m_checks[round - 1].setTexture(*m_xMark);			
				m_checks[round - 1].setScale(.1f, .1f);
			}
			m_checks[round - 1].setPosition(70.f, label->getPosition().y);

		}
	
	
	}

}