#pragma once
#include <list>
#include <SFML/System/Vector2.hpp>
#include <boost/shared_ptr.hpp>

class Polygon;
typedef boost::shared_ptr<Polygon> PolygonPtr;

class Polygon
{
public:
	Polygon(void);
	~Polygon(void);

	void addPoint(float p_x, float p_y);
	void addPoint(sf::Vector2f& p_point);

	bool isIn(float p_x, float p_y);
	bool isIn(sf::Vector2f& p_point);
	bool isIn(sf::Vector2f& p_start, sf::Vector2f& p_end);

private:
	std::list<sf::Vector2f> m_points;
};

