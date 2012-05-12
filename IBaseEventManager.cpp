#include "IBaseEventManager.h"

static IBaseEventManager* g_pEventMgr = NULL;

IBaseEventManager* IBaseEventManager::Get(void)
{
	return g_pEventMgr;
}

IBaseEventManager::IBaseEventManager(const char* p_name, bool p_setAsGlobal)
{
	if (p_setAsGlobal)
	{
		if (g_pEventMgr)
		{
			delete g_pEventMgr;
		}
		g_pEventMgr = this;
	}
}


IBaseEventManager::~IBaseEventManager(void)
{
	if (g_pEventMgr == this)
		g_pEventMgr = NULL;
}
