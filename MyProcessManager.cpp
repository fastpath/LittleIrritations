#include "MyProcessManager.h"

MyProcessManager::~MyProcessManager(void)
{
	clearAllProcesses();
}

unsigned int MyProcessManager::updateProcesses(float p_deltaMs)
{
    unsigned short int successCount = 0;
    unsigned short int failCount = 0;

	

    std::list<MyProcessStrongPtr>::iterator it = m_processList.begin();
    while (it != m_processList.end())
    {
        // grab the next process
        MyProcessStrongPtr pCurrProcess = (*it);

        // save the iterator and increment the old one in case we need to remove this process from the list
        std::list<MyProcessStrongPtr>::iterator thisIt = it;
        ++it;

        // process is uninitialized, so initialize it
        if (pCurrProcess->getState() == MyProcess::UNINITIALIZED)
            pCurrProcess->VonInit();

        // give the process an update tick if it's running
        if (pCurrProcess->getState() == MyProcess::RUNNING)
            pCurrProcess->VonUpdate(p_deltaMs);

        // check to see if the process is dead
        if (pCurrProcess->isDead())
        {
            // run the appropriate exit function
            switch (pCurrProcess->getState())
            {
                case MyProcess::SUCCEEDED :
                {
                    pCurrProcess->VonSuccess();
                    MyProcessStrongPtr pChild = pCurrProcess->removeChild();
                    if (pChild)
                        attachProcess(pChild);
                    else
                        ++successCount;  // only counts if the whole chain completed
                    break;
                }

                case MyProcess::FAILED :
                {
                    pCurrProcess->VonFail();
                    ++failCount;
                    break;
                }

                case MyProcess::ABORTED :
                {
                    pCurrProcess->VonAbort();
                    ++failCount;
                    break;
                }
            }

            // remove the process and destroy it
            m_processList.erase(thisIt);
        }
    }

    return ((successCount << 16) | failCount);
}

MyProcessWeakPtr MyProcessManager::attachProcess(MyProcessStrongPtr p_Process)
{
    m_processList.push_back(p_Process);
    return MyProcessWeakPtr(p_Process);
}

void MyProcessManager::clearAllProcesses(void)
{

}

unsigned int MyProcessManager::getProcessCount(void) const
{ 
	return m_processList.size();
}

void MyProcessManager::abortAllProcesses(bool p_immediate)
{
    std::list<MyProcessStrongPtr>::iterator it = m_processList.begin();
    while (it != m_processList.end())
    {
        std::list<MyProcessStrongPtr>::iterator tempIt = it;
        ++it;

        MyProcessStrongPtr pProcess = *tempIt;
        if (pProcess->isAlive())
        {
            pProcess->setState(MyProcess::ABORTED);
            if (p_immediate)
            {
                pProcess->VonAbort();
                m_processList.erase(tempIt);
            }
        }
    }
}