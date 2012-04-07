#include "Button.hpp"
#include <iostream>
#include "Application.hpp"

Button::Button()
{
	rect = sf::FloatRect();
	hover = false;
	callback = nullCallback;
}

Button::Button(float x, float y)
{
	rect = sf::FloatRect(x, y, x+108, y+20);
	hover = false;
	callback = nullCallback;
}

void Button::setText(const std::string &str)
{
	text.SetText(str);

	text.SetSize(14);

	sf::Vector2f buttonCenter(
				rect.Left+(rect.Right-rect.Left)/2.f,
				rect.Top+(rect.Bottom-rect.Top)/2.f
				);

	sf::FloatRect tr = text.GetRect();

	text.SetPosition( buttonCenter.x - ((tr.Right-tr.Left)/2.f),
							buttonCenter.y - ((tr.Bottom-tr.Top)/2.f) - 2
							);
}


void Button::render(sf::RenderTarget *target)
{
	sprite = sf::Sprite(Application::getInstance()->buttonImage);
	sf::Color textColor = sf::Color(230,230,200);
	text.SetColor(textColor);

	sf::Shape sh = sf::Shape::Rectangle(
				rect.Left, rect.Top, rect.Right, rect.Bottom,
				sf::Color(110,80,60), // brown
				1.f,
				sf::Color(220,210,170)
				);

	sprite.SetPosition(rect.Left, rect.Top);



	target->Draw(sprite);

	if(hover)
	{
		sf::Shape hollow = sf::Shape::Rectangle(
					rect.Left, rect.Top, rect.Right, rect.Bottom,
					sf::Color(0,255, 255,30)
					);
		target->Draw(hollow);
	}

	target->Draw(text);
}


void Button::processEvents(const sf::Event &event)
{
	if(event.Type == sf::Event::MouseMoved)
	{
		sf::Vector2f coords(event.MouseMove.X, event.MouseMove.Y);

		if(rect.Contains(coords.x, coords.y))
		{
			hover = true;
		}
		else
		{
			hover = false;
		}
	}

	else if(event.Type == sf::Event::MouseButtonPressed
			  && event.MouseButton.Button == sf::Mouse::Left)
	{
		sf::Vector2f coords(event.MouseButton.X, event.MouseButton.Y);

		if(rect.Contains(coords.x, coords.y))
		{
			callback();
		}
	}
}
