#include "misc.h"

//Resolve externs
bool options::misc::revealRanks = false;

namespace misc
{
	void rankReveal()
	{
		using ServerRankRevealAll = char(__cdecl*)(int*);

		static auto fnServerRankRevealAll = utils::findPattern("client.dll", "55 8B EC 8B 0D ? ? ? ? 68");

		int v[3] = { 0,0,0 };

		reinterpret_cast<ServerRankRevealAll>(fnServerRankRevealAll)(v);
	}
}