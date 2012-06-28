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
			m_startPolygon = currPolygon;
		}
		if (currPolygon->isIn(m_end))
		{
			endPolygon = currPolygon;
		}
		currPolygon->definePathPoints();
	}


	//saves obstacles which contain a polygon point or are within the polygon
	for (auto itObstPolygon = m_obstaclePolygons.begin(); itObstPolygon != m_obstaclePolygons.end(); ++itObstPolygon)
	{
		PolygonPtr currObstPolygon;
		for (int i = 0; i < currObstPolygon->getPointCount(); ++i)
		{
			PropertyPointPtr currObstPoint = currObstPolygon->getPoint(i);
			if (startPolygon->isIn(currObstPoint))
			{
				m_currentObstacles.push_back(currObstPolygon);
				
				for (int i = 0; i < currObstPolygon->getPathPointCount(); ++i)
				{
					PropertyPointPtr currObstPathPoint = currObstPolygon->getPathPoint(i);
					m_currentObstaclePathPoints.push_back(currObstPathPoint);
				}
			}
		}

		for (int i = 0; i < startPolygon->getPointCount(); ++i)
		{
			PropertyPointPtr currPoint = startPolygon->getPoint(i);
			if (currObstPolygon->isIn(currPoint))
			{
				m_currentObstacles.push_back(currObstPolygon);
				for (int i = 0; i < currObstPolygon->getPathPointCount(); ++i)
				{
					PropertyPointPtr currObstPathPoint = currObstPolygon->getPathPoint(i);
					m_currentObstaclePathPoints.push_back(currObstPathPoint);
				}
			}
		}
	}
	m_currentObstacles.unique();
	m_currentObstaclePathPoints.unique();

	std::map<PropertyPointPtr,std::list<PropertyPointPtr> > viewList;

	//checks which points of other obstacles can be seen from the found obstacles 
	for (auto itObstPathPoint = m_currentObstaclePathPoints.begin(); itObstPathPoint != m_currentObstaclePathPoints.end(); ++itObstPathPoint)
	{
		//the obstacle points are connected to all other obstacle Points
		for (auto itObstPathPoint2 = m_currentObstaclePathPoints.begin(); itObstPathPoint2 != m_currentObstaclePathPoints.end(); ++itObstPathPoint2)
		{
			if (itObstPathPoint == itObstPathPoint2)
			{
				continue;
			}

			PropertyLinePtr currLine = PropertyLinePtr(new PropertyLine(*itObstPathPoint,*itObstPathPoint2));
			bool intersection = false;
			for (auto itObstacle = m_currentObstacles.begin(); itObstacle != m_currentObstacles.end(); ++itObstacle)
			{
				if ((*itObstacle)->intersectsWith(currLine))
				{
					intersection = true;
					continue;
				}
			}

			if (startPolygon->intersectsWith(currLine))
			{
				intersection = true;
			}

			if (!intersection)
			{
				viewList[*itObstPathPoint].push_back(*itObstPathPoint2);
			}
		}

		//the obstacle Point is connected with all Polygon Points
		for (int i = 0; i < startPolygon->getPathPointCount(); ++i)
		{
			PropertyPointPtr currPolyPoint = startPolygon->getPathPoint(i);

			PropertyLinePtr currLine = PropertyLinePtr(new PropertyLine(*itObstPathPoint,currPolyPoint));

			bool intersection = false;
			for (auto itObstacle = m_currentObstacles.begin(); itObstacle != m_currentObstacles.end(); ++itObstacle)
			{
				if ((*itObstacle)->intersectsWith(currLine))
				{
					intersection = true;
					continue;
				}
			}

			if (startPolygon->intersectsWith(currLine))
			{
				intersection = true;
			}

			if (!intersection)
			{
				viewList[*itObstPathPoint].push_back(currPolyPoint);
			}
		}		
	}
}

bool PathFinder::findPath(void)
{
	PolygonPtr startPolygon = PolygonPtr();
	PolygonPtr endPolygon = PolygonPtr();








}
