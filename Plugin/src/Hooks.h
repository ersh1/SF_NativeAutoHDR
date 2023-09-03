#pragma once
#include "Settings.h"

#include <dxgi1_6.h>

namespace Hooks
{
    class Patches
    {
    public:
		static void Patch()
		{
			const auto scan = static_cast<uint8_t*>(dku::Hook::Assembly::search_pattern<"C6 45 68 01 8B 05 ?? ?? ?? ??">());
			if (!scan) {
			    ERROR("Failed to find format variable");
			}
			const auto offset = *reinterpret_cast<int32_t*>(scan + 6);
			uint32_t* format = reinterpret_cast<uint32_t*>(scan + 10 + offset);  // 507A290

			const auto settings = Settings::Main::GetSingleton();
			*format = settings->scRGB ? 77 : 62;
		}

    private:
    };

	class Hooks
	{
	public:
		struct UnkObject
		{
		    uint64_t unk00;
			uint64_t unk08;
			uint64_t unk10;
			uint64_t unk18;
			uint64_t unk20;
			uint64_t unk28;
			uint64_t unk30;
			uint64_t unk38;
			uint64_t unk40;
			uint64_t unk48;
			IDXGISwapChain3* swapChainInterface;
		};

		static void Hook()
		{
			const auto scan = static_cast<uint8_t*>(dku::Hook::Assembly::search_pattern<"E8 ?? ?? ?? ?? 8B 4D A8 8B 45 AC">());
			if (!scan) {
				ERROR("Failed to find callsite");
			}
			const auto callsiteOffset = *reinterpret_cast<int32_t*>(scan + 1);
			const auto UnkFuncCallsite = AsAddress(scan + 5 + callsiteOffset + 0x3EA);

			_UnkFunc = dku::Hook::write_call<5>(UnkFuncCallsite, Hook_UnkFunc);  // 32E7856
		}

	private:
		static void Hook_UnkFunc(uintptr_t a1, UnkObject* a2);

		static inline std::add_pointer_t<decltype(Hook_UnkFunc)> _UnkFunc;
	};

    void Install();
}