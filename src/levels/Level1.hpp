#ifndef LEVEL1_HPP
#define LEVEL1_HPP

#include "../Level.hpp"

class Level1 : public Level
{
public:
    Level1();
	 virtual std::string getFilename();
	 virtual std::vector<Wave> getWaves();
	 virtual int getBank();
	 virtual int getHomePv();
};

#endif // LEVEL1_HPP
