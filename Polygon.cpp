#include "Polygon.h"


Polygon::Polygon(void)
{
}


Polygon::~Polygon(void)
{
}

void Polygon::addPoint(float p_x, float p_y)
{
	m_points.push_back(boost::shared_ptr<sf::Vector2f>(new sf::Vector2f(p_x,p_y)));
}

void Polygon::addPoint(sf::Vector2f& p_point)
{
	m_points.push_back(boost::shared_ptr<sf::Vector2f>(&p_point));
}

bool Polygon::isIn(float p_x, float p_y)
{
	return true;
}

bool Polygon::isIn(sf::Vector2f& p_point)
{
	return true;
}

bool Polygon::isIn(sf::Vector2f& p_start, sf::Vector2f& p_end)
{
	return true;
}

void Polygon::draw(boost::shared_ptr<sf::RenderWindow> p_app) const
{
	for (int i=0; i < m_points.size(); ++i)
	{
		sf::Vector2f point1 = *(m_points[i]);
		sf::Vector2f point2 = *(m_points[(i+1)%(m_points.size())]);
		
		sf::Vector2f dir = point2-point1;
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
		sf::Vector2f point1 = *(m_points[i]);
		float width = 10.0f;
		sf::RectangleShape rectangle;
		rectangle.setSize(sf::Vector2f(10,10));
		rectangle.setPosition(sf::Vector2f(point1.x-width/2.0f,point1.y-width/2.0f));
		rectangle.setFillColor(sf::Color::Green);
		p_app->draw(rectangle);
	}
}
