#pragma once
#include "MyProcess.h"
#include <list>

class MyProcessManager
{
	std::list<MyProcessStrPtr> m_processList;


public:
	~MyProcessManager(void);

	unsigned int updateProcesses(unsigned long p_deltaMs);  // updates all attached processes
	MyProcessWeaPtr attachProcess(MyProcessStrPtr p_Process);  // attaches a process to the process mgr
	void abortAllProcesses(bool p_immediate);

	// accessors
	unsigned int getProcessCount(void) const;

private:
	void clearAllProcesses(void);
};

