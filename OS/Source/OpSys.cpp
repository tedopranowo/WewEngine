#include "OpSys.h"

#include "Logger.h"

#ifdef _WIN32
	#define WIN_32_LEAN_AND_MEAN
	#include <Windows.h>
#endif

OpSys::OpSys()
{
}


OpSys::~OpSys()
{
}

bool OpSys::CheckSystemResources()
{
	return false;
}

OpSys * OpSys::Create()
{
#ifdef _WIN32
	return new WindowsOS();
#else
	return nullptr;
#endif
}

bool WindowsOS::CheckFreeDiskSpace(const unsigned long long diskSpaceNeeded)
{
	//Used for save game data space requirement calculations
	unsigned long SectorsPerCluster;
	unsigned long BytesPerSector;
	unsigned long NumFreeClusters;
	unsigned long totalClusters;
	GetDiskFreeSpace("C:", &SectorsPerCluster, &BytesPerSector, &NumFreeClusters, &totalClusters);

	UINT64 NeededClusters = diskSpaceNeeded / (SectorsPerCluster * BytesPerSector);

	if (NeededClusters > NumFreeClusters)
	{
        LOG(Error, "Not enough hard disk memory to launch game.");
	}

	return false;
}

bool WindowsOS::WindowAlreadyExists(const char * pWindowName)
{
	HWND WindowHandle = FindWindow(NULL, pWindowName);

	if (WindowHandle != NULL)
	{
		ShowWindow(WindowHandle, SW_SHOWNORMAL);
		SetFocus(WindowHandle);
		SetForegroundWindow(WindowHandle);
		SetActiveWindow(WindowHandle);

		return true;
	}

	return false;
}
