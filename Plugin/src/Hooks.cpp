#include "Hooks.h"

#include "Offsets.h"
#include "Utils.h"

namespace Hooks
{
    void Patches::SetBufferFormat(RE::Buffers a_buffer, RE::BS_DXGI_FORMAT a_format)
    {
		(*Offsets::bufferArray)[static_cast<uint32_t>(a_buffer)]->format = a_format;
    }

    void Hooks::Hook_UnkFunc(uintptr_t a1, UnkObject* a2)
    {
		const auto settings = Settings::Main::GetSingleton();
		switch (*settings->FrameBufferFormat) {
		case 1:
			a2->swapChainInterface->SetColorSpace1(DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020);
			break;
		case 2:
			a2->swapChainInterface->SetColorSpace1(DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709);
			break;
		}

		return _UnkFunc(a1, a2);		
    }

#ifndef NDEBUG
    void DebugHooks::Hook_CreateRenderTargetView(uintptr_t a1, ID3D12Resource* a_resource, DXGI_FORMAT a_format, uint8_t a4, uint16_t a5, uintptr_t a6)
    {
		const auto textureDesc = a_resource->GetDesc();

		_CreateRenderTargetView(a1, a_resource, a_format, a4, a5, a6);
    }

    void DebugHooks::Hook_CreateDepthStencilView(uintptr_t a1, ID3D12Resource* a_resource, DXGI_FORMAT a_format, uint8_t a4, uint16_t a5, uintptr_t a6)
    {
		const auto textureDesc = a_resource->GetDesc();

		_CreateDepthStencilView(a1, a_resource, a_format, a4, a5, a6);
    }
#endif

    void Install()
	{
#ifndef NDEBUG
	    Utils::LogBuffers();
		//DebugHooks::Hook();
#endif
		Hooks::Hook();
		Patches::Patch();
	}
}
