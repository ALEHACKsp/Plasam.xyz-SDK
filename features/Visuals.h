#pragma once

#include "Options.h"

class BasePlayer;
class BaseEntity;
class Color;
class ClientClass;

namespace Visuals
{
	namespace Player
	{
		bool Begin(BaseEntity* pl, BasePlayer* localPlayer);

		void RenderBox();
	}
	namespace Misc
	{
		void DrawFovCrosshair(BasePlayer* localPlayer);
	}

	bool CreateFonts();
}