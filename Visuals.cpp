#include "visuals.h"

#include "Paint.h"
#include "math.h"
#include "utils.h"
#include "Engine.h"
#include "Color.h"

#include "BasePlayer.h"

HFont esp_font;
HFont defuse_font;
HFont dropped_weapons_font;

//Resolve Externs
bool options::visuals::enabled					= false;
bool options::visuals::player::renderAllies		= false;
bool options::visuals::player::renderEnemies	= true;
bool options::visuals::misc::FovCircle			= false;

struct
{
	BaseEntity*		pl;
	bool			is_enemy;
	bool			is_visible;
	Color			clr;
	Vector			head_pos;
	Vector			feet_pos;
	RECT			bbox;
} esp_ctx;

RECT GetBBox(BaseEntity* ent)
{
	RECT rect{};
	auto collideable = ent->GetCollideable();

	if (!collideable)
		return rect;

	auto min = collideable->GetMins();
	auto max = collideable->GetMaxs();

	const matrix3x4_t& trans = ent->m_rgflCoordinateFrame();

	Vector points[] = {
		Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z)
	};

	Vector pointsTransformed[8];
	for (int i = 0; i < 8; i++) {
		Math::VectorTransform(points[i], trans, pointsTransformed[i]);
	}

	Vector pos = ent->m_vecOrigin();
	Vector screen_points[8] = {};

	for (int i = 0; i < 8; i++) {
		if (!Math::WorldToScreen(pointsTransformed[i], screen_points[i]))
			return rect;
	}

	auto left = screen_points[0].x;
	auto top = screen_points[0].y;
	auto right = screen_points[0].x;
	auto bottom = screen_points[0].y;

	for (int i = 1; i < 8; i++) {
		if (left > screen_points[i].x)
			left = screen_points[i].x;
		if (top < screen_points[i].y)
			top = screen_points[i].y;
		if (right < screen_points[i].x)
			right = screen_points[i].x;
		if (bottom > screen_points[i].y)
			bottom = screen_points[i].y;
	}
	return RECT{ (long)left, (long)top, (long)right, (long)bottom };
}

bool Visuals::CreateFonts()
{
	esp_font				= g_VGUISurface->Create_Font();
	defuse_font				= g_VGUISurface->Create_Font();
	dropped_weapons_font	= g_VGUISurface->Create_Font();

	g_VGUISurface->SetFontGlyphSet(esp_font,				"Arial",	11, 700, 0, 0, FONTFLAG_DROPSHADOW);
	g_VGUISurface->SetFontGlyphSet(defuse_font,				"Arial",	15, 700, 0, 0, FONTFLAG_DROPSHADOW);
	g_VGUISurface->SetFontGlyphSet(dropped_weapons_font,	"Arial",	10, 700, 0, 0, FONTFLAG_DROPSHADOW);

	return true;
}

bool Visuals::Player::Begin(BaseEntity* iPlayer, BasePlayer* localPlayer)
{
	esp_ctx.pl = iPlayer;
	
	if (localPlayer->m_iTeamNum() == iPlayer->m_iTeamNum())
	{
		//Ally
		esp_ctx.is_enemy = false;
		esp_ctx.clr = Color(0, 255, 0);
	}
	else
	{
		//Enemy
		esp_ctx.is_enemy = true;
		esp_ctx.clr = Color(255, 0, 0);
	}
	

	auto head = iPlayer->GetHitboxPos(HITBOX_HEAD);
	auto origin = iPlayer->m_vecOrigin();

	head.z += 15;

	if (!Math::WorldToScreen(head, esp_ctx.head_pos) ||
		!Math::WorldToScreen(origin, esp_ctx.feet_pos))
		return false;

	auto h = fabs(esp_ctx.head_pos.y - esp_ctx.feet_pos.y);
	auto w = h / 1.65f;

	esp_ctx.bbox.left		= static_cast<long>(esp_ctx.feet_pos.x - w * 0.5f);
	esp_ctx.bbox.right		= static_cast<long>(esp_ctx.bbox.left + w);
	esp_ctx.bbox.bottom		= static_cast<long>(esp_ctx.feet_pos.y);
	esp_ctx.bbox.top		= static_cast<long>(esp_ctx.head_pos.y);

	return true;
}

void Visuals::Player::RenderBox()
{
	if ((esp_ctx.is_enemy && options::visuals::player::renderEnemies) || (!esp_ctx.is_enemy && options::visuals::player::renderAllies))
	{
		//Coloured Box
		g_VGUISurface->DrawSetColor(esp_ctx.clr);
		g_VGUISurface->DrawOutlinedRect(esp_ctx.bbox.left, esp_ctx.bbox.top, esp_ctx.bbox.right, esp_ctx.bbox.bottom);

		//Draw Shadowy thing
		g_VGUISurface->DrawSetColor(Color::Black);
		g_VGUISurface->DrawOutlinedRect(esp_ctx.bbox.left - 1, esp_ctx.bbox.top - 1, esp_ctx.bbox.right + 1, esp_ctx.bbox.bottom + 1);
		g_VGUISurface->DrawOutlinedRect(esp_ctx.bbox.left + 1, esp_ctx.bbox.top + 1, esp_ctx.bbox.right - 1, esp_ctx.bbox.bottom - 1);
	}
}

void Visuals::Misc::DrawFovCrosshair(BasePlayer* localPlayer)
{
	if (!options::visuals::misc::FovCircle)
		return;

	if (!localPlayer->isAlive())
		return;

	int width, height;
	g_EngineClient->GetScreenSize(width, height);

	float radius;

	float aimbotFov = options::aimbot::fov;
	float fov = 106;
	radius = tanf(DEG2RAD(aimbotFov) / 2) / tanf(DEG2RAD(fov) / 2) * width;

	g_VGUISurface->DrawSetColor(Color::Blue);
	g_VGUISurface->DrawOutlinedCircle(width / 2, height / 2, radius, 30);
}