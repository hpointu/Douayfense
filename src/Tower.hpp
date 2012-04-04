#ifndef TOWER_HPP
#define TOWER_HPP

#include <SFML/Graphics.hpp>

class Tower
{
public:
	Tower();
	void render(sf::RenderTarget *target);

	unsigned int i,j;
	bool placed;
	float range;

private:
	sf::Sprite sprite;
};

#endif // TOWER_HPP
