#pragma once

#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>

namespace Shape { enum { CIRCLE, SQUARE }; }

struct Particle
{

	sf::Vertex drawVertex;
	sf::Vector2f vel;


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const
	{
		target.draw(&drawVertex, 1, sf::Points, states);
	}

};

typedef std::uniform_real_distribution<> UnitRealDist;
typedef std::uniform_int_distribution<> UnitIntDist;
typedef std::shared_ptr<Particle> ParticlePtr;