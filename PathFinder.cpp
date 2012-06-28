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

const void PathFinder::initialize(std::vector<PolygonPtr>& p_pathPolygons, std::vector<PolygonPtr>& p_obstaclePolygons, PropertyPointPtr p_start, PropertyPointPtr p_end)
{
	m_pathPolygons = p_pathPolygons;
	m_obstaclePolygons = p_obstaclePolygons;

	m_start = p_start;
	m_end = p_end;

	/*if the end is in an obstacle
	for (auto itObstPolygon = m_obstaclePolygons.begin(); itObstPolygon != m_obstaclePolygons.end(); ++itObstPolygon)
	{
		PolygonPtr currPolygon = *itObstPolygon;
		if (currPolygon->isIn(m_end)) 
		{

		}
	}*/


	//identifies the start and end polygon
	//calls the polygon to define PathPoints
	for (auto itPathPolygon = m_pathPolygons.begin(); itPathPolygon != m_pathPolygons.end(); ++itPathPolygon)
	{
		PolygonPtr currPolygon = *itPathPolygon;
		if (currPolygon->isIn(p_start))
		{
			m_startPolygon = currPolygon;
		}
		if (currPolygon->isIn(p_end))
		{
			//endPolygon = currPolygon;
		}
		currPolygon->definePathPoints();
	}

		std::cout << "huhubla2" << std::endl;
	//saves obstacles which contain a polygon point or are within the polygon
	for (auto itObstPolygon = m_obstaclePolygons.begin(); itObstPolygon != m_obstaclePolygons.end(); ++itObstPolygon)
	{
		PolygonPtr currObstPolygon = *itObstPolygon;

		currObstPolygon->definePathPoints();

		for (int i = 0; i < currObstPolygon->getPointCount(); ++i)
		{
			PropertyPointPtr currObstPoint = currObstPolygon->getPoint(i);
			if ((m_startPolygon)->isIn(currObstPoint))
			{
				m_currentObstacles.push_back(currObstPolygon);
				
				for (int i = 0; i < currObstPolygon->getPathPointCount(); ++i)
				{
					PropertyPointPtr currObstPathPoint = currObstPolygon->getPathPoint(i);
					m_currentObstaclePathPoints.push_back(currObstPathPoint);
				}
			}
		}

		for (int i = 0; i < (m_startPolygon.get())->getPointCount(); ++i)
		{
			PropertyPointPtr currPoint = (m_startPolygon.get())->getPoint(i);
					
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
	
	std::list<PolygonPtr> tempList2;

	for (auto itObstPathPoint = m_currentObstacles.begin(); itObstPathPoint != m_currentObstacles.end(); ++itObstPathPoint)
	{
		PolygonPtr currPoint = *itObstPathPoint;
		bool good = true;
		for (auto itTempPathPoint = tempList2.begin(); itTempPathPoint != tempList2.end(); ++itTempPathPoint)
		{
			PolygonPtr currPoint2 = *itTempPathPoint;
			if ((currPoint.get()) == (currPoint2.get()))
			{
				good = false;
			}
		}
		if (good)
		{
			tempList2.push_back(currPoint);
		}
	}
	m_currentObstacles = tempList2;
	
	for (int i=0; i < (m_startPolygon)->getPathPointCount(); ++i)
	{
		m_currentObstaclePathPoints.push_back((m_startPolygon)->getPathPoint(i));
	}

	std::list<PropertyPointPtr> tempList;

	for (auto itObstPathPoint = m_currentObstaclePathPoints.begin(); itObstPathPoint != m_currentObstaclePathPoints.end(); ++itObstPathPoint)
	{
		PropertyPointPtr currPoint = *itObstPathPoint;
		bool good = true;
		for (auto itTempPathPoint = tempList.begin(); itTempPathPoint != tempList.end(); ++itTempPathPoint)
		{
			PropertyPointPtr currPoint2 = *itTempPathPoint;
			if ((currPoint.get()) == (currPoint2.get()))
			{
				good = false;
			}
		}
		if (good)
		{
			tempList.push_back(currPoint);
		}
	}

	m_currentObstaclePathPoints = tempList;

	//for (auto itViewPoint = m_currentObstaclePathPoints.begin(); itViewPoint != m_currentObstaclePathPoints.end(); ++itViewPoint)
	//{
	//	PropertyPointPtr currPoint = (*itViewPoint);
		//std::cout << "ObstacleGoodPointt: " << currPoint->x << "," << currPoint->y << "," << currPoint->z << std::endl;
	//}

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
					break;
				}
			}

			if ((m_startPolygon)->intersectsWith(currLine))
			{
				intersection = true;
			}

			if (!intersection)
			{
				m_viewList[*itObstPathPoint].push_back(*itObstPathPoint2);
			}
		}
	}




}

