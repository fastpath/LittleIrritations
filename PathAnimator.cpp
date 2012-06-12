#include "PathAnimator.h"


PathAnimator::PathAnimator(MovableActorWeakPtr p_pNewActor)
{
	m_pCurrActor = p_pNewActor;
}


PathAnimator::~PathAnimator(void)
{
}

void PathAnimator::VonInit(void)
{

	std::cout << "init that thing " << std::endl;

	m_currTime = 0.0f;
	m_pathDuration = 0.0f;
	m_currLineID = 0;

	float actorWalkspeed = 0.0f;
	if (m_pCurrActor.lock() != NULL && m_pCurrActor.lock()->hasProperty(ACTOR_WALKSPEED))
	{
		m_pCurrActor.lock()->getProperty(actorWalkspeed,ACTOR_WALKSPEED);
	} 
	else
	{
		actorWalkspeed = 100.0f;
	}

	for (int i=0; i < m_pathLines.size(); ++i)
	{
		PropertyLinePtr currLine = m_pathLines[i];
		float lineWalkspeed = 0.0f;
		if (currLine->hasProperty(LINE_WALKSPEED))
		{
			currLine->getProperty(lineWalkspeed,LINE_WALKSPEED);
		} 
		else
		{
			lineWalkspeed = 1.0f;
		}

		sf::Vector3f pathVector = (*currLine->getPathVector());
		float length = std::sqrt(pathVector.x*pathVector.x+pathVector.y*pathVector.y+pathVector.z*pathVector.z);

		float resultTime = (length/(actorWalkspeed*lineWalkspeed));

		//std::cout << "currLine " << i << " resultTime " << resultTime << std::endl;

		m_pathDuration += resultTime;

		m_lineWalkTimes.push_back(resultTime);
	}
	unPause();
}

bool PathAnimator::VprocessEvent(EventPtr p_event)
{
	return true;
}

void PathAnimator::VonUpdate(float p_deltaMs)
{

	//std::cout << "PathANi geht ab" << std::endl;

	m_currTime += p_deltaMs;

	float scale = m_currTime/m_lineWalkTimes[m_currLineID];
	if (scale > 1.0f)
	{
		m_currTime -= m_lineWalkTimes[m_currLineID++];
		scale = 0.0f;
	}
	if (m_currLineID >= m_pathLines.size())
	{
		succeed();
	}
	else
	{

		EventPtr newEvent(new Event(MOVE_ACTOR,0.0f));
		sf::Vector3f newPoint = (*m_pathLines[m_currLineID]->getStartPoint())+(*m_pathLines[m_currLineID]->getPathVector())*scale;
		boost::shared_ptr<sf::Vector3f> moveVector =  boost::shared_ptr<sf::Vector3f>(new sf::Vector3f(newPoint));
		//std::cout << "currLine " << m_currLineID << "scale " << scale << " TestPosi   " << newPoint.x << ", " << newPoint.y << ", " << newPoint.z << std::endl;
		PropertyPtr position = PropertyPtr(new TProperty<boost::shared_ptr<sf::Vector3f>>(VECTOR3FPTR,moveVector));
		newEvent->addProperty(position);

		PropertyPtr button = PropertyPtr(new TProperty<MovableActorWeakPtr>(MOVABLEACTORPTR, m_pCurrActor));
		newEvent->addProperty(button);

		IBaseEventManager::Get()->VQueueEvent(newEvent);

		
	}
}

void PathAnimator::addLine(PropertyLinePtr p_pNewLine)
{
	m_pathLines.push_back(p_pNewLine);
}

