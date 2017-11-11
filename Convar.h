#pragma once

#include "Color.h"
#include "Utils.h"

class ConVar
{
public:
	void SetValue(float value)
	{
		typedef void(__thiscall* OriginalFn)(void*, float);
		return utils::emulate< OriginalFn >(this, 15)(this, value);
	}

	char pad_0x0000[0x4]; //0x0000
	ConVar* pNext; //0x0004 
	__int32 bRegistered; //0x0008 
	char* pszName; //0x000C 
	char* pszHelpString; //0x0010 
	__int32 nFlags; //0x0014 
	char pad_0x0018[0x4]; //0x0018
	ConVar* pParent; //0x001C 
	char* pszDefaultValue; //0x0020 
	char* strString; //0x0024 
	__int32 StringLength; //0x0028 
	float fValue; //0x002C 
	__int32 nValue; //0x0030 
	__int32 bHasMin; //0x0034 
	float fMinVal; //0x0038 
	__int32 bHasMax; //0x003C 
	float fMaxVal; //0x0040 
	void* fnChangeCallback; //0x0044 
};//Size=0x0048

  /* i was intoxicated while making this class, do not judge */
class ICVar
{
private:
	virtual void pvoid0() = 0;
	virtual void pvoid1() = 0;
	virtual void pvoid2() = 0;
	virtual void pvoid3() = 0;
	virtual void pvoid4() = 0;
	virtual void pvoid5() = 0;
	virtual void pvoid6() = 0;
	virtual void pvoid7() = 0;
	virtual void pvoid8() = 0;
	virtual void pvoid9() = 0;
	virtual void pvoid10() = 0;
	virtual void pvoid11() = 0;
	virtual void pvoid12() = 0;
	virtual void pvoid13() = 0;
	virtual void pvoid14() = 0;
	virtual void pvoid15() = 0;
public:
	virtual ConVar*                    FindVar(const char *var_name) = 0; // 16
private:
	virtual void pvoid17() = 0;
	virtual void pvoid18() = 0;
	virtual void pvoid19() = 0;
	virtual void pvoid20() = 0;
	virtual void pvoid21() = 0;
	virtual void pvoid22() = 0;
	virtual void pvoid23() = 0;
	virtual void pvoid24() = 0;
public:
	virtual void                       ConsoleColorPrintf(const Color clr, const char *pFormat, ...) const = 0; // 25
}; extern ICVar* g_Cvar;