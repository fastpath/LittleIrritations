#pragma once
#include "EventManagerImpl.h"
#include "MovableActor.h"
#include "MyProcess.h"
#include "PropertyLine.h"
#include <vector>
#include <cmath>


class PathAnimator : public IEventListener, public MyProcess
{
public:
	PathAnimator(MovableActorWeakPtr p_pNewActor);
	~PathAnimator(void);

	virtual bool VprocessEvent(EventPtr p_event);
	virtual void VonUpdate(float p_deltaMs);

	virtual void VonInit(void);

	void addLine(PropertyLinePtr p_pNewLine);

private:
	std::vector<PropertyLinePtr> m_pathLines;
	std::vector<float> m_lineWalkTimes;

	MovableActorWeakPtr m_pCurrActor;

	int m_currLineID;
	float m_currTime;
	float m_pathDuration;

};

