#include "Application.h"

#include <iostream>

const sf::Time Application::TIME_STEP = sf::seconds(1 / 60.f);

Application::Application(const std::string & path) :
m_audioPlayer(m_soundBuffers)
{
	m_window.resetGLStates();
	m_socket.setBlocking(false);
	m_listener.setBlocking(false);

	std::cout << "getting invited?\n";
	c;
	std::cin >> c;
	if (c == 'y')
	{
		m_listener.listen(PORT);
		getWindow().create(sf::VideoMode(400, 600), "Mind Game - invite me");
	}
	else
		getWindow().create(sf::VideoMode(400, 600), "Mind Game");


}

Application::~Application()
{
	m_socket.disconnect();
}

sf::RenderWindow & Application::getWindow()
{
	return m_window;
}

sf::TcpSocket & Application::getSocket()
{
	return m_socket;
}

sf::TcpListener & Application::getListener()
{
	return m_listener;
}

AudioPlayer & Application::getAudioPlayer()
{
	return m_audioPlayer;
}

Textures & Application::getTextures()
{
	return m_textures;
}

Fonts & Application::getFonts()
{
	return m_fonts;
}

void Application::push(GameState * newState)
{
	m_states.push(newState);
}

void Application::pop()
{
	m_states.pop();
}

void Application::quit()
{
	m_states.clear();
}

int Application::getTps()
{
	return m_tps;
}

int Application::getFps()
{
	return m_fps;
}


void Application::run()
{
	m_states.applyChanges(*this);

	sf::Clock clock;
	sf::Time elapsed = sf::Time::Zero;
	m_tpsclock.restart();
	m_fpsclock.restart();

	while (!m_states.isEmpty())
	{
		m_states.draw(*this);
		elapsed += clock.restart();
		while (elapsed >= TIME_STEP && !m_states.isEmpty())
		{
			elapsed -= TIME_STEP;
			m_states.handleEvent(*this);
			m_states.applyChanges(*this);
			
			if (!m_states.isEmpty())
				m_states.update(*this);
			m_states.applyChanges(*this);
		
			m_audioPlayer.update();
			//count tps
			if (m_tpsclock.getElapsedTime() > sf::seconds(1.f))
			{
				m_tps = m_ticks;
				m_ticks = 0;
				m_tpsclock.restart();
			}
			++m_ticks;
		}

		//count fps
		if (m_fpsclock.getElapsedTime() > sf::seconds(1.f))
		{
			m_fps = m_frames;
			m_frames = 0;
			m_fpsclock.restart();
		}
		++m_frames;
	}


}
