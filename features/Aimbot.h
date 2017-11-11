#pragma once

#include "../SDK/Utils.h"
#include "../Math.h"

//Include Structures
#include "../SDK/Structures/QAngle.h"
#include "../SDK/Structures/Vector.h"
#include "../SDK/Classes/BasePlayer.h"
#include "../SDK/Classes/BaseWeapon.h"
#include "../SDK/Structures/CUserCmd.h"
#include "./Options.h"

//Include Interfaces
#include "../SDK/Interfaces/Engine.h"
#include "../SDK/Interfaces/ClientDll.h"


namespace aimbot
{
	void createMove(CUserCmd* cmd);
	QAngle smooth(QAngle angle);
	QAngle rcs(QAngle angle);
}