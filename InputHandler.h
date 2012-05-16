#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>
#include "EventManagerImpl.h"
#include "Property.h"
#include "Pose.h"

const float KEY_REPEAT_DELTA = 200;

class InputHandler
{
public:
	InputHandler(boost::shared_ptr<sf::RenderWindow> p_app);
	~InputHandler(void);

	void handleKeys();

private:
	boost::shared_ptr<sf::RenderWindow> m_app;
};

