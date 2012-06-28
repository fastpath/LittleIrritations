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

	const void initialize(std::vector<PolygonPtr>& p_pathPolygons, std::vector<PolygonPtr>& p_obstaclePolygons, PropertyPointPtr p_start, PropertyPointPtr p_end); 

	std::vector<PropertyPointPtr> findPath(void);

private:
	std::vector<PolygonPtr> m_pathPolygons;
	std::vector<PolygonPtr> m_obstaclePolygons;

	PropertyPointPtr m_start;
	PropertyPointPtr m_end;

	PolygonPtr m_startPolygon;
	std::list<PolygonPtr> m_currentObstacles;
	std::list<PropertyPointPtr> m_currentObstaclePathPoints;
	std::map<PropertyPointPtr,std::list<PropertyPointPtr> > m_viewList;

	bool collidesWithAnyLine(PropertyLinePtr p_pLine);

	std::vector<PropertyPointPtr> findPathRec(std::vector<PropertyPointPtr> p_currPoints);
};

