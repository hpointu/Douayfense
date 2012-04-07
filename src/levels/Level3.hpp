#ifndef LEVEL3_HPP
#define LEVEL3_HPP

#include "../Level.hpp"

class Level3 : public Level
{
public:
    Level3();
	 virtual std::string getFilename();
	 virtual std::vector<Wave> getWaves();
	 virtual int getBank();
	 virtual int getHomePv();
};

#endif // LEVEL3_HPP
