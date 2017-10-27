#include "BasePlayer.h"

#include "Matrix.h"

Vector BasePlayer::getEyePos()
{
	return NULL;
};

bool BasePlayer::isAlive()
{
	return m_lifeState() == LIFE_ALIVE;
}

Vector BasePlayer::GetHitboxPos(int hitbox_id)
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

Vector BasePlayer::GetEyePos()
{
	return m_vecOrigin() + m_vecViewOffset();
}

bool BasePlayer::CanSeePlayer(BasePlayer* player, int hitbox)
{
	CGameTrace tr;
	Ray_t ray;
	CTraceFilter filter;
	filter.pSkip = this;

	auto endpos = player->GetHitboxPos(hitbox);

	ray.Init(GetEyePos(), endpos);
	g_EngineTrace->TraceRay(ray, MASK_SHOT | CONTENTS_GRATE, &filter, &tr);

	return tr.hit_entity == player || tr.fraction > 0.97f;
}
