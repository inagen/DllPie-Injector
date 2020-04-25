#include "injection.h"
#include <sstream>

#define checkZero(ptr) if(true){\
	if (!ptr){\
		return false;\
	}\
}

std::string Injector::getProcessNameAndID(DWORD PID)
{
	TCHAR processName[MAX_PATH] = L"<unknown>";

	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, PID);


	if (hProcess != NULL)
	{
		HMODULE hMod;
		DWORD cbNeeded;

		if (EnumProcessModules(hProcess, &hMod, sizeof(hMod),
			&cbNeeded))
		{
			GetModuleBaseName(hProcess, hMod, processName,
				sizeof(processName) / sizeof(TCHAR));
		}
	}

	CloseHandle(hProcess);
	std::wstring wstr = processName;
	std::stringstream ss;
	ss << "[" << PID << "]" << " " << std::string(wstr.begin(), wstr.end());
	return ss.str();
}

std::vector<std::pair<DWORD, std::string>> Injector::getAllProcessNamesAndIDs() {
	std::vector<std::pair<DWORD, std::string>> result;
	DWORD aProcesses[1024], cbNeeded, processNum;

	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
	{
		return result;
	}

	processNum = cbNeeded / sizeof(DWORD);

	for (size_t i = 0; i < processNum; i++)
	{
		if (aProcesses[i])
		{
			result.push_back({ aProcesses[i], getProcessNameAndID(aProcesses[i]) });
		}
	}
	return result;
}


void Injector::setProcessByIndex(size_t index) {
	PID = processes.at(index).first;
}

void Injector::setDllPath(std::string newDllPath) {
	if (dllPath) {
		delete dllPath;
	}
	char* ptr = new char[newDllPath.size()];
	strcpy(ptr, newDllPath.c_str());
	dllPath = ptr;
}

void Injector::setInjectionMethod(InjectionMethod newMethod) {
	currentInjectionMethod = newMethod;
}

bool Injector::inject() {
	if (PID == 0 || dllPath == NULL) {
		return false;
	}
	switch (currentInjectionMethod)
	{
	case InjectionMethod::NotStated:
		return false;
		break;
	case InjectionMethod::LoadLibraryA:
		return loadLibraryAInjection();
		break;
	default:
		return false;
	}
}

Injector::~Injector() {
	if (dllPath) {
		delete dllPath;
	}
}

bool Injector::loadLibraryAInjection() {
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
	checkZero(hProcess)

	LPVOID pDllPath = VirtualAllocEx(hProcess, 0, strlen((const char*)dllPath) + 1,
		MEM_COMMIT, PAGE_READWRITE);
	checkZero(pDllPath)

	bool writeProcessMemoryResult = WriteProcessMemory(hProcess, pDllPath, (LPVOID)dllPath,
		strlen((const char*)dllPath) + 1, 0);
	checkZero(writeProcessMemoryResult)

	HANDLE hLoadThread = CreateRemoteThread(hProcess, 0, 0,
		(LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("Kernel32.dll"),
			"LoadLibraryA"), pDllPath, 0, 0);
	checkZero(hLoadThread)

	WaitForSingleObject(hLoadThread, INFINITE);
	
	Sleep(100);

	VirtualFreeEx(hProcess, pDllPath, strlen((const char*)dllPath) + 1, MEM_RELEASE);
	
	return true;
}