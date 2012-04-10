#include "Gobelin.hpp"
#include "Application.hpp"
#include "SoundManager.hpp"

Gobelin::Gobelin(Map::Cell pos, Map map) :
	Enemy(pos, map)
{
	speed = 3.5f;
}

sf::Image* Gobelin::getImage()
{
	return &Application::getInstance()->goblinImage;
}

Enemy* Gobelin::createClone()
{
	return new Gobelin(*this);
}

float Gobelin::getInitialPv()
{
	return 75;
}

void Gobelin::playDyingSound()
{
	SoundManager::getInstance()->playSound(Application::getInstance()->dyingBuff, 80, 2.f);
}
