#pragma once

#include "VMT.h"
#include "ClientDll.h"
#include "Hacks.h"

class CUserCmd;
class ClientMode;

using CreateMoveFn = void(__thiscall*)(ClientDLL*, int, float, bool);
extern CreateMoveFn oCreateMove;

namespace HookManager
{
	void Initialize();
	bool __stdcall CreateMove(float flInputSampleTime, CUserCmd* cmd);
};
