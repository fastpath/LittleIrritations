#pragma once
#include "Polygon.h"
#include <list>



/**
*
* Is able to find a path between two points in any polygon
*
*
**/

class PathFinder
{
public:
	PathFinder(void);
	~PathFinder(void);

	void initialize(std::list<PolygonPtr>& p_pathPolygons, std::list<PolygonPtr>& p_obstaclePolygons, boost::shared_ptr<sf::Vector3f> p_start, boost::shared_ptr<sf::Vector3f> p_end); 

	bool findPath(void);

private:
	std::list<PolygonPtr>& m_pathPolygons;
	std::list<PolygonPtr>& m_obstaclePolygons;
	boost::shared_ptr<sf::Vector3f> m_start;
	boost::shared_ptr<sf::Vector3f> m_end;
};

