#pragma once
#include "Settings.h"

#include <d3d12.h>
#include <dxgi1_6.h>

namespace Hooks
{
	class Patches
	{
	public:
		static void Patch()
		{
			uint32_t* frameBufferPtr = nullptr;
			uint32_t* imageSpaceBufferPtr = nullptr;
			uint32_t* scaleformCompositeBufferPtr = nullptr;

			{
				const auto scan = static_cast<uint8_t*>(dku::Hook::Assembly::search_pattern<"C6 45 68 01 8B 05 ?? ?? ?? ??">());
				if (!scan) {
					ERROR("Failed to find FrameBuffer format variable")
				}
				const auto offset = *reinterpret_cast<int32_t*>(scan + 6);
				frameBufferPtr = reinterpret_cast<uint32_t*>(scan + 10 + offset);  // 507A290
			}

			{
				const auto scan = static_cast<uint8_t*>(dku::Hook::Assembly::search_pattern<"44 8B 05 ?? ?? ?? ?? 89 55 FB">());
				if (!scan) {
					ERROR("Failed to find ImageSpaceBuffer and ScaleformCompositeBuffer format variables")
				}
				const auto offset = *reinterpret_cast<int32_t*>(scan + 3);
				imageSpaceBufferPtr = reinterpret_cast<uint32_t*>(scan + 7 + offset);  // 5079A70
				scaleformCompositeBufferPtr = reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(imageSpaceBufferPtr) + 0x280);  // 5079CF0
			}

			const auto settings = Settings::Main::GetSingleton();

			switch (*settings->FrameBufferFormat) {
			case 1:
				*frameBufferPtr = 62;
				break;
			case 2:
				*frameBufferPtr = 77;
				break;
			}

			switch (*settings->ImageSpaceBufferFormat) {
			case 1:
				*imageSpaceBufferPtr = 62;
				break;
			case 2:
				*imageSpaceBufferPtr = 77;
				break;
			}

			switch (*settings->ScaleformCompositeBufferFormat) {
			case 1:
				*scaleformCompositeBufferPtr = 62;
				break;
			case 2:
				*scaleformCompositeBufferPtr = 77;
				break;
			}
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
			const auto settings = Settings::Main::GetSingleton();
			if (*settings->FrameBufferFormat != 0) {
				const auto scan = static_cast<uint8_t*>(dku::Hook::Assembly::search_pattern<"E8 ?? ?? ?? ?? 8B 4D A8 8B 45 AC">());
				if (!scan) {
					ERROR("Failed to find color space hook")
				}
				const auto callsiteOffset = *reinterpret_cast<int32_t*>(scan + 1);
				const auto UnkFuncCallsite = AsAddress(scan + 5 + callsiteOffset + 0x3EA);

				_UnkFunc = dku::Hook::write_call<5>(UnkFuncCallsite, Hook_UnkFunc);  // 32E7856
			}
		}

	private:
		static void Hook_UnkFunc(uintptr_t a1, UnkObject* a2);

		static inline std::add_pointer_t<decltype(Hook_UnkFunc)> _UnkFunc;
	};

#ifndef NDEBUG
	class DebugHooks
	{
	public:
		static void Hook()
		{
			const auto callsite1 = AsAddress(dku::Hook::Module::get().base() + 0x32ED294);
			const auto callsite2 = AsAddress(dku::Hook::Module::get().base() + 0x32ED341);
			const auto callsite3 = AsAddress(dku::Hook::Module::get().base() + 0x32ED2C1);
			const auto callsite4 = AsAddress(dku::Hook::Module::get().base() + 0x32ED37F);

			_CreateRenderTargetView = dku::Hook::write_call<5>(callsite1, Hook_CreateRenderTargetView);
			dku::Hook::write_call<5>(callsite2, Hook_CreateRenderTargetView);
			_CreateDepthStencilView = dku::Hook::write_call<5>(callsite3, Hook_CreateDepthStencilView);
			dku::Hook::write_call<5>(callsite4, Hook_CreateDepthStencilView);
		}

	private:
		static DXGI_FORMAT Hook_GetFormat(uint32_t a_format);
		static void Hook_CreateRenderTargetView(uintptr_t a1, ID3D12Resource* a_resource, DXGI_FORMAT a_format, uint8_t a4, uint16_t a5, uintptr_t a6);
		static void Hook_CreateDepthStencilView(uintptr_t a1, ID3D12Resource* a_resource, DXGI_FORMAT a_format, uint8_t a4, uint16_t a5, uintptr_t a6);

		static inline std::add_pointer_t<decltype(Hook_GetFormat)> _GetFormat;
		static inline std::add_pointer_t<decltype(Hook_CreateRenderTargetView)> _CreateRenderTargetView;
		static inline std::add_pointer_t<decltype(Hook_CreateDepthStencilView)> _CreateDepthStencilView;
	};
#endif

	void Install();
}