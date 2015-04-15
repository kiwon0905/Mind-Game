#include "AudioPlayer.h"

AudioPlayer::AudioPlayer(SoundBuffers & soundBuffers) :
m_soundBuffers(soundBuffers)
{

}

void AudioPlayer::playMusic(const std::string & s)
{
	m_musics[s].openFromFile(s);
	m_musics[s].play();
}
void AudioPlayer::stopMusic(const std::string & s)
{
	m_musics[s].stop();
}
void AudioPlayer::playSound(const std::string & s)
{
	sf::Sound sound;
	sound.setBuffer(*m_soundBuffers.get(s));
	sound.play();
	m_sounds.push_back(sound);
}
void AudioPlayer::update()
{
	auto isDone = [](const sf::Sound & s) -> bool
	{
		return s.getStatus() == sf::Sound::Stopped;
	};
	m_sounds.remove_if(isDone);
}
