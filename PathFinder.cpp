#include "PathFinder.h"


PathFinder::PathFinder(void)
{
}


PathFinder::~PathFinder(void)
{
}

void PathFinder::initialize(std::list<PolygonPtr>& p_pathPolygons, std::list<PolygonPtr>& p_obstaclePolygons, boost::shared_ptr<sf::Vector3f> p_start, boost::shared_ptr<sf::Vector3f> p_end)
{
	PolygonPtr startPolygon = PolygonPtr();
	PolygonPtr EndPolygon = PolygonPtr();
	for (std::list<PolygonPtr>::iterator itPathPolygon = p_pathPolygons.begin(); itPathPolygon != p_pathPolygons.end(); ++itPathPolygon)
	{



	}


}

bool PathFinder::findPath(void)
{
	PolygonPtr startPolygon = PolygonPtr();
	PolygonPtr EndPolygon = PolygonPtr();
	for (std::list<PolygonPtr>::iterator itObstPolygon = m_obstaclePolygons.begin(); itObstPolygon != m_obstaclePolygons.end(); ++itObstPolygon)
	{
		PolygonPtr currPolygon = *itObstPolygon;
		if (currPolygon->isIn(m_end)) 
		{

		}
	}
	for (std::list<PolygonPtr>::iterator itPathPolygon = p_pathPolygons.begin(); itPathPolygon != p_pathPolygons.end(); ++itPathPolygon)
	{



	}


}
