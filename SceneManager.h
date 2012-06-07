#pragma once
#include <boost/shared_ptr.hpp>
#include "Pose.h"
#include "Player.h"
#include "IEventListener.h"
#include "Property.h"

class SceneManager : public IEventListener
{
private:
	boost::shared_ptr<Player> m_player;

	bool VprocessEvent(EventPtr p_event);	

public:
	SceneManager(void);
	~SceneManager(void);

	void setPlayer(boost::shared_ptr<Player> p_newPlayer){ m_player = p_newPlayer;};

	bool m_guiActive;
};

