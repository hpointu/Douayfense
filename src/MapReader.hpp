#ifndef MAPREADER_HPP
#define MAPREADER_HPP
#include <fstream>
#include <string>

class MapReader
{
public:
	MapReader();
	void createMapFromFile(const std::string &filename);


};

#endif // MAPREADER_HPP
