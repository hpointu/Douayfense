#include "MapReader.hpp"
#include "Map.hpp"

MapReader::MapReader()
{
}

void MapReader::createMapFromFile(const std::string &filename)
{
	std::ifstream file;
	file.open(filename.c_str());


}
