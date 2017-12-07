#pragma once

#include "BaseEntity.h"

class BaseWeapon;

class BasePlayer : public BaseEntity
{
public:

	//Netvars

	NETVAR(int32_t	, m_iHealth			, "DT_BasePlayer"	, "m_iHealth"			);
	NETVAR(QAngle	, m_aimPunchAngle	, "DT_BasePlayer"	, "m_aimPunchAngle"		);
	NETVAR(Vector	, m_vecViewOffset	, "DT_BasePlayer"	, "m_vecViewOffset[0]"	);
	NETVAR(CHandle<BaseWeapon>, m_hActiveWeapon, "DT_BaseCombatCharacter", "m_hActiveWeapon");
	//NETVAR(Handle<BaseWeapon>, m_hActiveWeapon, "DT_BaseCombatCharacter", "m_hActiveWeapon");

	//Functions

	Vector	GetEyePos();
	bool	CanSeePlayer(BasePlayer* player, int hitbox);
};