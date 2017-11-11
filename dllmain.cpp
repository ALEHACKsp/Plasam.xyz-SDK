#define _CRT_SECURE_NO_WARNINGS
#define HWID "71d9f4b05c2b1242b95930f43d9b10e9"

#include "hwid.h"
#include "SDK.h"

HWND windowHandle = NULL;

void cheatThread(LPVOID base)
{
	//if (HWID != hwid::get())
	//	return;

	sdk::initialize();
	NetvarSys::Get().Initialize();
	InputSys::Get().Initialize();
	Menu::Get().setup();

	HookManager::Initialize();
	
	//Setup menu key
	InputSys::Get().RegisterHotkey(VK_DELETE, [base]() {
		Menu::Get().toggle();
	});
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
			DisableThreadLibraryCalls(hModule);

			// Setup console
			#ifdef _DEBUG
			AllocConsole();
			freopen("CONIN$", "r", stdin);
			freopen("CONOUT$", "w", stdout);
			freopen("CONOUT$", "w", stderr);

			SetConsoleTitleA(CHEAT_NAME);
			#endif

			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)cheatThread, hModule, 0, 0);
		}break;
	}
	return TRUE;
}