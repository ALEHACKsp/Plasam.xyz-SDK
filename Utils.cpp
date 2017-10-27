#include "Utils.h"

/* standard libraries */

#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

namespace utils
{
	void log(const char* fmt, ...)
	{
		if (!fmt) return;

		va_list va_alist;
		char logBuf[256] = { 0 };

		va_start(va_alist, fmt);
		_vsnprintf(logBuf + strlen(logBuf), sizeof(logBuf) - strlen(logBuf), fmt, va_alist);
		va_end(va_alist);

		if (logBuf[0] != '\0')
		{
			SYSTEMTIME time;
			GetLocalTime(&time);
			printf("[%02d:%02d:%02d]", time.wHour, time.wMinute, time.wSecond);
			printf(": %s\n", logBuf);
		}

	}
	DWORD findPattern(std::string moduleName, std::string pattern) // learn_more
	{
		const char* pat = pattern.c_str();
		DWORD firstMatch = 0;
		DWORD rangeStart = (DWORD)GetModuleHandleA(moduleName.c_str());
		MODULEINFO miModInfo;
		K32GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
		DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;
		for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++)
		{
			if (!*pat)
			{
				log(" -- Found pattern '%s' in 's'", pattern, moduleName.c_str());
				return firstMatch;
			}

			if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat))
			{
				if (!firstMatch)
					firstMatch = pCur;

				if (!pat[2])
				{
					log(" -- Found pattern '%s' in '%s'", pattern.c_str(), moduleName.c_str());
					return firstMatch;
				}

				if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
					pat += 3;

				else
					pat += 2; //one ?
			}
			else
			{
				pat = pattern.c_str();
				firstMatch = 0;
			}
		}

		log(" -- The pattern '%s' in '%s' returned no valid result.", pattern, moduleName.c_str());
		return NULL;
	}
};