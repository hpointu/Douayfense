#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Singleton.hpp"

class Application : public Singleton<Application>
{
	friend class Singleton<Application>;
public:

private:
	Application();
	~Application();
};

#endif // APPLICATION_HPP
