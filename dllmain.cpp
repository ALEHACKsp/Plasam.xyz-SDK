#include "SDK.h"

void cheatThread()
{
	sdk::initialize();
	HookManager::Initialize();
	NetvarSys::Get().Initialize();
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		{
			// Setup console
			AllocConsole();
			freopen("CONIN$", "r", stdin);
			freopen("CONOUT$", "w", stdout);
			freopen("CONOUT$", "w", stderr);

			SetConsoleTitleA(CHEAT_NAME);

			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)cheatThread, 0, 0, 0);
		}break;
	}
	return TRUE;
}