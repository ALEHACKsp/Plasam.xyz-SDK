#include "Aimbot.h"

BasePlayer* getClosestPlayer(BasePlayer* localPlayer)
{
	BasePlayer* closestEnemy = NULL;

	float bestFov = 180;

	for (int i = 1; i < g_EngineClient->getMaxClients(); i++)
	{
		BasePlayer* iPlayer = (BasePlayer*)g_EntityList->GetClientEntity(i);

		if (!iPlayer)
			continue;

		if (iPlayer == localPlayer)
			continue;

		if (!iPlayer->isAlive())
			continue;

		if (iPlayer->m_iTeamNum() == localPlayer->m_iTeamNum())
			continue;

		Vector eVecTarget = iPlayer->GetHitboxPos(HITBOX_HEAD);
		Vector pVecTarget = localPlayer->GetEyePos();

		QAngle viewAngles;
		g_EngineClient->getViewAngles(viewAngles);

		float fov = Math::GetFov(viewAngles, Math::CalcAngle(eVecTarget, pVecTarget));

		if (!localPlayer->CanSeePlayer(iPlayer, HITBOX_HEAD))
			continue;

		if (fov < bestFov)
		{
			bestFov = fov;
			closestEnemy = iPlayer;
		}
	}

	return closestEnemy;
}

namespace aimbot
{
	void createMove(CUserCmd * cmd)
	{
		QAngle oldAngle;

		g_EngineClient->getViewAngles(oldAngle);

		BasePlayer* localPlayer = (BasePlayer*)g_EntityList->GetClientEntity(g_EngineClient->getLocalPlayer());

		if (!localPlayer || !localPlayer->isAlive())
		{
			return;
		}

		//BaseWeapon* activeWeapon = (BaseWeapon*)

		BasePlayer* Enemy = getClosestPlayer(localPlayer);

		if (Enemy != NULL)
		{
			Vector eVecTarget = Enemy->GetHitboxPos(HITBOX_HEAD);
			Vector pVecTarget = localPlayer->GetEyePos();


			QAngle angle;
			angle = Math::CalcAngle(eVecTarget, pVecTarget);

			//angle = aimbot::rcs(angle, cmd);
			//angle = aimbot::smooth(angle, cmd);

			Math::NormalizeAngles(angle);
			Math::ClampAngles(angle);


			cmd->viewangles = angle;
			g_EngineClient->setViewAngles(cmd->viewangles);
		}
	}
}
