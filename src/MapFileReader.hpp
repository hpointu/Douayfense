#ifndef MAPFILEREADER_H
#define MAPFILEREADER_H

#include <string>
#include "Map.hpp"

class MapFileReader
{
public:
	 MapFileReader(const std::string &fileName);

	 Map getMap();

	 unsigned int getMapWidth();
	 unsigned int getMapHeight();

private:
	 bool isFileCorrect();

	 std::string fileName;
};

#endif // MAPFILEREADER_H
