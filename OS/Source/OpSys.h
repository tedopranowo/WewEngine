#pragma once
class OpSys
{
public:
	OpSys();
	virtual ~OpSys();

	virtual bool CheckFreeDiskSpace(const unsigned long long diskSpaceNeeded) = 0;
	virtual bool CheckSystemResources();
	virtual bool WindowAlreadyExists(const char* pWindowName) = 0;

	//Abstract Factory
	static OpSys* Create();
};

class WindowsOS : public OpSys
{
public:
	WindowsOS() {}
	~WindowsOS() {}

	// Inherited via OpSys
	bool CheckFreeDiskSpace(const unsigned long long diskSpaceNeeded) override;
	bool WindowAlreadyExists(const char* pWindowName) override;

};