#ifndef LEVEL2_HPP
#define LEVEL2_HPP

#include "../Level.hpp"

class Level2 : public Level
{
public:
    Level2();
	 virtual std::string getFilename();
	 virtual std::vector<Wave> getWaves();
	 virtual int getBank();
	 virtual int getHomePv();
};

#endif // LEVEL1_HPP
