#pragma once

#include <Windows.h>
#include <Psapi.h>

#include <iostream>
#include <string>

namespace utils
{
	void log(const char* fmt, ...);
	DWORD findPattern(std::string moduleName, std::string pattern);

	template<typename FuncType>
	static FuncType emulate(void* ppClass, int index)
	{
		int* pVTable = *(int**)ppClass;
		int dwAddress = pVTable[index];
		return (FuncType)(dwAddress);
	}
}