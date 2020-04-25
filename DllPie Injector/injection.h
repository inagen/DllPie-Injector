#pragma once
#include <Windows.h>
#include <tchar.h>
#include <psapi.h>
#include <string>
#include <vector>
#include <map>



class Injector {
public:
	std::vector<std::pair<DWORD, std::string>> processes = getAllProcessNamesAndIDs();
	enum class InjectionMethod {
		NotStated,
		LoadLibraryA
	};
private:
	InjectionMethod currentInjectionMethod = InjectionMethod::NotStated;
	DWORD PID = 0;
	LPCSTR dllPath = NULL;

public:
	Injector() = default;
	void setInjectionMethod(InjectionMethod);
	void setProcessByIndex(size_t index);
	void setDllPath(std::string);
	bool inject();
	~Injector();
private:
	std::string getProcessNameAndID(DWORD PID);
	std::vector<std::pair<DWORD, std::string>> getAllProcessNamesAndIDs();
	bool loadLibraryAInjection();
};

