#include <SFML/Graphics.hpp>
#include "Windmill.h"
#include <SFML/Audio.hpp>

int main(int argc, char *argv)
{
	unsigned int width = 1200;
	unsigned int height = 800;

	sf::RenderWindow window(sf::VideoMode(width, height), "Template", sf::Style::Titlebar | sf::Style::Close);
	Windmill *windmill1 = new Windmill("WindmillBase.JPG", "blade.JPG");
	Windmill *windmill2 = new Windmill("WindmillBase.JPG", "blade.JPG");
	Windmill *windmill3 = new Windmill("WindmillBase.JPG", "blade.JPG");


	sf::SoundBuffer buffer;
	buffer.loadFromFile("Wind.wav");
	sf::Sound sound(buffer);

	sf::Texture cloudsTexture;
	cloudsTexture.loadFromFile("tiling_clouds.jpg");
	cloudsTexture.setRepeated(true);

	sf::Sprite tilingCloudsSprite;
	tilingCloudsSprite.setTexture(cloudsTexture);
	tilingCloudsSprite.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));


	sf::Vector2<float> position;
	position.x = 300;
	position.y = 400;
	windmill1->CreateWindmill(position);

	position.x = 550;
	position.y = 400;
	windmill2->CreateWindmill(position);

	position.x = 800;
	position.y = 400;
	windmill3->CreateWindmill(position);

	sf::Event evt;
	sf::Clock appTimer;
	int mouseX = 0;
	int mouseY = 0;

	window.pollEvent(evt);

	int lastMouseX = 0.0f;
	int lastMouseY = 0.0f;

	int posX = 0.0f;
	int posY = 0.0f;

	int key4Pressed = 0;
	int keyPressed = 1;

	sf::Vector2<float> rotPos;
	sf::IntRect backgroundRect = tilingCloudsSprite.getTextureRect();
	float secondTimer = 0.0f; // elapsed time per second.
	float movementSpeed = 150.0f; // scrolling movement speed.
	sound.play();
	while (window.isOpen()) {
		float deltaTime = appTimer.restart().asSeconds();
		
		while (window.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				window.close();
			}
			else if (evt.type == sf::Event::MouseMoved) 
			{
				mouseX = evt.mouseMove.x;
				mouseY = evt.mouseMove.y;

				posX = (lastMouseX - mouseX) * -1;
				posY = (lastMouseY - mouseY) * -1;

				lastMouseX = mouseX;
				lastMouseY = mouseY;
			}
			else if (evt.type == sf::Event::KeyReleased) 
			{
				switch (evt.key.code)
				{
				case sf::Keyboard::Key::Num1:
					keyPressed = 1;
					break;
				case sf::Keyboard::Key::Num2:
					keyPressed = 2;
					break;
				case sf::Keyboard::Key::Num3:
					keyPressed = 3;
					break;
				case sf::Keyboard::Key::Num4: 
				{
					key4Pressed++;
					keyPressed = 4;
					break;
				}
					
					
				default:
					break;
				}
			}
		}

		// do stuff.
		window.clear();
		secondTimer += deltaTime;

		sf::IntRect deltaRect = backgroundRect;
		deltaRect.left = backgroundRect.left + (int)(movementSpeed * secondTimer);
		tilingCloudsSprite.setTextureRect(deltaRect);

		if (secondTimer > 1.0f)
		{
			/* Remove a second from timer (we can't set it to 0 because there's a chance that a small
			* fraction of a second has elapsed, and we don't want to lose that). eg. 1.001f */
			secondTimer -= 1.0f;
			backgroundRect.left += (int)movementSpeed; // Add on the appropriate offset.
			if (backgroundRect.left >= (float)cloudsTexture.getSize().x) {
				backgroundRect.left -= cloudsTexture.getSize().x;
			}
		}


		window.draw(tilingCloudsSprite);
		if (keyPressed == 1) 
			windmill1->DrawWindmill(&window, posX, posY, 400.0f, 300.0f);

		else if(keyPressed != 4)
			windmill1->DrawWindmill(&window, 0, 0, 400.0f, 300.0f);

		if (keyPressed == 2) 
			windmill2->DrawWindmill(&window, posX, posY, 400.0f, 300.0f);

		else if (keyPressed != 4)
			windmill2->DrawWindmill(&window, 0, 0, 400.0f, 300.0f);

		if (keyPressed == 3) 
			windmill3->DrawWindmill(&window, posX, posY, 400.0f, 300.0f);

		else if (keyPressed != 4)
			windmill3->DrawWindmill(&window, 0, 0, 400.0f, 300.0f);

		if (keyPressed == 4) 
		{
			if(key4Pressed>0)
			{
				windmill1->ResetPosiiton();
				windmill2->ResetPosiiton();
				windmill3->ResetPosiiton();
				key4Pressed--;
			}

			rotPos = windmill1->DrawWindmill(&window, posX, posY, 400.0f, 300.0f);
			rotPos = windmill2->DrawWindmill(&window, posX, posY, rotPos.x, rotPos.y);
			rotPos = windmill3->DrawWindmill(&window, posX, posY, rotPos.x, rotPos.y);
		}
			
		posX = 0;
		posY = 0;

		window.display();
	}

	return 0;
}