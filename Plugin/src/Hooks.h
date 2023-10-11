#pragma once
#include "Settings.h"
#include "Utils.h"
#include "RE/Buffers.h"

#include <dxgi1_6.h>

namespace Hooks
{
	class Patches
	{
	public:
		static void Patch()
		{
			const auto settings = Settings::Main::GetSingleton();

			if (*settings->FrameBufferFormat == 2) {
				SetBufferFormat(RE::Buffers::FrameBuffer, RE::BS_DXGI_FORMAT::BS_DXGI_FORMAT_R16G16B16A16_FLOAT);
			} else {
				SetBufferFormat(RE::Buffers::FrameBuffer, RE::BS_DXGI_FORMAT::BS_DXGI_FORMAT_R10G10B10A2_UNORM);
			}

			switch (*settings->ImageSpaceBufferFormat) {
			case 1:
				SetBufferFormat(RE::Buffers::ImageSpaceBuffer, RE::BS_DXGI_FORMAT::BS_DXGI_FORMAT_R10G10B10A2_UNORM);
				break;
			case 2:
				SetBufferFormat(RE::Buffers::ImageSpaceBuffer, RE::BS_DXGI_FORMAT::BS_DXGI_FORMAT_R16G16B16A16_FLOAT);
				break;
			}

			if (*settings->UpgradeUIRenderTarget) {
				SetBufferFormat(RE::Buffers::ScaleformCompositeBuffer, RE::BS_DXGI_FORMAT::BS_DXGI_FORMAT_R16G16B16A16_FLOAT);
			}

			{
				if (*settings->UpgradeRenderTargets > 0) {
					const bool bLimited = *settings->UpgradeRenderTargets == 1 ? true : false;
					const RE::BS_DXGI_FORMAT format = *settings->UpgradeRenderTargets == 1 ? RE::BS_DXGI_FORMAT::BS_DXGI_FORMAT_R10G10B10A2_UNORM : RE::BS_DXGI_FORMAT::BS_DXGI_FORMAT_R16G16B16A16_FLOAT;

					for (const auto& renderTargetName : settings->RenderTargetsToUpgrade.get_collection()) {
					    if (auto buffer = GetBufferFromString(renderTargetName)) {
							UpgradeRenderTarget(buffer, format, bLimited);
					    }
                    }
				}
			}

			Utils::LogBuffers();
		}

	private:
		static RE::BufferDefinition* GetBufferFromString(std::string_view a_bufferName);

		static void UpgradeRenderTarget(RE::BufferDefinition* a_buffer, RE::BS_DXGI_FORMAT a_format, bool a_bLimited);
		static void SetBufferFormat(RE::BufferDefinition* a_buffer, RE::BS_DXGI_FORMAT a_format);
		static void SetBufferFormat(RE::Buffers a_buffer, RE::BS_DXGI_FORMAT a_format);
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
			_UnkFunc = dku::Hook::write_call<5>(dku::Hook::IDToAbs(204384, 0x3EA), Hook_UnkFunc);
		}

	private:
		static void Hook_UnkFunc(uintptr_t a1, UnkObject* a2);

		static inline std::add_pointer_t<decltype(Hook_UnkFunc)> _UnkFunc;
	};

	void Install();
}