#pragma once

#include "BaseEntity.h"

class EngineClient
{
	public:
		int getLocalPlayer(void)
		{
			typedef int(__thiscall* _GetLocalPlayer)(void*);
			return utils::emulate<_GetLocalPlayer>(this, 12)(this);
		}

		void getViewAngles(QAngle& qViewAngles)
		{
			typedef void(__thiscall* OriginalFn)(PVOID, QAngle&);
			utils::emulate< OriginalFn >(this, 18)(this, qViewAngles);
		}

		void setViewAngles(QAngle& vAngles)
		{
			typedef void(__thiscall* fnVA)(void*, QAngle&);
			utils::emulate<fnVA>(this, 19)(this, vAngles);
		}

		int getMaxClients(void)
		{
			typedef int(__thiscall* OriginalFn)(void*);
			return utils::emulate<OriginalFn>(this, 20)(this);
		}
};

class EntityList
{
private:
	virtual void*				  GetClientNetworkable(int entnum) = 0;
	virtual void*                 vtablepad0x1(void) = 0;
	virtual void*                 vtablepad0x2(void) = 0;
public:
	virtual BaseEntity*         GetClientEntity(int entNum) = 0;
	virtual BaseEntity*         GetClientEntityFromHandle(HANDLE hEnt) = 0;
	virtual int                   NumberOfEntities(bool bIncludeNonNetworkable) = 0;
	virtual int                   GetHighestEntityIndex(void) = 0;
private:
	virtual void                  SetMaxEntities(int maxEnts) = 0;
	virtual int                   GetMaxEntities() = 0;
};


// Initialize some externs

extern EngineClient*	g_EngineClient;
extern EntityList*		g_EntityList;
