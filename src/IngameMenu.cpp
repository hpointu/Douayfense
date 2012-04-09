#include "IngameMenu.hpp"
#include "Application.hpp"
#include "Const.hpp"

IngameMenu::IngameMenu() :
	visible(false)
{
	float bx = 310, by = 250;

	bQuit = Button(bx, by);
	bQuit.setText("Quitter");
	bQuit.setCallback(IngameMenu::quitAction);
	by += 25;

	bCancel = Button(bx, by);
	bCancel.setText("Annuler");
	bCancel.setCallback(IngameMenu::cancelAction);
	by += 25;
}

void IngameMenu::processEvents(const sf::Event &event)
{
	if(event.Type == sf::Event::Closed)
		Application::getInstance()->window->Close();

	else if(event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Escape)
	{
		cancelAction();
	}

	bQuit.processEvents(event);
	bCancel.processEvents(event);
}

void IngameMenu::render(sf::RenderTarget *target)
{
	sf::Shape bg = sf::Shape::Rectangle(0, 0,
													W_WIDTH, W_HEIGHT,
													sf::Color(100,100,100,120));
	target->Draw(bg);

	sf::Shape sh = sf::Shape::Rectangle(290, 210,
													436, 310,
													sf::Color(110,90,60,150),
													1.f,
													sf::Color(30,35,60,200));
	target->Draw(sh);


	sf::String question("Que souhaitez vous ?");
	question.SetSize(14);
	question.SetColor(sf::Color(250,250,220));
	question.SetPosition(300, 220);

	target->Draw(question);
	bQuit.render(target);
	bCancel.render(target);

}

void IngameMenu::cancelAction()
{
	IngameMenu::getInstance()->hide();
	Application::getInstance()->togglePause();
}


void IngameMenu::quitAction()
{
	IngameMenu::getInstance()->hide();
	Application::getInstance()->reset();
}
