// ProcessingExample.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "ParticlesSystem.h"
#include "Entity.h"

int main()
{
	// create the window
	sf::RenderWindow window(sf::VideoMode(512, 256), "Particles");

	//entity
	Entity entity("graphics/player001.png",
		sf::Vector2f(50.f, 50.f),21.f,26.f);
	
	// create the particle system
	//ParticlesSystem particles(1000);

	// create a clock to track the elapsed time
	sf::Clock clock;

	// run the main loop
	while (window.isOpen())
	{
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// make the particle system emitter follow the mouse
		sf::Vector2i mouse = sf::Mouse::getPosition(window);
		//particles.setEmitter(window.mapPixelToCoords(mouse));

		// update it
		sf::Time elapsed = clock.restart();
		//particles.update(elapsed);


		entity.update(elapsed.asSeconds());

		// draw it
		window.clear();
		//window.draw(particles);

		window.draw(entity);
		window.display();
	}

	return 0;
}