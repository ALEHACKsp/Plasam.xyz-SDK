#include "Aimbot.h"

//Resolve externs
bool	options::aimbot::enabled			= false;
bool	options::aimbot::closestBoneEnabled = false;
bool	options::aimbot::friendlyFire		= false;
int		options::aimbot::bone				= HITBOX_HEAD;
float	options::aimbot::fov				= 0;
float	options::aimbot::smoothing			= 0;
float	options::aimbot::rcs				= 2;
float	options::aimbot::killTimeout		= 0;

const int importantBones[] = {HITBOX_HEAD,HITBOX_CHEST,HITBOX_LOWER_NECK,HITBOX_NECK};

Vector getClosestSpot(BasePlayer* localPlayer, BasePlayer* enemy)
{
	QAngle viewAngles;
	g_EngineClient->getViewAngles(viewAngles);

	float tempFov = options::aimbot::fov;

	Vector pVecTarget = localPlayer->GetEyePos();

	Vector tempSpot = { 0,0,0 };

	for (int i = 0; i < 4; i++)
	{
		if (!localPlayer->CanSeePlayer(enemy, importantBones[i]))
			continue;

		Vector cbVecTarget = enemy->GetHitboxPos(importantBones[i]);

		float cbFov = Math::GetFov(viewAngles, Math::CalcAngle(cbVecTarget, pVecTarget));

		if (cbFov < tempFov)
		{
			tempFov = cbFov;
			tempSpot = cbVecTarget;
		}
	}

	return tempSpot;
}

BasePlayer* getClosestPlayer(BasePlayer* localPlayer)
{
	BasePlayer* closestEnemy = NULL;

	float bestFov = options::aimbot::fov;

	for (int i = 1; i < g_EngineClient->getMaxClients(); i++)
	{
		BasePlayer* iPlayer = (BasePlayer*)g_EntityList->GetClientEntity(i);

		if (!iPlayer)
			continue;

		if (iPlayer == localPlayer)
			continue;

		if (!iPlayer->isAlive())
			continue;

		if (iPlayer->isDormant())
			continue;

		if (iPlayer->m_iTeamNum() == localPlayer->m_iTeamNum() && !options::aimbot::friendlyFire)
			continue;

		Vector eVecTarget = iPlayer->GetHitboxPos(options::aimbot::bone);
		Vector pVecTarget = localPlayer->GetEyePos();

		QAngle viewAngles;
		g_EngineClient->getViewAngles(viewAngles);

		float fov = Math::GetFov(viewAngles, Math::CalcAngle(eVecTarget, pVecTarget));

		if (!localPlayer->CanSeePlayer(iPlayer, options::aimbot::bone))
			continue;

		if (fov < bestFov)
		{
			bestFov = fov;
			closestEnemy = iPlayer;
		}
	}

	return closestEnemy;
}

QAngle aimbot::smooth(QAngle angle)
{
	QAngle viewAngles;
	g_EngineClient->getViewAngles(viewAngles);
	QAngle delta = angle - viewAngles;
	Math::NormalizeAngles(delta);
	QAngle toChange;

	float smoothValue = powf(options::aimbot::smoothing, 0.1); //Makes smoothing more useable shifts lower values closer to one

	float coeff = (1.0f - smoothValue) / delta.Length() * 4.f;

	coeff = powf(coeff, 2.f) * 10.f;

	coeff = min(1.f, coeff);
	toChange = delta * coeff;

	angle = viewAngles + toChange;

	return angle;
}

QAngle aimbot::rcs(QAngle angle)
{
	BasePlayer* localplayer = (BasePlayer*)g_EntityList->GetClientEntity(g_EngineClient->getLocalPlayer());
	QAngle CurrentPunch = localplayer->m_aimPunchAngle();

	angle.pitch -= CurrentPunch.pitch * options::aimbot::rcs;
	angle.yaw -= CurrentPunch.yaw * options::aimbot::rcs;

	return angle;
}

namespace aimbot
{
	void createMove(CUserCmd * cmd)
	{
		if (!options::aimbot::enabled)
		{
			return;
		}

		if (!(cmd->buttons & IN_ATTACK))
			return;

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
			Vector eVecTarget;

			if (options::aimbot::closestBoneEnabled)
			{
				eVecTarget = getClosestSpot(localPlayer, Enemy);
			}
			else
			{
				eVecTarget = Enemy->GetHitboxPos(options::aimbot::bone);
			}
			
			Vector pVecTarget = localPlayer->GetEyePos();


			QAngle angle;
			angle = Math::CalcAngle(eVecTarget, pVecTarget);

			angle = rcs(angle);
			angle = smooth(angle);

			Math::NormalizeAngles(angle);
			Math::ClampAngles(angle);

			cmd->viewangles = angle;
			g_EngineClient->setViewAngles(cmd->viewangles);
		}
	}
}
