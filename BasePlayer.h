#pragma once

#include "BaseEntity.h"

class BaseWeapon;

class BasePlayer : public BaseEntity
{
public:

	//Netvars

	NETVAR(int32_t	, m_iHealth			, "DT_BasePlayer"	, "m_iHealth"			)
	NETVAR(int32_t	, m_iTeamNum		, "DT_BaseEntity"	, "m_iTeamNum"			)
	NETVAR(int32_t	, m_lifeState		, "DT_BasePlayer"	, "m_lifeState"			)
	NETVAR(Vector	, m_vecViewOffset	, "DT_BasePlayer"	, "m_vecViewOffset[0]"	);
	//NETVAR(Handle<BaseWeapon>, m_hActiveWeapon, "DT_BaseCombatCharacter", "m_hActiveWeapon");

	//Functions

	Vector	getEyePos();
	bool	isAlive();
	Vector	GetHitboxPos(int hitbox_id);
	Vector	GetEyePos();
	bool	CanSeePlayer(BasePlayer* player, int hitbox);
};