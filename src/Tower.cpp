#include "Tower.hpp"
#include "Application.hpp"
#include "Const.hpp"

Tower::Tower() :
	placed(false),
	range(100)
{
	sprite = sf::Sprite(Application::getInstance()->towerImage);
}


void Tower::render(sf::RenderTarget *target)
{
	sprite.SetPosition(j*CELL_SIZE,
							 i*CELL_SIZE - (Application::getInstance()->towerImage.GetHeight()/2.5f)
							 );

	if(!placed)
	{
		sprite.SetColor(sf::Color(255,255,255,180));
//		sf::Shape rangeCircle sf::Shape::Circle()
	}
	else
		sprite.SetColor(sf::Color(255,255,255));

	target->Draw(sprite);
}
