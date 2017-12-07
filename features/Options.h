#pragma once

namespace options
{
	namespace menu
	{
		extern int		tab;
	}
	namespace aimbot
	{
		extern bool		enabled;
		extern bool		closestBoneEnabled;
		extern bool		friendlyFire;
		extern int		bone;
		extern float	fov;
		extern float	smoothing;
		extern float	rcs;
		extern float	killTimeout;
	}
	namespace triggerbot
	{
		extern bool		enabled;
	}
	namespace visuals
	{
		extern bool		enabled;

		namespace player
		{
			extern bool		renderEnemies;
			extern bool		renderAllies;
		}
		namespace misc
		{
			extern bool		FovCircle;
		}
	}
	namespace misc
	{
		extern bool		revealRanks;
	}
}