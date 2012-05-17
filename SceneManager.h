#pragma once
#include <boost/shared_ptr.hpp>
#include "Pose.h"
#include "Player.h"
#include "IEventListener.h"
#include "Property.h"

class SceneManager : public IEventListener
{
private:
	boost::shared_ptr<Player> player;

	bool VprocessEvent(EventPtr p_event);	

public:
	SceneManager(void);
	~SceneManager(void);

	void setPlayer(boost::shared_ptr<Player> newPlayer){ player = newPlayer;};
};

