#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Singleton.hpp"
#include <SFML/Graphics.hpp>

class Application : public Singleton<Application>
{
	friend class Singleton<Application>;
public:
	void run();
	sf::Image enemyImage;

private:
	Application();
	~Application();

	sf::RenderWindow *window;
};

#endif // APPLICATION_HPP
