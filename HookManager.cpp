#include "HookManager.h"

namespace HookManager
{
	vfunc_hook hlclient_hook;
	vfunc_hook direct3d_hook;

	void Initialize()
	{

		hlclient_hook.setup(g_ClientMode);
		direct3d_hook.setup(g_D3DDevice9);

		//direct3d_hook.hook_index(42, hkEndScene);
		hlclient_hook.hook_index(24, (CreateMoveFn)HookManager::CreateMove);
	}
	bool __stdcall CreateMove(float flInputSampleTime, CUserCmd* cmd)
	{

		aimbot::createMove(cmd);

		return 0;
	};
};