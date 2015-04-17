#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <SFML/Network.hpp>
#include <memory>

#include "ResourceManager.h"
#include "GameStateStack.h"
#include "AudioPlayer.h"


class Application
{
public:
	static const sf::Time TIME_STEP;
	static const unsigned int PORT = 5000;

	Application(const std::string & path);
	~Application();

	void quit();
	void push(GameState * newState);
	void pop();
	void run();

	sf::TcpSocket & getSocket();
	sf::TcpListener & getListener();
	sf::RenderWindow & Application::getWindow();
	AudioPlayer & getAudioPlayer();
	Textures & getTextures();
	Fonts & getFonts();

	int getTps();
	int getFps();
	char c;
private:
	GameStateStack m_states;
	sf::RenderWindow m_window; 
	sf::TcpSocket m_socket;
	sf::TcpListener m_listener; 
	AudioPlayer m_audioPlayer;
	Textures m_textures;
	SoundBuffers m_soundBuffers;
	Fonts m_fonts;


	sf::Clock m_tpsclock;
	int m_ticks;
	int m_tps;

	sf::Clock m_fpsclock;
	int m_frames;
	int m_fps;

};

