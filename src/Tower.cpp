#include "Tower.hpp"
#include "Application.hpp"
#include "Const.hpp"

Tower::Tower() :
	placed(false),
	selected(false),
	range(80),
	damage(45),
	price(150)
{
	sprite = sf::Sprite(Application::getInstance()->towerImage);
	name = "Tourelle de base";
}

Tower* Tower::createCopy()
{
	return new Tower(*this);
}

void Tower::render(sf::RenderTarget *target)
{
	sf::Vector2f center(j*CELL_SIZE + (CELL_SIZE/2.f), i*CELL_SIZE + (CELL_SIZE/2.f));
	sprite.SetPosition(j*CELL_SIZE,
							 i*CELL_SIZE - (Application::getInstance()->towerImage.GetHeight()/2.5f)
							 );

	if(!placed)
	{
		sprite.SetColor(sf::Color(255,255,255,180));
	}
	else
	{
		sprite.SetColor(sf::Color(255,255,255));
	}

	if(!placed || selected)
	{
		sf::Shape rangeCircle = sf::Shape::Circle(center, range, sf::Color(0,200,0,40), 2.f, sf::Color(0,200,0,100));
		target->Draw(rangeCircle);
	}

	target->Draw(sprite);
}
