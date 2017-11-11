#include "BaseEntity.h"

ICollideable* BaseEntity::GetCollideable()
{
	typedef ICollideable*(__thiscall *OrigFn)(void*);
	return utils::emulate<OrigFn>(this, 3)(this);
}

bool BaseEntity::isPlayer()
{
	return utils::emulate<bool(__thiscall*)(BaseEntity*)>(this, 152)(this);
}

bool BaseEntity::isAlive()
{
	return m_lifeState() == LIFE_ALIVE;
}

bool BaseEntity::isDormant()
{
	void *pNetworked = (void*)(this + 0x8);
	typedef bool(__thiscall *OrigFn)(void*);
	return utils::emulate<OrigFn>(pNetworked, 9)(pNetworked);
}

const model_t* BaseEntity::GetModel()
{
	void *pRenderable = (void*)(this + 0x4);
	typedef const model_t*(__thiscall *OrigFn)(void*);
	return utils::emulate<OrigFn>(pRenderable, 8)(pRenderable);
}

Vector BaseEntity::GetHitboxPos(int hitbox_id)
{
	matrix3x4_t boneMatrix[MAXSTUDIOBONES];

	if (SetupBones(boneMatrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0.0f)) {
		auto studio_model = g_ModelInfo->GetStudiomodel(GetModel());
		if (studio_model) {
			auto hitbox = studio_model->pHitboxSet(0)->GetHitbox(hitbox_id);
			if (hitbox) {
				auto
					min = Vector{},
					max = Vector{};

				Math::VectorTransform(hitbox->bbmin, boneMatrix[hitbox->bone], min);
				Math::VectorTransform(hitbox->bbmax, boneMatrix[hitbox->bone], max);

				return (min + max) / 2.0f;
			}
		}
	}
	return Vector{};
}

bool BaseEntity::SetupBones(matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime)
{
	void *pRenderable = (void*)(this + 0x4);
	typedef bool(__thiscall *OrigFn)(void*, matrix3x4_t*, int, int, float);
	return utils::emulate<OrigFn>(pRenderable, 13)(pRenderable, pBoneToWorldOut, nMaxBones, boneMask, currentTime);
}
