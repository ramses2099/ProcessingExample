#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Entity:
	public sf::Drawable,
	public sf::Transformable
{

public:
	Entity(const std::string&  path, sf::Vector2f position,
		float width, float height)
	{
		if (!m_texture.loadFromFile(path))
			throw "NOT CAN'T LOAD IMAGE";

		m_vertices.setPrimitiveType(sf::Quads);
		m_vertices.resize(width * height * 4);

		
		// box
		m_vertices[0].position = sf::Vector2f(position.x,position.y);
		m_vertices[1].position = sf::Vector2f(position.x + width, position.y);
		m_vertices[2].position = sf::Vector2f(position.x + width, position.y + height);
		m_vertices[3].position = sf::Vector2f(position.x, position.y + height);
					   
		// coords
		m_vertices[0].texCoords = sf::Vector2f(0.f, 0.f);
		m_vertices[1].texCoords = sf::Vector2f(width, 0.f);
		m_vertices[2].texCoords = sf::Vector2f(width, height);
		m_vertices[3].texCoords = sf::Vector2f(0.f, height);


		velocity = sf::Vector2f(0.f, 0.50f);

		//26*32

	};
	~Entity() {};

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const 
	{
		states.transform *= getTransform();

		states.texture = &m_texture;

		target.draw(m_vertices, states);

	}
	
	virtual void update(float dt) 
	{
		for (size_t i = 0; i < m_vertices.getVertexCount(); i++)
		{
			m_vertices[i].position += velocity * dt;
		}
	}

private:
	sf::VertexArray m_vertices;
	sf::Texture m_texture;

	sf::Vector2f velocity;
	sf::Vector2f acceleracion;

};
