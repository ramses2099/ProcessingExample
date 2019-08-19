#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class EntityObject
{
public:
	EntityObject():_isLoad(false) {};
	
	virtual void update(float dt) {};
	virtual void input(sf::Event event) {};
	virtual void draw(sf::RenderWindow& window) 
	{
		if (_isLoad) {
			window.draw(_sprite);
		}
	};
		
	virtual ~EntityObject() {};

protected:
	const sf::Vector2f& getPosition()noexcept { return _position; };
	void setPosition(const sf::Vector2f& v1)
	{
		if (_isLoad)
		{
			_position = v1;
			_sprite.setPosition(_position);
		}
	}
	//
	const sf::Vector2f& getVelocity()noexcept { return _velocity; };
	void setVelocity(const sf::Vector2f& v1) { _velocity = v1; }
	//
	const sf::Vector2f& getAcceleration()noexcept { return _acceleration; };
	void setAcceleration(const sf::Vector2f& v1) { _acceleration = v1; }
	//
	const sf::Vector2f& getSteer()noexcept { return _steer; };
	void setSteer(const sf::Vector2f& v1) { _steer = v1; }
	//
	const float getMaxSpeed()noexcept { return _maxSpeed; };
	void setMaxSpeed(float maxSpeed) { _maxSpeed = maxSpeed; }
	//
	const float getMaxForce()noexcept { return _maxForce; };
	void getMaxForce(float maxForce) { _maxForce = maxForce; }

	void Load(std::string path) 
	{
		if (_texture.loadFromFile(path)) 
		{
			_isLoad = true;
			_sprite.setTexture(_texture);
		}
	
	}


private:
	sf::Sprite _sprite;
	sf::Texture _texture;
	bool _isLoad;

	sf::Vector2f _position;
	sf::Vector2f _velocity;
	sf::Vector2f _acceleration;
	sf::Vector2f _steer;

	float _maxSpeed;
	float _maxForce;


};
