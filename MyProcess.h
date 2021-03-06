#pragma once
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

class MyProcess;
typedef boost::shared_ptr<MyProcess> MyProcessStrongPtr;
typedef boost::weak_ptr<MyProcess> MyProcessWeakPtr;

class MyProcess
{
	friend class MyProcessManager;
public:
	enum State
	{
		// Processes that are neither dead nor alive
		UNINITIALIZED = 0,  // created but not running
		REMOVED,  // removed from the process list but not destroyed; this can happen when a process that is already running is parented to another process

		// Living processes
		RUNNING,  // initialized and running
		PAUSED,  // initialized but paused
		
		// Dead processes
		SUCCEEDED,  // completed successfully
		FAILED,  // failed to complete
		ABORTED,  // aborted; may not have started
	};

	MyProcess(void);
	~MyProcess(void);

		// Functions for ending the process.
	inline void succeed(void)
	{
		m_state = SUCCEEDED;
	};
	inline void fail(void)
	{
		m_state = FAILED;
	};
	
	// pause
	inline void pause(void)
	{
		m_state = PAUSED;
	};
	inline void unPause(void)
	{
		m_state = RUNNING;
	};

	// accessors
	State getState(void) const;
	bool isAlive(void) const;
	bool isDead(void) const;
	bool isRemoved(void) const;
	bool isPaused(void) const;

	// child functions
	inline void attachChild(MyProcessStrongPtr pChild);
	MyProcessStrongPtr removeChild(void);  // releases ownership of the child
	MyProcessStrongPtr peekChild(void);  // doesn't release ownership

protected:
	virtual void VonInit(void);  // called during the first update; responsible for setting the initial state (typically RUNNING)
	virtual void VonUpdate(float deltaMs) = 0;  // called every frame
	virtual void VonSuccess(void) { }  // called if the process succeeds (see below)
	virtual void VonFail(void) { }  // called if the process fails (see below)
	virtual void VonAbort(void) { }  // called if the process is aborted (see below)

private:
	State m_state;  // the current state of the process
	MyProcessStrongPtr m_pChild;  // the child process, if any
	void setState(State p_newState);




};

