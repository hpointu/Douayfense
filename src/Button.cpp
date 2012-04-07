#include "Button.hpp"
#include <iostream>

Button::Button()
{
	rect = sf::FloatRect();
	hover = false;
	callback = nullCallback;
}

Button::Button(float x1, float y1, float x2, float y2)
{
	rect = sf::FloatRect(x1, y1, x2, y2);
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
							buttonCenter.y - ((tr.Bottom-tr.Top)/2.f)
							);
}


void Button::render(sf::RenderTarget *target)
{
	sf::Color textColor = sf::Color::White;
	text.SetColor(textColor);

	sf::Shape sh = sf::Shape::Rectangle(
				rect.Left, rect.Top, rect.Right, rect.Bottom,
				sf::Color(110,80,60), // brown
				2.f,
				sf::Color(220,210,170)
				);



	target->Draw(sh);
	target->Draw(text);

	if(hover)
	{
		sf::Shape hollow = sf::Shape::Rectangle(
					rect.Left, rect.Top, rect.Right, rect.Bottom,
					sf::Color(0,255,0,30)
					);
		target->Draw(hollow);
	}
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
