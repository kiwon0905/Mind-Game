#pragma once

#include <list>
#include <unordered_map>
#include <SFML\Audio.hpp>
#include "ResourceManager.h"


class AudioPlayer
{
public:
	AudioPlayer(SoundBuffers & soundBuffers);
	void playMusic(const std::string & s);
	void stopMusic(const std::string & s);
	void playSound(const std::string & s);
	void update();
private:
	std::unordered_map<std::string, sf::Music> m_musics;
	std::list<sf::Sound> m_sounds;
	SoundBuffers & m_soundBuffers;
};