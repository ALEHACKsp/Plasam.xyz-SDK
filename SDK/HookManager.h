#pragma once

#include "SDK.h"

#include "VMT.h"
#include "./Interfaces/ClientDll.h"
#include "./Interfaces/Paint.h"
#include "../features/Hacks.h"

class CUserCmd;
class ClientMode;

struct IDirect3DDevice9;

using EndScene_t = long(__stdcall *)(IDirect3DDevice9*);
using PaintTraverse_t = void(__thiscall*)(IPanel*, VPANEL, bool, bool);

namespace HookManager
{
	void Initialize();
	bool __stdcall CreateMove(float flInputSampleTime, CUserCmd* cmd);
	bool __stdcall EndScene(IDirect3DDevice9* device);
	void __stdcall PaintTraverse(VPANEL panel, bool forceRepaint, bool allowForce);
};
