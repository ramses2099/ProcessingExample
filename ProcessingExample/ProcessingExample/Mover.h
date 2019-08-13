#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "PVector.h"
#include "MathUtils.h"
#include "GlobalConstants.h"

class Mover
{
public:
	Mover()
	{
		init();
	};

	Mover(PVector loc, sf::Color c)
	{
		location.set(loc);
		velocity.set(0.f, 0.f);
		accelaration.set(0.f, 0.f);

		//
		shape.setRadius(10.f);
		shape.setFillColor(c);
		shape.setPosition(location.sf());

		topSpeed = 10.f;
		mass = 10.f;

	};

	~Mover() {};

	void applayFriction()
	{
		float c = 0.01f;
		PVector friction = velocity;
		friction.mult(-1.f);
		friction.normalize();
		friction.mult(c);

		applayForce(friction);

	}

	void update()
	{

		/*-- friction
		PVector wind(0.001f, 0.f);
		PVector gravity(0.f, 0.1f);

		applayFriction();
		applayForce(wind);
		applayForce(gravity);
		--*/

		velocity.add(accelaration);
		location.add(velocity);

		aVelocity += aAcceleration;
		angle += aVelocity;
		
		accelaration.mult(0);

		shape.setPosition(location.sf());

		shape.setRotation(angle);
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(shape);
	}

	void input(const sf::RenderWindow & window)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			/*--
			sf::Vector2i pos = sf::Mouse::getPosition(window);
			mouse.set(static_cast<float>(pos.x), static_cast<float>(pos.y));

			std::cout << mouse.to_str() << std::endl;
			--*/
			//applayForce(PVector(1.5f, 0.f));
			//applayForce(PVector(0.f, 10.f));

		}
	}

	void checkEdges()
	{
		if (location.getX() > WIDTH - shape.getRadius())
		{
			float dx = velocity.getX() * -1;
			velocity.set(dx, velocity.getY());
		}
		else if (location.getX() < shape.getRadius())
		{
			float dx = velocity.getX() * -1;
			velocity.set(dx, velocity.getY());
		}

		if (location.getY() > HEIGHT - shape.getRadius())
		{
			float dy = velocity.getY() * -1;
			velocity.set(0, dy);
		}
		else if (location.getY() < shape.getRadius())
		{
			float dy = velocity.getY() * -1;
			velocity.set(0, dy);
		}

	}

	void applayForce(PVector force)
	{
		PVector f = PVector::div(force, mass);
		accelaration.add(f);
	}

	const PVector& getLocation()noexcept { return location; }

	const float getMass() noexcept { return mass; }

private:
	PVector location;
	PVector velocity;
	PVector accelaration;
	PVector mouse;

	float topSpeed;
	float mass;

	float angle;
	float aVelocity;
	float aAcceleration;

	sf::CircleShape shape;

	void init()
	{

		location.set(MathUtils::randomFloat(1.f, WIDTH),
			MathUtils::randomFloat(1.f, HEIGHT));
		velocity.set(0.f, 0.f);
		accelaration.set(0.f, 0.f);
		
		//
		shape.setRadius(10.f);
		shape.setFillColor(sf::Color::Red);
		shape.setPosition(location.sf());

		topSpeed = 10.f;
		mass = 10.f;
	}


};

