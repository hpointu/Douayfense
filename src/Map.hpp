#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#define CELL_SIZE 20

class Map
{
public:
	enum Type
	{
		GROUND,
		HOME,
		PATH,
		START
	};

	struct Cell
	{
		Type type;
		unsigned int posI;
		unsigned int posJ;
	};

	Map();
	Map(const std::vector< std::vector< Map::Cell > > &cellMap);

	Cell nextPathCellFrom(unsigned int i, unsigned int j);
	void render(sf::RenderTarget *target);

private:
	std::vector< std::vector< Cell > > cells;
};

#endif // MAP_HPP
