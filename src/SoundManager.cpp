#include "SoundManager.hpp"
#include <cstdlib>

SoundManager::SoundManager() :
	sndIndex(0),
	musicIndex(0)
{
	musicIndex = rand()%5;
}

void SoundManager::init()
{
	menu.OpenFromFile("music/menu.ogg");
	ending.OpenFromFile("music/ending.ogg");

	menu.SetLoop(true);
	menu.SetVolume(35);
	ending.SetLoop(true);
	ending.SetVolume(35);

	musics[0].OpenFromFile("music/village.ogg");
	musics[1].OpenFromFile("music/ancients.ogg");
	musics[2].OpenFromFile("music/procession.ogg");
	musics[3].OpenFromFile("music/direnews.ogg");
	musics[4].OpenFromFile("music/dreaming.ogg");

}

void SoundManager::playSound(const sf::SoundBuffer &buffer, float volume, float pitch)
{
	sounds[sndIndex].SetBuffer(buffer);
	sounds[sndIndex].SetPitch(pitch);
	sounds[sndIndex].SetVolume(volume);
	sounds[sndIndex].Play();
	sndIndex++; if(sndIndex >= MAX_SND) sndIndex = 0;
}


void SoundManager::playMenuMusic()
{
	ending.Stop();
	musics[musicIndex].Stop();
	if(menu.GetStatus() != sf::Sound::Playing)
		menu.Play();
}

void SoundManager::playEndingMusic()
{
	menu.Stop();
	musics[musicIndex].Stop();
	if(ending.GetStatus() != sf::Sound::Playing)
		ending.Play();
}

void SoundManager::playMusic()
{
	menu.Stop();
	ending.Stop();

	musics[musicIndex].SetVolume(35);
	musics[musicIndex].SetLoop(false);
	musics[musicIndex].Play();
}

void SoundManager::runningMusic()
{
	if(musics[musicIndex].GetStatus() == sf::Sound::Stopped)
	{
		musicIndex++; if(musicIndex >= 5) musicIndex = 0;
		playMusic();
	}
}
