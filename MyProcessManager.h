#pragma once
#include "MyProcess.h"
#include <list>

class MyProcessManager
{
	std::list<MyProcessStrongPtr> m_processList;


public:
	~MyProcessManager(void);

	unsigned int updateProcesses(float p_deltaMs);  // updates all attached processes
	MyProcessWeakPtr attachProcess(MyProcessStrongPtr p_Process);  // attaches a process to the process mgr
	void abortAllProcesses(bool p_immediate);

	// accessors
	unsigned int getProcessCount(void) const;

private:
	void clearAllProcesses(void);
};

