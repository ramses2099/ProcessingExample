#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "PVector.h"
#include "MathUtils.h"
#include "GlobalConstants.h"
#include "Mover.h"

class Attractor
{
public:
	Attractor()
	{
		init();
	};
	
	~Attractor() {};
	
	void update()
	{
				
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(shape);
	}

	PVector attract(Mover m) 
	{
		PVector force = PVector::sub(location, m.getLocation());
		float dist = force.mag();
		dist = MathUtils::clamp(dist, 5.0f, 25.0f);

		force.normalize();

		float strength = (G * mass * m.getMass()) / (dist * dist);

		force.mult(strength);

		return force;
	}

private:
	PVector location;	
	float mass;

	sf::CircleShape shape;

	void init()
	{
		location.set(WIDTH/2,HEIGHT/2);
				
		//
		shape.setRadius(20.f);
		shape.setFillColor(sf::Color::Green);
		shape.setPosition(location.sf());

		mass = 20.f;
	}


};
