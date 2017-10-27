#pragma once

#include <Windows.h>

#include <iostream>
#include <string>

#include "Utils.h"

#include "Vector.h"
#include "QAngle.h"
#include "CUserCmd.h"
#include "VMT.h"

#include "HookManager.h"
#include "NetvarManager.h"

#define CHEAT_NAME "Plasam.xyz"

struct IDirect3DDevice9;

extern IDirect3DDevice9*     g_D3DDevice9;

namespace sdk
{
	void initialize();
}