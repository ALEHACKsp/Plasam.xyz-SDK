#pragma once

#include "Vector.h"
#include "QAngle.h"
#include "Matrix.h"
#include "Math.h"
#include "StudioDefinitions.h"
#include "enums.h"

#include "NetvarManager.h"
#include "Utils.h"

#include "Model.h"

#define NETVAR(type, name, table, netvar)									\
    type& name##() const {													\
        static int _##name = NetvarSys::Get().GetOffset(table, netvar);     \
        return *(type*)((uintptr_t)this + _##name);							\
    }

class BaseEntity
{
public:
	//NetVars

	NETVAR(Vector	, m_vecOrigin	, "DT_BaseEntity"	, "m_vecOrigin"		)

	//Functions
	bool isPlayer();
	const model_t* GetModel();
	bool SetupBones(matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime);
};