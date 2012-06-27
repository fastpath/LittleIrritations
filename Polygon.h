#pragma once
#include <vector>
#include "PropertyLine.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <boost/shared_ptr.hpp>
#include <cmath>
#include "PropertyPoint.h"

class Polygon;
typedef boost::shared_ptr<Polygon> PolygonPtr;

class Polygon
{
public:
	Polygon(void);
	Polygon(bool p_pathPolygon);
	~Polygon(void);

	void addPoint(float p_x, float p_y);
	void addPoint(sf::Vector2f& p_point);
	void addPoint(sf::Vector3f& p_point);

	bool isIn(float p_x, float p_y);
	bool isIn(boost::shared_ptr<sf::Vector3f> p_pPoint);
	bool isIn(sf::Vector2f& p_point);
	bool isIn(sf::Vector2f& p_start, sf::Vector2f& p_end);

	bool intersectsWith(PropertyLinePtr otherLine);

	void draw(boost::shared_ptr<sf::RenderWindow> p_app) const;

	unsigned int getPointCount() const;
	PropertyPointPtr getPoint(unsigned int index) const;

	unsigned int getPathPointCount() const;
	PropertyPointPtr getPathPoint(unsigned int index) const;

	void definePathPoints(void);


private:
	std::vector<PropertyPointPtr> m_points;
	std::vector<PropertyPointPtr> m_pathPoints;
	std::vector<PropertyLinePtr> m_lines;

	void updateInternals(void);

	float m_maxX;
	float m_minX;

	float m_maxY;
	float m_minY;

	bool m_pathPolygon; //is this a path or obstaclePolygon

	bool m_ready; //all Points are analyzed for Pathfinding
};

