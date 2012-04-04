#ifndef TOWER_HPP
#define TOWER_HPP

#include <string>
#include <SFML/Graphics.hpp>

class Tower
{
public:
	Tower();
	void render(sf::RenderTarget *target);
	Tower* createCopy();

	unsigned int i,j;
	bool placed;
	bool selected;
	int range;
	int damage;
	std::string name;

	int getValue(){ return 0.75*price; }
	int getPrice(){ return 1.f*price; }

protected:
	int price;

private:
	sf::Sprite sprite;
};

#endif // TOWER_HPP
