#include "TriggerBot.h"

//Resolve Externs
bool options::triggerbot::enabled = false;

void TriggerBot::CreateMove(CUserCmd* cmd)
{

	if (!options::triggerbot::enabled)
		return;

	//Check triggerbot key state
	if(!g_InputSystem->IsButtonDown(KEY_LALT))
		return;

	BasePlayer* localPlayer = (BasePlayer*)g_EntityList->GetClientEntity(g_EngineClient->getLocalPlayer());

	if (!localPlayer->isAlive())
		return;

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
	
	g_EngineTrace->TraceRay(ray, MASK_SHOT, &traceFilter, &tr);

	BasePlayer* player = (BasePlayer*)tr.hit_entity;

	if (!player)
		return;

	if (!player->isPlayer())
		return;

	if (player->isDormant())
		return;

	if (!player->isAlive())
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