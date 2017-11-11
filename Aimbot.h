#pragma once

#include "Utils.h"

//Include Structures
#include "QAngle.h"
#include "Vector.h"
#include "BasePlayer.h"
#include "BaseWeapon.h"
#include "Options.h"

//Include Interfaces
#include "Engine.h"
#include "CUserCmd.h"

namespace aimbot
{
	void createMove(CUserCmd* cmd);
	QAngle smooth(QAngle angle);
	QAngle rcs(QAngle angle);
}