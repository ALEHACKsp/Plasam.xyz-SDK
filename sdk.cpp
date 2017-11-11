#include "SDK.h"

#include "Engine.h"
#include "ClientDll.h"
#include "Model.h"
#include "Convar.h"
#include "Paint.h"

//Resolve externs

EngineClient	* g_EngineClient	= nullptr;
IEngineTrace	* g_EngineTrace		= nullptr;
EntityList		* g_EntityList		= nullptr;
ClientDLL		* g_Client			= nullptr;
ClientMode		* g_ClientMode		= nullptr;
IVModelInfo		* g_ModelInfo		= nullptr;
IDirect3DDevice9* g_D3DDevice9		= nullptr;
CGlobalVarsBase * g_GlobalVars		= nullptr;
ICVar			* g_Cvar			= nullptr;
IPanel			* g_VGuiPanel		= nullptr;
ISurface		* g_VGUISurface		= nullptr;

template< typename T >
T* SeekInterface(char* mod, char* interf, bool seek = true)
{
	typedef T* (*CreateInterfaceFn)(const char* szName, int iReturn);
	CreateInterfaceFn CreateInterface = (CreateInterfaceFn)GetProcAddress(GetModuleHandleA(mod), ("CreateInterface"));

	std::string sInterface, sInterfaceVersion = "0";

	if (seek)
	{
		for (auto i = 0; i <= 99; i++)
		{
			sInterface = interf;
			sInterface += sInterfaceVersion;
			sInterface += std::to_string(i);

			T* funcPtr = CreateInterface(sInterface.c_str(), NULL);

			if (funcPtr != NULL)
			{
				utils::log(" -- Found interface pointer for '%s' ==> 0x%x", sInterface.c_str(), funcPtr);
				return funcPtr;
			}

			if (i == 99 && sInterfaceVersion == "0")
			{
				sInterfaceVersion = "00";
				i = 0;
			}
			else if (i == 99 && sInterfaceVersion == "00")
			{
				utils::log(" -- Faulty interface pointer for '%s' ==> 0x%x", interf, funcPtr);
				return nullptr;
			}
		}
	}
	else
	{
		T* ptr = CreateInterface(interf, 0);

		if (ptr)
		{
			utils::log(" -- Found interface pointer for '%s' ==> 0x%x", interf, ptr);
			return ptr;
		}
		else
		{
			utils::log(" -- Faulty interface pointer for '%s' ==> 0x%x", interf, ptr);
			return nullptr;
		}
	}

	return nullptr;
}

namespace sdk
{

	void initialize()
	{
		utils::log(" ===================================================================================");
		utils::log(" Initializing %s, built on %s at %s.", CHEAT_NAME, __DATE__, __TIME__);

		g_Client		= SeekInterface<ClientDLL>		("client.dll",	"VClient");
		g_EngineClient	= SeekInterface<EngineClient>	("engine.dll",	"VEngineClient");
		g_EngineTrace	= SeekInterface<IEngineTrace>	("engine.dll",	"EngineTraceClient");
		g_EntityList	= SeekInterface<EntityList>		("client.dll",	"VClientEntityList");
		g_ModelInfo		= SeekInterface<IVModelInfo>	("engine.dll",	"VModelInfoClient");
		g_Cvar			= SeekInterface<ICVar>			("vstdlib.dll", "VEngineCvar");
		g_VGUISurface	= SeekInterface<ISurface>		("vguimatsurface.dll", "VGUI_Surface");
		g_VGuiPanel		= SeekInterface<IPanel>			("vgui2.dll", "VGUI_Panel");

		g_D3DDevice9	= **(IDirect3DDevice9***)(utils::findPattern("shaderapidx9.dll", "A1 ? ? ? ? 50 8B 08 FF 51 0C") + 1);

		g_GlobalVars	= *(CGlobalVarsBase**)(((*(PDWORD*)g_Client)[0]) + 0x1B);
		g_GlobalVars	= (CGlobalVarsBase*)*(PDWORD)g_GlobalVars;

		auto uAddress	= *(DWORD*)(utils::findPattern("Client.dll", "8B 0D ? ? ? ? 8B 01 5D FF") + 2);
		g_ClientMode	= *(ClientMode**)(uAddress);

	}
}