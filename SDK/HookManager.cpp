#include "HookManager.h"

namespace HookManager
{
	vfunc_hook hlclient_hook;
	vfunc_hook direct3d_hook;
	vfunc_hook vguipanel_hook;

	void Initialize()
	{

		hlclient_hook.setup(g_ClientMode);
		direct3d_hook.setup(g_D3DDevice9);
		vguipanel_hook.setup(g_VGuiPanel);

		direct3d_hook.hook_index(42, HookManager::EndScene);
		hlclient_hook.hook_index(24, HookManager::CreateMove);
		vguipanel_hook.hook_index(41, HookManager::PaintTraverse);

		Visuals::CreateFonts();
	}
	bool __stdcall CreateMove(float flInputSampleTime, CUserCmd* cmd)
	{
		aimbot::createMove(cmd);
		
		TriggerBot::CreateMove(cmd);

		return 0;
	};

	bool __stdcall EndScene(IDirect3DDevice9* device)
	{

		auto oEndScene = direct3d_hook.get_original<EndScene_t>(42);

		Menu::Get().render();

		if (InputSys::Get().IsKeyDown(VK_TAB) && options::misc::revealRanks)
		{
			misc::rankReveal();
		}

		return oEndScene(device);
	}

	void __stdcall PaintTraverse(VPANEL panel, bool forceRepaint, bool allowForce)
	{
		static auto panelId = VPANEL{ 0 };
		static auto oPaintTraverse = vguipanel_hook.get_original<PaintTraverse_t>(41);

		oPaintTraverse(g_VGuiPanel, panel, forceRepaint, allowForce);

		if(options::visuals::enabled)
		{
			if (!panelId) {
				const auto panelName = g_VGuiPanel->GetName(panel);
				if (!strcmp(panelName, "FocusOverlayPanel")) {
					panelId = panel;
				}
			}
			else if (panelId == panel) {
				BasePlayer* localPlayer = (BasePlayer*)g_EntityList->GetClientEntity(g_EngineClient->getLocalPlayer());
				Visuals::Misc::DrawFovCrosshair(localPlayer);
				for (auto i = 1; i <= g_EntityList->GetHighestEntityIndex(); ++i) {
					BaseEntity* iEnt = g_EntityList->GetClientEntity(i);

					if (!iEnt)
						continue;

					if (iEnt->isDormant())
						continue;

					if (iEnt->isPlayer())
					{
						if (iEnt == localPlayer)
							continue;

						if (iEnt->isAlive()) {
							// Begin will calculate player screen coordinate, bounding box, etc
							// If it returns false it means the player is not inside the screen
							// or is an ally (and team check is enabled)
							if (Visuals::Player::Begin(iEnt,localPlayer)) {
								Visuals::Player::RenderBox();
							}
						}
					}
				}
			}
		}
	}
};