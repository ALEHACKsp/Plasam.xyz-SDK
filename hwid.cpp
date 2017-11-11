#include "hwid.h"

using namespace std;



string GetHddSerial() {
	TCHAR volumeName[MAX_PATH + 1] = { 0 };
	TCHAR fileSystemName[MAX_PATH + 1] = { 0 };
	DWORD serialNumber;
	DWORD maxComponentLen;
	DWORD fileSystemFlags;
	if (GetVolumeInformation(
		_T("C:\\"),
		volumeName,
		sizeof(volumeName),
		&serialNumber,
		&maxComponentLen,
		&fileSystemFlags,
		fileSystemName,
		sizeof(fileSystemName))
		)
	{
		stringstream ss;
		ss << serialNumber;
		string str = ss.str();
		return str + "-";
	}
	else
	{
		return "";
	}
}

string GetProcessorArchitecture() {

	SYSTEM_INFO siSysInfo;
	GetSystemInfo(&siSysInfo);
	string ProcessorArchitecture;
	switch (siSysInfo.wProcessorArchitecture)
	{
	case 9:
		ProcessorArchitecture = "x64";
		break;

	case 5:
		ProcessorArchitecture = "ARM";
		break;

	case 6:
		ProcessorArchitecture = "Itallium";
		break;

	case 0:
		ProcessorArchitecture = "x86";
		break;

	default:
		ProcessorArchitecture = "unknown";
	}
	return ProcessorArchitecture + "-";
}

string GetUserInfo() {
	TCHAR infoBuf[INFO_BUFFER_SIZE];
	DWORD  bufCharCount = INFO_BUFFER_SIZE;
	std::string computerName;
	std::string username;
	GetComputerName(infoBuf, &bufCharCount);
	computerName = infoBuf;
	GetUserName(infoBuf, &bufCharCount);
	username = infoBuf;
	return computerName + "-" + username;
}

namespace hwid
{
	string get()
	{
		string hdd = GetHddSerial();
		string proc = GetProcessorArchitecture();
		string user = GetUserInfo();
		string total = hdd + proc + user;
		return md5(total);
	}
}