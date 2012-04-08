#include "Application.hpp"
#include "SoundManager.hpp"

#include <cstdlib>
#include <ctime>

int main(void)
{
	srand(time(0));

	SoundManager::getInstance()->init();
	Application::getInstance()->run();
	return 0;
}
