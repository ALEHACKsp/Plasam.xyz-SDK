#pragma once

#include "BaseEntity.h"

class BaseWeapon : public BaseEntity
{
public:
	NETVAR(float_t, m_flNextPrimaryAttack, "DT_BaseCombatWeapon", "m_flNextPrimaryAttack");
};