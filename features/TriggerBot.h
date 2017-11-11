#pragma once

#include "../SDK/Classes/BasePlayer.h"
#include "../SDK/Classes/BaseWeapon.h"
#include "../SDK/Structures/CUserCmd.h"
#include "../SDK/Interfaces/Engine.h"
#include "../SDK/Interfaces/ClientDll.h"
#include "../SDK/Structures/Vector.h"
#include "../SDK/Structures/QAngle.h"
#include "../Math.h"

namespace TriggerBot
{
	void CreateMove(CUserCmd* cmd);
}