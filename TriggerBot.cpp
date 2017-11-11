#include "TriggerBot.h"

void TriggerBot::CreateMove(CUserCmd* cmd)
{
	

	BasePlayer* localPlayer = (BasePlayer*)g_EntityList->GetClientEntity(g_EngineClient->getLocalPlayer());

	Vector traceStart, traceEnd;

	trace_t tr;

	QAngle viewAngles;
	g_EngineClient->getViewAngles(viewAngles);

	Math::AngleVectors(viewAngles, traceEnd);

	traceStart = localPlayer->GetEyePos();
	traceEnd = traceStart + (traceEnd * 8192.0f);

	Ray_t ray;
	ray.Init(traceStart, traceEnd);
	CTraceFilter traceFilter;
	traceFilter.pSkip = localPlayer;
	
	g_EngineTrace->TraceRay(ray, 0x46004003, &traceFilter, &tr);

	BasePlayer* player = (BasePlayer*)tr.hit_entity;

	if (!player)
		return;

	if (!player->isPlayer())
		return;

	if (!player->isDormant())
		return;

	if (!player->isAlive())
		return;

	if (!localPlayer->CanSeePlayer(player, HITBOX_HEAD))
		return;

	BaseWeapon*  activeWeapon = (BaseWeapon*)g_EntityList->GetClientEntityFromHandle(localPlayer->m_hActiveWeapon());

	if (activeWeapon->m_flNextPrimaryAttack() > g_GlobalVars->curtime)
	{
		cmd->buttons &= ~IN_ATTACK;
	}
	else
	{
		cmd->buttons |= IN_ATTACK;
	}	

}