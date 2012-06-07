#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>
#include <cmath>

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

	void draw(boost::shared_ptr<sf::RenderWindow> p_app) const;
	unsigned int GetPointCount() const;
	sf::Vector2f GetPoint(unsigned int index) const;


private:
	std::vector<boost::shared_ptr<sf::Vector2f>> m_points;
};

