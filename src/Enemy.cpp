#include "Enemy.hpp"
#include "Application.hpp"
#include "Const.hpp"
#include <cmath>

Enemy::Enemy(Map::Cell pos, Map map) :
	myMap(map)
{
	x = pos.posJ*CELL_SIZE;
	y = pos.posI*CELL_SIZE;
	speed = 1.4f;
	sprite = sf::Sprite(Application::getInstance()->enemyImage);
}

void Enemy::render(sf::RenderTarget *target)
{
	sprite.SetPosition(x-(Application::getInstance()->enemyImage.GetWidth()/1.3f),
							 y-(Application::getInstance()->enemyImage.GetHeight() + 4));
	target->Draw(sprite);
}

void Enemy::moveToNext()
{
	Map::Cell current = myMap.getCell(x,y);
	Map::Cell dest = myMap.nextPathCellFrom(current);

	float toX = dest.posJ*CELL_SIZE + CELL_SIZE/2.f;
	float toY = dest.posI*CELL_SIZE + CELL_SIZE/2.f;

	float dX = toX-x;
	float dY = toY-y;

	float err = 1.f*speed;

	if(::fabs(dX) > err)
		x += (dX>0) ? speed : -speed;

	if(::fabs(dY) > err)
		y += (dY>0) ? speed : -speed;

	myMap.setVisited(current.posI, current.posJ, true);

}
