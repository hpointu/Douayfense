#ifndef SOUNDMANAGER_HPP
#define SOUNDMANAGER_HPP

#include "Singleton.hpp"
#include <SFML/Audio.hpp>

#define MAX_SND 100

class SoundManager : public Singleton<SoundManager>
{
	friend class Singleton<SoundManager>;

public:
	void init();

	void playMenuMusic();
	void playEndingMusic();

	void playMusic();
	void runningMusic();

	void playSound(const sf::SoundBuffer &buffer, float volume = 100, float pitch = 1.f);

private:
	SoundManager();

	unsigned int sndIndex, musicIndex;
	sf::Sound sounds[MAX_SND];

	sf::Music ending, menu;
	sf::Music musics[5];
};

#endif // SOUNDMANAGER_HPP
