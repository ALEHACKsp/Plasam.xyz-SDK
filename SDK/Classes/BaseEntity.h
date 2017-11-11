#pragma once

#include "../Structures/Vector.h"
#include "../Structures/QAngle.h"
#include "../Structures/CHandle.h"
#include "../Structures/Matrix.h"
#include "./Math.h"
#include "../Structures/StudioDefinitions.h"
#include "../enums.h"

#include "../../NetvarManager.h"
#include "../Utils.h"
#include "../../Math.h"

#include "../Interfaces/Model.h"

#define NETVAR(type, name, table, netvar)									\
    type& name##() const {													\
        static int _##name = NetvarSys::Get().GetOffset(table, netvar);     \
        return *(type*)((uintptr_t)this + _##name);							\
    }

class BaseEntity
{
public:
	//NetVars
	NETVAR(int32_t		, m_iTeamNum	, "DT_BaseEntity"	, "m_iTeamNum"		);
	NETVAR(int32_t		, m_lifeState	, "DT_BasePlayer"	, "m_lifeState"		);
	NETVAR(Vector		, m_vecOrigin	, "DT_BaseEntity"	,	"m_vecOrigin"	);

	const matrix3x4_t& m_rgflCoordinateFrame()
	{
		static auto _m_rgflCoordinateFrame = NetvarSys::Get().GetOffset("DT_BaseEntity", "m_CollisionGroup") - 0x30;
		return *(matrix3x4_t*)((uintptr_t)this + _m_rgflCoordinateFrame);
	}

	//Functions
	ICollideable*	GetCollideable();
	bool			isPlayer();
	bool			isAlive();
	bool			isDormant();
	const model_t*	GetModel();
	Vector			GetHitboxPos(int hitbox_id);
	bool			SetupBones(matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime);
};