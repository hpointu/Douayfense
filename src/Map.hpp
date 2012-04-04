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
		HOME = 2,
		DOOR = 3
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

private:
	std::vector< std::vector< Cell > > cells;
	std::vector< std::vector< bool > > visited;
	unsigned int width, height;

	sf::Color getColor(Type type);
};

#endif // MAP_HPP
