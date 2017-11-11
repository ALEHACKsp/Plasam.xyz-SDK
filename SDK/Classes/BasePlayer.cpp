#include "BasePlayer.h"

#include "../Structures/Matrix.h"

Vector BasePlayer::getEyePos()
{
	return NULL;
};

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
