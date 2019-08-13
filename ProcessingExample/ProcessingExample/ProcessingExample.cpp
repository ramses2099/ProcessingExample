// ProcessingExample.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "PVector.h"
#include "MathUtils.h"
#include "GlobalConstants.h"

#include "Mover.h"
#include "Attractor.h"

//declaracion de variables



Mover mover;
Mover mover2(PVector(WIDTH/2,50.f), sf::Color::Blue);
Mover mover3(PVector(WIDTH / 2 + 50, 70.f), sf::Color::White);
Attractor attractor;

void setup() {
	   
}

void draw(sf::RenderWindow& window)
{
	window.clear();

	mover.draw(window);
	mover2.draw(window);
	mover3.draw(window);
	attractor.draw(window);
		
	window.display();

}

void update()
{
	
	//mover update
	mover.update();
	mover.checkEdges();

	
	PVector force = attractor.attract(mover2);
	mover2.applayForce(force);	
	mover2.update();
	mover2.checkEdges();

	PVector force2 = attractor.attract(mover3);
	mover3.applayForce(force2);
	mover3.update();
	mover3.checkEdges();


}


void input(const sf::RenderWindow& window)
{

	mover.input(window);

	mover2.input(window);

	


}


int main()
{
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Processing Example");

	window.setFramerateLimit(60);
	//init
	setup();


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			input(window);

		}


		//update
		update();

		//draw
		draw(window);

	}

	return 0;
}