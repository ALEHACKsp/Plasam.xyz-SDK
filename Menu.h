#pragma once

#include "input.h"
#include "Color.h"
#include "Options.h"

#include "Convar.h"

#include "imgui\imgui.h"
#include "ImGUI\Directx9\imgui_impl_dx9.h"
#include "imgui\imgui_internal.h"

class Menu
	: public Singleton<Menu>
{
public:
	void			setup();
	void			render();
	void			toggle();

	bool			IsVisible() const { return _visible; }

private:
	ImGuiStyle      _style;
	bool			_visible;

	void			createStyle();
};