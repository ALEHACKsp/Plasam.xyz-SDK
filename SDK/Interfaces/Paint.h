#pragma once

#include <Windows.h>
#include "../Utils.h"
#include "../Structures/Color.h"

enum FontFeature
{
	FONT_FEATURE_ANTIALIASED_FONTS = 1,
	FONT_FEATURE_DROPSHADOW_FONTS = 2,
	FONT_FEATURE_OUTLINE_FONTS = 6,
};

enum FontDrawType
{
	FONT_DRAW_DEFAULT = 0,
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,
	FONT_DRAW_TYPE_COUNT = 2,
};

enum FontFlags
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,
};

typedef DWORD HFont;
typedef unsigned int VPANEL;

class IPanel
{
public:
	const char *GetName(unsigned int vguiPanel)
	{
		typedef const char *(__thiscall* tGetName)(void*, unsigned int);
		return utils::emulate<tGetName>(this, 36)(this, vguiPanel);
	}

	const char *GetClassName(unsigned int vguiPanel)
	{
		typedef const char *(__thiscall* tGetClassName)(void*, unsigned int);
		return utils::emulate<tGetClassName>(this, 37)(this, vguiPanel);
	}
};


class ISurface
{
public:
	void DrawSetColor(Color c)
	{
		typedef void(__thiscall* _DrawSetColor)(void*, Color);
		return utils::emulate<_DrawSetColor>(this, 14)(this, c);
	}

	void DrawRect(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* OriginalFn)(void*, int, int, int, int);
		return utils::emulate< OriginalFn >(this, 16)(this, x0, y0, x1, y1);
	}

	void DrawLine(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* OriginalFn)(void*, int, int, int, int);
		return utils::emulate< OriginalFn >(this, 19)(this, x0, y0, x1, y1);
	}

	void DrawOutlinedRect(int X, int Y, int W, int H)
	{
		typedef void(__thiscall* _DrawOutlinedRect)(void*, int, int, int, int);
		return utils::emulate<_DrawOutlinedRect>(this, 18)(this, X, Y, W, H);
	}

	void DrawOutlinedCircle(int x, int y, int radius, int segments)
	{
		typedef void(__thiscall* _DrawOutlinedCircle)(void*, int, int, int, int);
		return utils::emulate<_DrawOutlinedCircle>(this, 103)(this, x, y, radius, segments);
	}

	void DrawSetTextFont(int Font)
	{
		typedef void(__thiscall* _DrawSetTextFont)(void*, int);
		return utils::emulate<_DrawSetTextFont>(this, 23)(this, Font);
	}

	void DrawSetTextColor(Color c)
	{
		typedef void(__thiscall* _DrawSetTextColor)(void*, Color);
		return utils::emulate<_DrawSetTextColor>(this, 24)(this, c);
	}

	void DrawSetTextPos(int X, int Y)
	{
		typedef void(__thiscall* _DrawSetTextPos)(void*, int, int);
		return utils::emulate<_DrawSetTextPos>(this, 26)(this, X, Y);
	}

	void DrawPrintText(wchar_t* _Input, int Length, int Type = 0)
	{
		typedef void(__thiscall* _DrawPrintText)(void*, wchar_t*, int, int);
		return utils::emulate<_DrawPrintText>(this, 28)(this, _Input, Length, Type);
	}

	bool GetTextSize(int Font, const wchar_t* _Input, int& Wide, int& Tall)
	{
		typedef bool(__thiscall* _GetTextSize)(void*, int, const wchar_t*, int&, int&);
		return utils::emulate< _GetTextSize >(this, 79)(this, Font, _Input, Wide, Tall);
	}

	HFont Create_Font()
	{
		typedef HFont(__thiscall* OriginalFn)(void*);
		return utils::emulate< OriginalFn >(this, 71)(this);
	}

	bool SetFontGlyphSet(HFont font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int nRangeMin = 0, int nRangeMax = 0)
	{
		
		typedef bool(__thiscall* OriginalFn)(void*, HFont, const char*, int, int, int, int, int, int, int);
		utils::log(" -- Resetting font '%s' at index 0x%x.", windowsFontName, font);
		return utils::emulate< OriginalFn >(this, 72)(this, font, windowsFontName, tall, weight, blur, scanlines, flags, nRangeMin, nRangeMax);
	}
}; 

extern ISurface*	g_VGUISurface;
extern IPanel*		g_VGuiPanel;