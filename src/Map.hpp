#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Map
{
public:
	enum Type
	{
		GROUND = 0,
		PATH = 1,
		DOOR = 2,
		HOME = 3,
		ROCK = 4,
		ERROR = 99
	};

	struct Cell
	{
		Type type;
		unsigned int posI;
		unsigned int posJ;
	};

	Map();
	Map(const std::vector< std::vector< Map::Cell > > &cellMap);

	std::vector<Cell> getDoors();
	Cell nextPathCellFrom(Cell current);
	Cell getCell(float x, float y);
	void render(sf::RenderTarget *target);

	void setVisited(unsigned int i, unsigned int j, bool val);
	bool isVisited(unsigned int i, unsigned int j);

	unsigned int width, height;

private:
	std::vector< std::vector< Cell > > cells;
	std::vector< std::vector< bool > > visited;

	sf::Color getColor(Type type);
};

#endif // MAP_HPP
