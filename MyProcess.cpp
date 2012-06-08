#include "MyProcess.h"

//---------------------------------------------------------------------------------------------------------------------
// Constructor
//---------------------------------------------------------------------------------------------------------------------
MyProcess::MyProcess(void)
{
	m_state = UNINITIALIZED;
	//m_pParent = NULL;
	//m_pChild = NULL;
}


//---------------------------------------------------------------------------------------------------------------------
// Destructor
//---------------------------------------------------------------------------------------------------------------------
MyProcess::~MyProcess(void)
{
	if (m_pChild)
	{
		m_pChild->VonAbort();
	}
}


/*
//---------------------------------------------------------------------------------------------------------------------
// Attaches this process to the passed in parent.  It's perfectly valid for this process to have been run and you can
// safely call it from within this process' OnUpdate() function.
//---------------------------------------------------------------------------------------------------------------------
bool Process::AttachToParent(Process* pParent)
{
	// If the process is alive, we need to mark it to be removed from the process list without being destroyed.  If 
	// the process is dead, kick and error and don't attach it.  If the process has already been marked for removal,
	// it means we're trying to double-attach this process, which is an error.
	if (IsAlive())
	{
		m_state = REMOVED;
	}
	else if (IsDead())
	{
		GCC_ERROR("Attempting to attach a dead process to a parent");
		return false;
	}
	else if (IsRemoved())
	{
		GCC_ERROR("Attempting to attach a process that is already being removed to another parent");
		return false;
	}

	// Attach this process to the new parent.  It will be attached at the very end of the child tree.
	pParent->AttachChild(this);

	return true;
}
*/


//---------------------------------------------------------------------------------------------------------------------
// Removes the child from this process.  This releases ownership of the child to the caller and completely removes it
// from the process chain.
//---------------------------------------------------------------------------------------------------------------------
MyProcessStrongPtr MyProcess::removeChild(void)
{
	if (m_pChild)
	{
        MyProcessStrongPtr pChild = m_pChild;  // this keeps the child from getting destroyed when we clear it
		m_pChild.reset();
		//pChild->SetParent(NULL);
        return pChild;
	}

	return MyProcessStrongPtr();
}

MyProcessStrongPtr MyProcess::peekChild(void) { 
	return m_pChild; 
}

/*
//---------------------------------------------------------------------------------------------------------------------
// Cancels the top level process in this chain by calling its Fail() function.
//---------------------------------------------------------------------------------------------------------------------
void Process::CancelTopLevelProcess(void)
{
	StrongProcessPtr pTop = GetTopLevelProcess();
	pTop->Fail();
}
*/

MyProcess::State MyProcess::getState(void) const
{
	return m_state;
}

void MyProcess::setState(MyProcess::State p_newState)
{
	m_state = p_newState;
}

bool MyProcess::isAlive(void) const
{
	return (m_state == RUNNING || m_state == PAUSED);
}

bool MyProcess::isDead(void) const
{
	return (m_state == SUCCEEDED || m_state == FAILED || m_state == ABORTED);
}

bool MyProcess::isRemoved(void) const
{
	return (m_state == REMOVED);
}

bool MyProcess::isPaused(void) const
{
	return m_state == PAUSED;
}

void MyProcess::VonInit(void)
{
	m_state = RUNNING;
} 