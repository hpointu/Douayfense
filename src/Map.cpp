#include "Map.hpp"
#include "Const.hpp"
#include "Application.hpp"

Map::Map()
{
}

Map::Map(const std::vector< std::vector< Map::Cell > > &cellMap)
{
	width = cellMap[0].size();
	height = cellMap.size();
	cells = cellMap;

	visited.resize(height, std::vector<bool>(width));
	for(unsigned int i=0; i<height; i++)
		for(unsigned int j=0; j<width; j++)
			visited[i][j] = false;
}

void Map::render(sf::RenderTarget *target)
{
	for(unsigned int i=0; i<height; i++)
	{
		for(unsigned int j=0; j<width; j++)
		{
			Cell c = cells[i][j];

			if(c.type != Map::GROUND)
			{
				sf::Shape rect = sf::Shape::Rectangle(0,0,
																  CELL_SIZE,CELL_SIZE,
																  getColor(c.type),
																  0.f, sf::Color::Black);

				rect.SetPosition(sf::Vector2f(j*CELL_SIZE, i*CELL_SIZE));

				target->Draw(rect);
			}
		}
	}

	for(unsigned int i=0; i<height; i++)
	{
		for(unsigned int j=0; j<width; j++)
		{
			Cell c = cells[i][j];

			if(c.type == Map::GROUND)
			{
				sf::Sprite sp(Application::getInstance()->grassImage);
				sp.SetPosition(j*CELL_SIZE -6,
									i*CELL_SIZE -6);
				target->Draw(sp);
			}
		}
	}

	for(unsigned int i=0; i<height; i++)
	{
		for(unsigned int j=0; j<width; j++)
		{
			Cell c = cells[i][j];

			if(c.type == Map::HOME)
			{
				sf::Sprite sp(Application::getInstance()->homeImage);
				sp.SetPosition(j*CELL_SIZE -8,
									i*CELL_SIZE -16);
				target->Draw(sp);
			}

			else if(c.type == Map::DOOR)
			{
				sf::Sprite sp(Application::getInstance()->doorImage);
				sp.SetPosition(j*CELL_SIZE -8,
									i*CELL_SIZE -8);
				target->Draw(sp);
			}
		}
	}
}

bool Map::isVisited(unsigned int i, unsigned int j)
{
	return visited[i][j];
}

void Map::setVisited(unsigned int i, unsigned int j, bool val)
{
	visited[i][j] = val;
}

Map::Cell Map::nextPathCellFrom(Cell current)
{
	Cell left = current, top = current, right = current, bottom = current;
	if(current.posI > 0)
		top.posI -= 1;
	if(current.posI < height-1)
		bottom.posI += 1;
	if(current.posJ > 0)
		left.posJ -= 1;
	if(current.posJ < width-1)
		right.posJ += 1;

	if((cells[left.posI][left.posJ].type & Map::PATH) == Map::PATH
			&& !visited[left.posI][left.posJ])
		return left;
	else if((cells[right.posI][right.posJ].type & Map::PATH) == Map::PATH
			  && !visited[right.posI][right.posJ])
		return right;
	else if((cells[top.posI][top.posJ].type & Map::PATH) == Map::PATH
			  && !visited[top.posI][top.posJ])
		return top;
	else if((cells[bottom.posI][bottom.posJ].type & Map::PATH) == Map::PATH
			  && !visited[bottom.posI][bottom.posJ])
		return bottom;

	return current;

}

Map::Cell Map::getCell(float x, float y)
{
	unsigned int i = y/CELL_SIZE;
	unsigned int j = x/CELL_SIZE;

	Cell err;
	err.type = Map::ERR;

	if(i<height && j<width)
		return cells[i][j];
	else
		return err;
}

std::vector<Map::Cell> Map::getDoors()
{
	std::vector<Cell> res;
	for(unsigned int i=0; i<height; i++)
	{
		for(unsigned int j=0; j<width; j++)
		{
			Cell c = cells[i][j];
			if(c.type == Map::DOOR)
				res.push_back(c);
		}
	}
	return res;
}

sf::Color Map::getColor(Type type)
{
	switch(type)
	{
	case Map::GROUND:
		return sf::Color(110,150,85);
		break;
	case Map::PATH:
		return sf::Color(255,240,165);
		break;
	case Map::HOME:
		return sf::Color(255,240,165);
		break;
	case Map::DOOR:
		return sf::Color(255,240,165);
		break;
	case Map::ROCK:
		return sf::Color(100,100,100);
		break;
	default:
		return sf::Color::Red;
		break;
	}
}
