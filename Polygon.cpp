#include "Polygon.h"


Polygon::Polygon(void)
{
}


Polygon::~Polygon(void)
{
}

void Polygon::addPoint(float p_x, float p_y)
{
	m_points.push_back(boost::shared_ptr<sf::Vector3f>(new sf::Vector3f(p_x,p_y,0.0f)));
	updateInternals();
}

void Polygon::addPoint(sf::Vector2f& p_point)
{
	m_points.push_back(boost::shared_ptr<sf::Vector3f>(new sf::Vector3f(p_point.x,p_point.y,0.0f)));
	updateInternals();
}

void Polygon::updateInternals(void)
{
	int pointsSize = m_points.size();
	boost::shared_ptr<sf::Vector3f> newPoint = m_points[pointsSize-1];

	if(newPoint->x > m_maxX)
	{
		m_maxX = newPoint->x;
	}
	if(newPoint->y > m_maxY)
	{
		m_maxY = newPoint->y;
	}
	if(newPoint->x < m_minX)
	{
		m_minX = newPoint->x;
	}
	if(newPoint->y < m_minY)
	{
		m_minY = newPoint->y;
	}
	
	if(pointsSize > 1)
	{
		if(m_lines.size() > 0)
		{
			m_lines.erase(m_lines.end()-1);
		}
		PropertyLinePtr pNewLine = PropertyLinePtr(new PropertyLine(newPoint,m_points[pointsSize-2]));
		PropertyLinePtr pNewLine2 = PropertyLinePtr(new PropertyLine(newPoint,m_points[0]));
		m_lines.push_back(pNewLine);
		m_lines.push_back(pNewLine2);
	}
}

bool Polygon::isIn(float p_x, float p_y)
{

	int hitCounter = 0;

	for(std::vector<PropertyLinePtr>::iterator itLine = m_lines.begin(); itLine != m_lines.end(); ++itLine)
	{
		PropertyLinePtr currLine = *itLine;
		boost::shared_ptr<sf::Vector3f> startPoint = currLine->getStartPoint();
		boost::shared_ptr<sf::Vector3f> lineVec = currLine->getPathVector();

		float tX = (p_x-startPoint->x)/lineVec->x;
		if(tX < 0.0f || tX > 1.0f)
		{
			continue;
		}
		if ((startPoint->y + tX * lineVec->y) > p_y)
		{
			hitCounter++;
		}
	}
	if ( hitCounter == 0 || hitCounter % 2 == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Polygon::isIn(sf::Vector2f& p_point)
{
	return isIn(p_point.x, p_point.y);
}

bool Polygon::isIn(sf::Vector2f& p_start, sf::Vector2f& p_end)
{



	return true;
}

void Polygon::draw(boost::shared_ptr<sf::RenderWindow> p_app) const
{
	for (int i=0; i < m_lines.size(); ++i)
	{
		PropertyLinePtr currLine = m_lines[i];
		sf::Vector2f point1 = sf::Vector2f(currLine->getStartPoint()->x,currLine->getStartPoint()->y);
		
		sf::Vector2f dir = sf::Vector2f(currLine->getPathVector()->x,currLine->getPathVector()->y);;
		float length = std::sqrt(dir.x*dir.x+dir.y*dir.y);
		dir.x = dir.x/length;
		dir.y = dir.y/length;

		int signY = (0.0f<dir.y)-(dir.y<0.0f);
		int signX = (0.0f<dir.x)-(dir.x<0.0f);

		sf::RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(length,5));
		rectangle.setPosition(point1);
		rectangle.setFillColor(sf::Color::Red);
		rectangle.rotate((dir.y < 0 ? -1.0f : 1.0f)*std::acos(dir.x)*180.0f/3.14f);
		p_app->draw(rectangle);
	}

	for (int i=0; i < m_points.size(); ++i)
	{
		sf::Vector2f point1 = sf::Vector2f(m_points[i]->x,m_points[i]->y);
		float width = 10.0f;
		sf::RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(10,10));
		rectangle.setPosition(sf::Vector2f(point1.x-width/2.0f,point1.y-width/2.0f));
		rectangle.setFillColor(sf::Color::Green);
		p_app->draw(rectangle);
	}
}

void Polygon::definePathPoints(void)
{
	if (m_points.size() < 4)
	{
		return;
	}
	for (std::vector<boost::shared_ptr<sf::Vector3f>>::iterator itPoint = m_points.begin(); itPoint != m_points.end()-2; ++itPoint)
	{
		boost::shared_ptr<sf::Vector3f> startPoint = *itPoint;
		boost::shared_ptr<sf::Vector3f> currPoint = *(itPoint+1);
		boost::shared_ptr<sf::Vector3f> endPoint = *(itPoint+2);



	}

}
