#include "PathFinder.h"


PathFinder::PathFinder(void)
{
}


PathFinder::~PathFinder(void)
{
}

/**
* 
*
**/

void PathFinder::initialize(std::list<PolygonPtr>& p_pathPolygons, std::list<PolygonPtr>& p_obstaclePolygons, boost::shared_ptr<sf::Vector3f> p_start, boost::shared_ptr<sf::Vector3f> p_end)
{
	PolygonPtr startPolygon = PolygonPtr();
	PolygonPtr endPolygon = PolygonPtr();

	//if the end is in an obstacle
	for (auto itObstPolygon = m_obstaclePolygons.begin(); itObstPolygon != m_obstaclePolygons.end(); ++itObstPolygon)
	{
		PolygonPtr currPolygon = *itObstPolygon;
		if (currPolygon->isIn(m_end)) 
		{

		}
	}

	//identifies the start and end polygon
	//calls the polygon to define PathPoints
	for (auto itPathPolygon = m_pathPolygons.begin(); itPathPolygon != m_pathPolygons.end(); ++itPathPolygon)
	{
		PolygonPtr currPolygon = *itPathPolygon;
		if (currPolygon->isIn(m_start))
		{
			startPolygon = currPolygon;
		}
		if (currPolygon->isIn(m_end))
		{
			endPolygon = currPolygon;
		}
		currPolygon->definePathPoints();
	}

	std::list<PolygonPtr> obstacles;
	for (auto itObstPolygon = m_obstaclePolygons.begin(); itObstPolygon != m_obstaclePolygons.end(); ++itObstPolygon)
	{
		PolygonPtr currObstPolygon;
		for (int i = 0; i < currObstPolygon->getPointCount(); ++i)
		{
			PropertyPointPtr currObstPoint = currObstPolygon->getPoint(i);
			if (startPolygon->isIn(currObstPoint))
			{
				obstacles.push_back(currObstPolygon);
			}
		}

		for (int i = 0; i < startPolygon->getPointCount(); ++i)
		{
			PropertyPointPtr currPoint = startPolygon->getPoint(i);
			if (currObstPolygon->isIn(currPoint))
			{
				obstacles.push_back(currObstPolygon);
			}
		}
	}
	obstacles.unique();

	//checks which points of other obstacles can be seen from the found obstacles 
	for (auto itObstPolygon = obstacles.begin(); itObstPolygon != obstacles.end(); ++itObstPolygon)
	{
		PolygonPtr currObstPolygon = *itObstPolygon;
		for (auto itObstPolygon2 = obstacles.begin(); itObstPolygon2 != obstacles.end(); ++itObstPolygon2)
		{
			for (int i = 0; i < currObstPolygon->getPathPointCount(); ++i)
			{
				PropertyPointPtr currObstPathPoint = currObstPolygon->getPoint(i);


			}

		}

		}
	}



}

bool PathFinder::findPath(void)
{
	PolygonPtr startPolygon = PolygonPtr();
	PolygonPtr endPolygon = PolygonPtr();








}
