#pragma once

#include <list>
#include <memory>
#include <random>
#include <sstream>
#include <vector>
#include <SFML/Graphics.hpp>


class ParticlesSystem :
	public sf::Drawable,
	public sf::Transformable
{
public:
	ParticlesSystem(unsigned int count) :
		m_particles(count),
		m_vertices(sf::Points, count),
		m_lifetime(sf::seconds(3.f)),
		m_emitter(0.f, 0.f)
	{};
	~ParticlesSystem() {};

	void setEmitter(sf::Vector2f position) 
	{
		m_emitter = position;
	}

	void update(sf::Time elapsed)
	{
		for (size_t i = 0; i < m_particles.size(); i++)
		{
			Particle& p = m_particles[i];
			p.lifetime -= elapsed;

			if (p.lifetime <= sf::Time::Zero)
				resetParticle(i);

			m_vertices[i].position += p.velocity * elapsed.asSeconds();

			float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
			m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);

		}
	
	}
private:
	struct Particle
	{
		sf::Vector2f velocity;
		sf::Time lifetime;

	};

	void resetParticle(std::size_t index)
	{
		float angle = (std::rand() % 360) * 3.14f / 180.f;
		float speed = (std::rand() % 50) + 50.f;

		m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
		m_particles[index].lifetime = sf::milliseconds(std::rand() % 2000 + 1000);

		m_vertices[index].position = m_emitter;

	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		states.texture = NULL;

		target.draw(m_vertices, states);

	}

	std::vector<Particle> m_particles;
	sf::VertexArray m_vertices;
	sf::Time m_lifetime;
	sf::Vector2f m_emitter;

};