std::vector<PropertyPointPtr> PathFinder::findPath(void)
{

	std::list<PropertyPointPtr> visiblePointsFromStart;

	//the obstacle points are connected to all other obstacle Points
	for (auto itObstPathPoint = m_currentObstaclePathPoints.begin(); itObstPathPoint != m_currentObstaclePathPoints.end(); ++itObstPathPoint)
	{

		PropertyLinePtr currLine = PropertyLinePtr(new PropertyLine(m_start,*itObstPathPoint));
		bool intersection = false;
		for (auto itObstacle = m_currentObstacles.begin(); itObstacle != m_currentObstacles.end(); ++itObstacle)
		{
			if ((*itObstacle)->intersectsWith(currLine))
			{
				intersection = true;
				break;
			}
		}

		if ((m_startPolygon)->intersectsWith(currLine))
		{
			intersection = true;
		}

		if (!intersection)
		{
			visiblePointsFromStart.push_back(*itObstPathPoint);
		}
	}

	PropertyLinePtr fromStartToEnd = PropertyLinePtr(new PropertyLine(m_start,m_end));

	if (!collidesWithAnyLine(fromStartToEnd))
	{
		std::cout << "fertig!!!!!!" << std::endl;
	}
	else
	{
		std::cout << " nicht fertig!!!!!!" << std::endl;
	}

	float maxLength = 100000;
	PropertyPointPtr bestPoint;
	for (auto itVisiblePoint = visiblePointsFromStart.begin(); itVisiblePoint != visiblePointsFromStart.end(); ++itVisiblePoint)
	{
		PropertyPointPtr currVisPoint = (*itVisiblePoint);
		PropertyLinePtr fromStartToVis = PropertyLinePtr(new PropertyLine(m_start,currVisPoint));
		PropertyLinePtr fromVisToEnd = PropertyLinePtr(new PropertyLine(currVisPoint,m_end));

		if ((fromStartToVis->length()+fromVisToEnd->length()) < maxLength)
		{
			maxLength = (fromStartToVis->length()+fromVisToEnd->length());
			bestPoint = currVisPoint;
		}
	}

	std::vector<PropertyPointPtr> pointList;
	pointList.push_back(m_start);
	pointList.push_back(bestPoint);


	pointList = findPathRec(pointList);
	std::cout << pointList.size() << std::endl;

	return pointList;
}

bool PathFinder::collidesWithAnyLine(PropertyLinePtr p_pLine)
{
		bool intersection = false;
		for (auto itObstacle = m_currentObstacles.begin(); itObstacle != m_currentObstacles.end(); ++itObstacle)
		{
			if ((*itObstacle)->intersectsWith(p_pLine))
			{
				intersection = true;
				break;
			}
		}

		if ((m_startPolygon)->intersectsWith(p_pLine))
		{
			intersection = true;
		}

		return intersection;
}

std::vector<PropertyPointPtr> PathFinder::findPathRec(std::vector<PropertyPointPtr> p_currPoints)
{
	PropertyPointPtr currStartPoint = *(p_currPoints.end()-1);
	PropertyLinePtr fromStartToEnd = PropertyLinePtr(new PropertyLine(currStartPoint,m_end));
	if (!collidesWithAnyLine(fromStartToEnd))
	{
		p_currPoints.push_back(m_end);
		return p_currPoints;
	}
	else
	{
		for (auto itViewList = m_viewList.begin(); itViewList != m_viewList.end(); ++itViewList)
		{
			PropertyPointPtr currPoint = (*itViewList).first;
			std::list<PropertyPointPtr> viewablePoints = (*itViewList).second;

			if (currPoint.get() == currStartPoint.get())
			{
				std::cout << "StartPointt: " << currPoint->x << "," << currPoint->y << "," << currPoint->z << std::endl;

				float maxLength = 100000;
				PropertyPointPtr bestPoint;
				for (auto itViewPoint = viewablePoints.begin(); itViewPoint != viewablePoints.end(); ++itViewPoint)
				{
					PropertyPointPtr currVisPoint = (*itViewPoint);
					std::cout << "ViewablePointt: " << currPoint->x << "," << currPoint->y << "," << currPoint->z << std::endl;
					
					PropertyLinePtr fromStartToVis = PropertyLinePtr(new PropertyLine(currStartPoint,currVisPoint));
					PropertyLinePtr fromVisToEnd = PropertyLinePtr(new PropertyLine(currVisPoint,m_end));

					if ((fromStartToVis->length()+fromVisToEnd->length()) < maxLength)
					{
						maxLength = (fromStartToVis->length()+fromVisToEnd->length());
						bestPoint = currVisPoint;
					}

				}

				if (p_currPoints.size() >= 2)
				{
					PropertyPointPtr endMinusTwo = *(p_currPoints.end()-2);

					bool found = false;

					for (auto itViewList = m_viewList.begin(); itViewList != m_viewList.end(); ++itViewList)
					{
						PropertyPointPtr currPoint = (*itViewList).first;
						std::list<PropertyPointPtr> viewablePoints = (*itViewList).second;

						if (currPoint.get() == bestPoint.get())
						{
							for (auto itViewPoint = viewablePoints.begin(); itViewPoint != viewablePoints.end(); ++itViewPoint)
							{
								PropertyPointPtr currVisPoint = (*itViewPoint);
								if (currVisPoint.get() == endMinusTwo.get())
								{
									found = true;
								}
							}
						}
					}

					if (found)
					{
						p_currPoints.erase(p_currPoints.end()-1);
					}

				}



				p_currPoints.push_back(bestPoint);
				return findPathRec(p_currPoints);
			}
		}
		
	}
}
