#pragma once

#include <list>
#include <memory>
#include <random>
#include <sstream>
#include <vector>
#include "Particle.h"


class ParticleSystem :public sf::Drawable
{
public:
	ParticleSystem(sf::Vector2u canvasSize) :
		_dissolve(false),
		_particleSpeed(100.f),
		_transparent(sf::Color(0, 0, 0, 0)),
		_dissolutionRate(4),
		_gravity(sf::Vector2f(0.0f, 0.0f)),
		_canvasSize(canvasSize)
	{
		_startPos = sf::Vector2f(
			static_cast<float>(_canvasSize.x) / 2,
			static_cast<float>(_canvasSize.y) / 2);

	};
	~ParticleSystem() { _particles.clear(); };

	/*Getter and Setter*/

	const int getDissolutionRate()noexcept { return _dissolutionRate; }
	const int getNumberOfParticles()noexcept { return _particles.size(); }
	const float getParticleSpeed()noexcept { return _particleSpeed; }

	void setCanvasSize(sf::Vector2u newSize) { _canvasSize = newSize; }
	void setDissolutionRate(sf::Uint8 rate) { _dissolutionRate = rate; }
	void setDissolve() { _dissolve = !_dissolve; }
	void setDistribution() { _shape = (_shape + 1) % 2; }
	void setGravity(float x, float y) { _gravity.x = x; _gravity.y = y; }
	void setGravity(sf::Vector2f gravity) { _gravity = gravity; }
	void setParticleSpeed(float speed) { _particleSpeed = speed; }
	void setPosition(float x, float y) { _startPos.x = x; _startPos.y = y; }
	void setPosition(sf::Vector2f position) { _startPos = position; }
	void setShape(sf::Uint8 shape) { _shape = shape; }
	/*Getter and Setter*/

	/*Function member*/

	void draw(sf::RenderTarget& target, sf::RenderStates states)const
	{
		for (const auto& item : _particles)
		{
			target.draw(&item->drawVertex, 1, sf::Points);
		}
		return;
	}
	//
	void fuel(int particles)
	{
		for (int i = 0; i < particles; i++)
		{
			Particle* particle;
			particle = new Particle();

			particle->drawVertex.position.x = _startPos.x;
			particle->drawVertex.position.y = _startPos.y;

			/*Randomizer initialization*/
			std::random_device rd;
			std::mt19937 gen(rd());

			switch (_shape)
			{
				case Shape::CIRCLE: {
					/*Generate a random angle*/
					UnitRealDist randomAngle(0.0f, (3.0f * 3.14159265));
					float angle = randomAngle(gen);

					//UnitRealDist randomAngleCos(0.0f, std::cos(angle));
					//UnitRealDist randomAngleSin(0.0f, std::sin(angle));
					
					UnitRealDist randomAngleCos(0.0f, 2.0f);
					UnitRealDist randomAngleSin(0.0f, 1.0f);
					
					particle->vel.x = randomAngleCos(gen);
					particle->vel.y = randomAngleSin(gen);
					
					break;
				}
				case Shape::SQUARE: {
					UnitRealDist randomSide(-1.0f, 1.0f);
					particle->vel.x = randomSide(gen);
					particle->vel.y = randomSide(gen);
					break;
				}
				default: {
					particle->vel.x = 0.5f;
					particle->vel.y = 0.5f;
					break; 
				}
			}

			/*We don't want lame particles. reject, start over*/
			if (particle->vel.x == 0.0f && particle->vel.y == 0.0f) 
			{
				delete particle;
				continue;
			}

			UnitIntDist randomColor(0, 255);
			particle->drawVertex.color.r = randomColor(gen);
			particle->drawVertex.color.g = randomColor(gen);
			particle->drawVertex.color.b = randomColor(gen);
			particle->drawVertex.color.a = 255;

			_particles.push_back(ParticlePtr(particle));

		}

		return;
	}
	//
	const std::string getNumberOfParticlesString()const 
	{
		std::ostringstream oss;
		oss << _particles.size();
		return oss.str();
	}
	//
	void update(float deltaTime)
	{

		/* Run through each particle and apply our system to it */
		for (auto it = _particles.begin(); it != _particles.end(); it++)
		{
			/* Apply Gravity */
			(*it)->vel.x += _gravity.x * deltaTime;
			(*it)->vel.y += _gravity.y * deltaTime;

			/* Apply thrust */
			(*it)->drawVertex.position.x += (*it)->vel.x * deltaTime * _particleSpeed;
			(*it)->drawVertex.position.y += (*it)->vel.y * deltaTime * _particleSpeed;

			/* If they are set to disolve, disolve */
			if (_dissolve) (*it)->drawVertex.color.a -= _dissolutionRate;

			if ((*it)->drawVertex.position.x > _canvasSize.x
				|| (*it)->drawVertex.position.x < 0
				|| (*it)->drawVertex.position.y > _canvasSize.y
				|| (*it)->drawVertex.position.y < 0
				|| (*it)->drawVertex.color.a < 10)
			{
				it = _particles.erase(it);
				if (it == _particles.end()) return;
			}


		}
	}
	

	/*Function member*/
private:
	bool _dissolve;
	float _particleSpeed;

	sf::Color _transparent;

	sf::Uint8 _dissolutionRate;
	sf::Uint8 _shape;

	sf::Vector2f _gravity;
	sf::Vector2f _startPos;
	sf::Vector2u _canvasSize;

	std::vector<ParticlePtr> _particles;

};
