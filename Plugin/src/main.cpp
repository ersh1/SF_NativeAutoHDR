#include "DKUtil/Config.hpp"

#include "Hooks.h"
#include "Offsets.h"
#include "Settings.h"

using namespace DKUtil::Alias;

BOOL APIENTRY DllMain(HMODULE a_hModule, DWORD a_ul_reason_for_call, LPVOID a_lpReserved)
{
	if (a_ul_reason_for_call == DLL_PROCESS_ATTACH) {
#ifndef NDEBUG
		while (!IsDebuggerPresent()) {
			Sleep(100);
		}
#endif

		// stuff
		dku::Logger::Init(Plugin::NAME, std::to_string(Plugin::Version));

		INFO("game type : {}", dku::Hook::GetProcessName())
		INFO("base address : {:X}", dku::Hook::Module::get().base())

		dku::Hook::Trampoline::AllocTrampoline(14);
		Settings::Main::GetSingleton()->Load();
		Offsets::Initialize();
		Hooks::Install();
	}

	return TRUE;
}