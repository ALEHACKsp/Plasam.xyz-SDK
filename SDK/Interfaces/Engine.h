#pragma once

class BaseEntity;
class CBaseHandle;

#include "../Structures/Matrix.h"
#include "../Utils.h"

class EngineClient
{
	public:
		void GetScreenSize(int& Width, int& Height)
		{
			typedef void(__thiscall* _GetScreenSize)(void*, int&, int&);
			utils::emulate< _GetScreenSize >(this, 5)(this, Width, Height);
		}

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

		bool IsInGame()
		{
			typedef bool(__thiscall* OriginalFn)(PVOID);
			return utils::emulate< OriginalFn >(this, 26)(this);
		}

		const VMatrix&	WorldToScreenMatrix(void)
		{
			typedef VMatrix&(__thiscall* _Orig)(void*);
			return utils::emulate<_Orig>(this, 37)(this);
		}
};

class EntityList
{
private:
	virtual void*					GetClientNetworkable(int entnum) = 0;
	virtual void*					vtablepad0x1(void) = 0;
	virtual void*					vtablepad0x2(void) = 0;
public:
	virtual BaseEntity*				GetClientEntity(int entNum) = 0;
	virtual BaseEntity*				GetClientEntityFromHandle(CBaseHandle hEnt) = 0;
	virtual int						NumberOfEntities(bool bIncludeNonNetworkable) = 0;
	virtual int						GetHighestEntityIndex(void) = 0;
private:
	virtual void					SetMaxEntities(int maxEnts) = 0;
	virtual int						GetMaxEntities() = 0;
};


// Initialize some externs

extern EngineClient*	g_EngineClient;
extern EntityList*		g_EntityList;
