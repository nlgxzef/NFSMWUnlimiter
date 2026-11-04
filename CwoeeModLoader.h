#pragma once

namespace CwoeeModLoader {
	template<typename T>
	T GetFuncPtr(const char* funcName) {
		if (auto dll = LoadLibraryA("NFSMWCwoeeModLoader_gcp.asi")) {
			return (T)GetProcAddress(dll, funcName);
		}
		if (auto dll = LoadLibraryA("NFSMWCwoeeModLoader_gcp.dll")) {
			return (T)GetProcAddress(dll, funcName);
		}
		return nullptr;
	}

	int GetNumCarTypeInfos() {
		static auto funcPtr = GetFuncPtr<int(__cdecl*)()>("CwoeeModLoader_GetNumCarTypeInfos");
		if (!funcPtr) return 0;
		return funcPtr();
	}
}