#pragma once

#include <string>
#include <time.h>
#include <random>
#include <cmath>
#include <iostream>


/* Includes - SFML */
#include <SFML/System/Vector2.hpp>

/* Defines */
#define PI 3.14159265358979323846F

class PVector
{
public:
	PVector() :x(0.f), y(0.f) {}
	PVector(float x, float y) :x(x), y(y) {}
	PVector(const PVector& v) :x(v.x), y(v.y) {}
	PVector(sf::Vector2f v) :x(v.x), y(v.y) {}
	~PVector() {}

	//set
	void set(PVector & v) { this->x = v.x; this->y = v.y; }
	void set(sf::Vector2f& v) { this->x = v.x; this->y = v.y; }
	void set(float x, float y) { this->x = x; this->y = y; }
	//set
	
	//operation
	PVector copy()
	{
		return PVector(this->x, this->y);
	}
	/*
	 *Adds x, y, and z components to a vector, one vector to another, or two independent vectors
	*/
	void add(PVector & v)
	{
		this->x += v.x;
		this->y += v.y;
	}

	/*
	 *Subtract x, y, and z components from a vector, one vector from another,
	 *or two independent vectors
	*/
	void sub(PVector & v)
	{
		this->x -= v.x;
		this->y -= v.y;
	}

	/*
	 *Divide a vector by a scalar
	 */
	void div(float scale) {
		this->x /= scale;
		this->y /= scale;
	}
	
	/*	
	 *Multiply a vector by a scalar
	*/
	
	void mult(float scale) {
		this->x *= scale;
		this->y *= scale;
	}
	
	/*
	 *Calculate the magnitude of the vector
	 */
	float mag() 
	{
		return std::sqrt((std::pow(this->x, 2) + std::pow(this->y, 2)));
	}

	/*
	 *Set the magnitude of the vector
	*/
	void setMag(float scale) 
	{
		float len = mag();
		this->x = (this->x / len) * scale;
		this->y = (this->y / len) * scale;	
	}
	
	/*
	 *Calculate the distance between two points
	*/
	float dist(PVector & v)
	{
		float dx = v.x - this->x;
		float dy = v.y - this->y;

		PVector vd(dx, dy);

		return vd.mag();
	}

	/*
	 *Calculate the dot product of two vectors
	*/
	float dot(PVector & v)
	{
		return ((this->x * v.x) + (this->y * v.y));
	}

	/*
	 *Calculate and return the cross product
	*/
	float cross(PVector & v)
	{
		return ((this->x * v.y) - (this->y * v.x));
	}

	/*
	 *Normalize the vector to a length of 1
	*/
	void normalize() 
	{
		float len = mag();
		if (len != 0)
		{
			div(len);
		}	
	}

	/*
	 *Limit the magnitude of the vector
	*/
	void limit(float lim) 
	{	
		if (mag() > lim)
		{
			normalize();
			mult(lim);
		}

	}

	const std::string to_str()
	{
		char tmpbuf[256];
		sprintf_s(tmpbuf, "[%f, %f] \n", this->x, this->y);
		return tmpbuf;
	}

	const sf::Vector2f sf()
	{
		return sf::Vector2f(this->x, this->y);
	}

	/*
	 *Calculates the angle of rotation for a vector (2D vectors only).
	 */
	float heading() 
	{
		return std::atan2(this->x, this->y);
	}

	void rotateBy(float scale) 
	{
		float angle = heading();
		float len = mag();

		this->x = std::cos(scale + angle)* len;
		this->y = std::sin(scale + angle)* len;
	}
	
	void operator=(const PVector & v)
	{
		this->x = v.x;
		this->y = v.y;
	}

	void operator+=(const PVector & v)
	{
		this->x += v.x;
		this->y += v.y;
	}

	void operator-=(const PVector & v)
	{
		this->x -= v.x;
		this->y -= v.y;
	}

	void operator*=(const PVector & v)
	{
		this->x *= v.x;
		this->y *= v.y;
	}

	void operator/=(const PVector & v)
	{
		this->x /= v.x;
		this->y /= v.y;
	}


private:
	float x, y;

};

