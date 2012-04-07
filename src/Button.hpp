#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>

typedef void (*CallbackPtr)();

class Button
{
public:
	Button();
	Button(float x, float y);

	void render(sf::RenderTarget *target);

	void processEvents(const sf::Event &event);

	void setText(const std::string &str);

	void setCallback( CallbackPtr ptr ) { callback = ptr; }

private:
	sf::FloatRect rect;
	bool hover;
	sf::String text;
	CallbackPtr callback;

	sf::Sprite sprite;

	static void nullCallback(){}

};


#endif // BUTTON_HPP
