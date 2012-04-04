#include "MapFileReader.hpp"
#include <cstdio>
#include <cstdlib>
#include <iostream>

MapFileReader::MapFileReader(const std::string &fileName)
{
	this->fileName = fileName;
	if(!isFileCorrect())
		exit(-1);
}


Map MapFileReader::getMap()
{
	std::cout << "Loading map \"" << fileName << "\" ..." << std::endl;

	FILE *file = fopen(fileName.data(), "r");

	std::vector< std::vector< Map::Cell > > cellMap;
	cellMap.resize(getMapHeight(), std::vector<Map::Cell>(getMapWidth()));

	unsigned int x = 0 , y = 0;
	char c;
	while(fread(&c, 1, 1, file))
	{
		if(c != '\n')
		{
			int intVal = c-48;

			Map::Cell c;
			c.type = Map::Type(intVal);
			c.posI = y;
			c.posJ = x;
			cellMap[y][x] = c;

			// set the coords
			x++;
		}
		if(c == '\n')
		{
			y++;
			x=0;
		}
	}

	return Map(cellMap);
}

unsigned int MapFileReader::getMapWidth()
{
	FILE *file = fopen(fileName.data(), "r");

	char c;
	unsigned int count = 0;
	while(fread(&c, 1, 1, file) && c != '\n')
	{
		count++;
	}
	return count;
}

unsigned int MapFileReader::getMapHeight()
{
	FILE *file = fopen(fileName.data(), "r");

	char c;
	unsigned int count = 0;
	while(fread(&c, 1, 1, file))
	{
		if(c == '\n')
		{
			count++;
		}
	}
	return count;
}

bool MapFileReader::isFileCorrect()
{
	int width = -1;

	FILE *file = fopen(fileName.c_str(), "r");

	char c;
	int count = 0;
	while(fread(&c, 1, 1, file))
	{
		count++;
		if(c == '\n')
		{
			if(width<0)
				width = count;
			else
			{
				if(width != count)
				{
					return false;
				}
			}
			count = 0;
		}
	}

	return true;
}
