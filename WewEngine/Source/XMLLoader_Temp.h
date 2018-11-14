#pragma once

#include "WewEngineStd.h"

tinyxml2::XMLElement* LoadAndGetRoot_TEMP(const char* pFilePath)
{
	// [TODO]: REFACTOR!!!!!!
	static tinyxml2::XMLDocument toLoad;
	toLoad.LoadFile(pFilePath);

	if (toLoad.Error())
	{
		LOG(Error, "Failed to load a file!");
		return nullptr;
	}

	return toLoad.RootElement();
}