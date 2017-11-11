#pragma once

#include <iostream>
#include <windows.h>
#include <Tchar.h>
#include <string>
#include <sstream>
#include "md5.h"
#define INFO_BUFFER_SIZE 32767

namespace hwid
{
	std::string get();
}