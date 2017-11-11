#pragma once

//Include Structures
#include "../SDK/Structures/Vector.h"
#include "../SDK/Structures/QAngle.h"
#include "../SDK/Structures/CUserCmd.h"

//Include Classes
#include "../SDK/Classes/BasePlayer.h"
#include "../SDK/Classes/BaseWeapon.h"

//Include Interfaces
#include "../SDK/Interfaces/Engine.h"
#include "../SDK/Interfaces/ClientDll.h"
#include "../SDK/Interfaces/InputSystem.h"

//Include Functions
#include "./Options.h"
#include "../Math.h"
#include "../input.h"

namespace TriggerBot
{
	void CreateMove(CUserCmd* cmd);
}