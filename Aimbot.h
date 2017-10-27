#pragma once

#include "Utils.h"

#include "SDK.h"

//Include Structures
#include "QAngle.h"
#include "Vector.h"
#include "BasePlayer.h"
#include "BaseWeapon.h"

//Include Interfaces
#include "Engine.h"

class CUserCmd;

namespace aimbot
{
	void createMove(CUserCmd* cmd);
}