#pragma once
#include <SFML/Graphics.hpp>

class Vector2fUtils
{
public:
		
	static float dot(sf::Vector2f v1, sf::Vector2f v2) 
	{
		return v1.x * v2.x + v1.y * v2.y;
	}
	//
	static float cross(sf::Vector2f v1, sf::Vector2f v2)
	{
		return (v1.x * v2.y) - (v1.y * v2.x);
	}
	//
	static sf::Vector2f sub(sf::Vector2f v1, sf::Vector2f v2)
	{
		float dx = v1.x - v2.x;
		float dy = v1.y - v2.y;
		return sf::Vector2f(dx, dy);
	}
	//
	static sf::Vector2f add(sf::Vector2f v1, sf::Vector2f v2)
	{
		float dx = v1.x + v2.x;
		float dy = v1.y + v2.y;
		return sf::Vector2f(dx, dy);
	}
	//
	static sf::Vector2f mult(sf::Vector2f v1, float scale)
	{
		float dx = v1.x * scale;
		float dy = v1.y * scale;
		return sf::Vector2f(dx, dy);
	}
	//
	static sf::Vector2f div(sf::Vector2f v1, float scale)
	{
		float dx = v1.x / scale;
		float dy = v1.y / scale;
		return sf::Vector2f(dx, dy);
	}
	//
	static float length(sf::Vector2f v1)
	{
		return std::sqrt((std::pow(v1.x, 2) + std::pow(v1.y, 2)));
	}
	//
	static sf::Vector2f setLength(sf::Vector2f v1, float scale)
	{
		float len = length(v1);
		float dx = (v1.x / len) * scale;
		float dy = (v1.x / len) * scale;
		return sf::Vector2f(dx, dy);
	}
	//
	static sf::Vector2f nomalize(sf::Vector2f v1) 
	{
		sf::Vector2f rs;
		float len = length(v1);
		if (len != 0)
		{
			sf::Vector2f rsxy = div(v1,len);
			rs.x = rsxy.x;
			rs.y = rsxy.y;
		}
		return rs;
	}
	//
	static float getAngle(sf::Vector2f v1) 
	{
		return std::atan2(v1.x, v1.y);
	}
	//
	static sf::Vector2f setAngle(sf::Vector2f v1, float scale) 
	{
		float len = length(v1);
		float dx = std::cos(scale) * len;
		float dy = std::sin(scale) * len;
		return sf::Vector2f(dx, dy);
	}
	//
	static sf::Vector2f rotateBy(sf::Vector2f v1, float scale)
	{
		float angle = getAngle(v1);
		float len = length(v1);
		float dx = std::cos(scale+angle) * len;
		float dy = std::sin(scale+angle) * len;
		return sf::Vector2f(dx, dy);
	}
	//
	static float dist(sf::Vector2f v1, sf::Vector2f v2)
	{
		float len = 0;
		float dx = v2.x - v1.x;
		float dy = v2.y - v1.y;
		sf::Vector2f vs(dx, dy);
		len = length(vs);		
		return len;
	}
	//
	static sf::Vector2f limit(sf::Vector2f v1, float lim)
	{
		sf::Vector2f dn;
		float len = length(v1);
		if (len > lim) 
		{
			sf::Vector2f dx = nomalize(v1);
			dn = mult(dx, lim);
		}
				
		return dn;
	}
	//
	const std::string to_str(sf::Vector2f v1)
	{
		char tmpbuf[256];
		sprintf_s(tmpbuf, "[%f, %f] \n", v1.x, v1.y);
		return tmpbuf;
	}


private:
	Vector2fUtils() {};
	~Vector2fUtils() {};
};
