#include "Menu.h"

//Resolve externs
int options::menu::tab		= 0;

static ConVar* cl_mouseenable = nullptr;

const char* targets[] = {
	"HEAD",
	"NECK",
	"LOWER NECK",
	"HITBOX PELVIS",
	"HITBOX STOMACH",
	"LOWER CHEST",
	"CHEST",
	"UPPER CHEST",
	"RIGHT THIGH",
	"LEFT THIGH",
	"RIGHT CALF",
	"LEFT CALF",
	"RIGHT FOOT",
	"LEFT FOOT",
	"RIGHT HAND",
	"LEFT HAND",
	"RIGHT UPPER ARM",
	"RIGHT FOREARM",
	"LEFT UPPER ARM",
	"LEFT FOREARM"
};

std::string currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%d.%m.%Y %X", &tstruct);

	return buf;
}

void aimTab()
{
	ImGui::Checkbox("Aimbot", &options::aimbot::enabled);

	ImGui::Separator();

	ImGui::PushItemWidth(180);

	ImGui::Combo("##AIMTARGET", &options::aimbot::bone, targets, IM_ARRAYSIZE(targets));

	ImGui::SliderFloat("FOV:      ", &options::aimbot::fov, 0, 20);
	ImGui::SliderFloat("Smoothing:", &options::aimbot::smoothing, 0, 1);
	ImGui::SliderFloat("RCS:	  ", &options::aimbot::rcs, 0, 2);
	ImGui::SliderFloat("Kill Timeout:", &options::aimbot::killTimeout, 0, 1, "%.3fs");

	ImGui::Checkbox("Friendly Fire", &options::aimbot::friendlyFire);

	ImGui::PopItemWidth();
}

void visualsTab()
{
	ImGui::Checkbox("ESP", &options::visuals::enabled);

	ImGui::Separator();

	ImGui::Checkbox("Render Allies", &options::visuals::player::renderAllies);
	ImGui::Checkbox("Render Enemies", &options::visuals::player::renderEnemies);

	ImGui::Separator();

	ImGui::Checkbox("Fov Circle", &options::visuals::misc::FovCircle);
}

void miscTab()
{

	ImGui::Checkbox("Rank reveal", &options::misc::revealRanks);

	ImGui::Separator();

	ImGui::PushItemWidth(180);

	//ImGui::SliderInt("Chance:   ", &options::bhop::chance, 0, 100, "%.0f%%");

	ImGui::PopItemWidth();
}

void Menu::setup()
{
	ImGui_ImplDX9_Init(InputSys::Get().GetMainWindow(),g_D3DDevice9);

	cl_mouseenable = g_Cvar->FindVar("cl_mouseenable");

	createStyle();
	
	return;
}

void Menu::render()
{
	ImGui_ImplDX9_NewFrame();

	ImGui::GetIO().MouseDrawCursor = _visible;

	ImGui::SetNextWindowPos(ImVec2{ 0, 0 }, ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2{ 0, 0 }, ImGuiSetCond_Once);

	if (!_visible)
	{
		//Draw watermark and return
		bool watermark = true;
		ImGui::Begin("##wm", &watermark, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs);
		ImGui::TextColored(Color(255, 255, 0, 255), "Plasam.xyz");
		ImGui::TextColored(Color(0, 255, 0, 255), "By $lack");

		ImGui::End();

		ImGui::Render();

		return;
	}

	int w;
	int h;

	g_EngineClient->GetScreenSize(w, h);

	ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiSetCond_Appearing);

	ImGui::PushStyleColor(ImGuiCol_WindowBg, Color(20, 20, 20, 50));
	ImGui::SetNextWindowSize(ImVec2(w, h), ImGuiSetCond_Once);

	ImGui::Begin("##bg", &_visible, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar);
	{}
	ImGui::End();

	ImGui::PopStyleColor();

	ImGui::PushStyle(_style);

	if (ImGui::Begin("Plasam.xyz",
		&_visible,
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_ShowBorders |
		ImGuiWindowFlags_NoResize)) {

		ImGui::TextColored(Color(255, 255, 0, 255), "Plasam.xyz");
		ImGui::TextColored(Color(0, 255, 0, 255), "By $lack");
		ImGui::TextColored(Color(255, 127, 0, 255), currentDateTime().c_str());

		ImGui::Separator();

		if (ImGui::Button("AIM", ImVec2(128, 42))) options::menu::tab = 0;
		ImGui::SameLine();
		if (ImGui::Button("VISUALS", ImVec2(128, 42))) options::menu::tab = 1;
		ImGui::SameLine();
		if (ImGui::Button("MISC", ImVec2(128, 42))) options::menu::tab = 2;

		ImGui::Separator();

		switch (options::menu::tab)
		{
		case 0:
			aimTab();
			break;
		case 1:
			visualsTab();
			break;
		case 2:
			miscTab();
			break;
		}

	}

	ImGui::PopStyle();

	ImGui::End();

	ImGui::Render();

	return;
}

void Menu::toggle()
{
	_visible = !_visible;
	cl_mouseenable->SetValue(!_visible);
	return;
}

void Menu::createStyle()
{
	_style.Colors[ImGuiCol_Text] = Color(255, 255, 0, 255);

	//Backgrounds
	_style.Colors[ImGuiCol_WindowBg] = Color(0, 0, 0, 255);
	_style.Colors[ImGuiCol_FrameBg] = Color(0, 0, 0, 255);
	_style.Colors[ImGuiCol_ComboBg] = Color(0, 0, 0, 255);
	_style.Colors[ImGuiCol_ScrollbarBg] = Color(0, 0, 0, 255);
	_style.Colors[ImGuiCol_Header] = Color(20, 20, 20);
	_style.Colors[ImGuiCol_HeaderHovered] = Color(48, 48, 48);
	_style.Colors[ImGuiCol_HeaderActive] = Color(0, 0, 0, 255);

	//ScrollBar
	_style.Colors[ImGuiCol_ScrollbarGrab] = Color(255, 255, 0, 255);
	_style.Colors[ImGuiCol_ScrollbarGrabHovered] = Color(220, 220, 0, 255);
	_style.Colors[ImGuiCol_ScrollbarGrabActive] = Color(200, 200, 0, 255);

	_style.Colors[ImGuiCol_Button] = Color(0, 0, 0, 255);
	_style.Colors[ImGuiCol_ButtonHovered] = Color(20, 20, 20, 255);
	_style.Colors[ImGuiCol_ButtonActive] = Color(70, 70, 70, 255);	
}