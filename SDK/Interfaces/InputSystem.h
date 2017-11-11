#pragma once

#include "../Utils.h"

enum ButtonCode_t;

class InputSystem
{
public:
	void EnableInput(bool bEnable)
	{
		typedef void(__thiscall* OriginalFn)(void*, bool);
		return utils::emulate< OriginalFn >(this, 11)(this, bEnable);
	}
	bool IsButtonDown(ButtonCode_t code)
	{
		typedef bool(__thiscall* OriginalFn)(void*, ButtonCode_t);
		return utils::emulate< OriginalFn >(this, 15)(this, code);
	}
	void ResetInputState()
	{
		typedef void(__thiscall* OriginalFn)(void*);
		return utils::emulate< OriginalFn >(this, 39)(this);
	}
	char* ButtonCodeToString(ButtonCode_t code)
	{
		typedef char*(__thiscall* OriginalFn)(void*, ButtonCode_t);
		return utils::emulate< OriginalFn >(this, 40)(this, code);
	}
	ButtonCode_t VirtualKeyToButtonCode(int nVirtualKey)
	{
		typedef ButtonCode_t(__thiscall* OriginalFn)(void*, int);
		return utils::emulate< OriginalFn >(this, 44)(this, nVirtualKey);
	}
	int ButtonCodeToVirtualKey(ButtonCode_t code)
	{
		typedef int(__thiscall* OriginalFn)(void*, ButtonCode_t);
		return utils::emulate< OriginalFn >(this, 45)(this, code);
	}
	void GetCursorPosition(int* m_pX, int* m_pY)
	{
		typedef void(__thiscall* OriginalFn)(void*, int*, int*);
		return utils::emulate< OriginalFn >(this, 56)(this, m_pX, m_pY);
	}
};