#include "BaseEntity.h"

bool BaseEntity::isPlayer()
{
	return utils::emulate<bool(__thiscall*)(BaseEntity*)>(this, 152)(this);
}

const model_t* BaseEntity::GetModel()
{
	void *pRenderable = (void*)(this + 0x4);
	typedef const model_t*(__thiscall *OrigFn)(void*);
	return utils::emulate<OrigFn>(pRenderable, 8)(pRenderable);
}

bool BaseEntity::SetupBones(matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
{
	void *pRenderable = (void*)(this + 0x4);
	typedef bool(__thiscall *OrigFn)(void*, matrix3x4_t*, int, int, float);
	return utils::emulate<OrigFn>(pRenderable, 13)(pRenderable, pBoneToWorldOut, nMaxBones, boneMask, currentTime);
}