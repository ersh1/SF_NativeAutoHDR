#include "Hooks.h"

namespace Hooks
{
    void Hooks::Hook_UnkFunc(uintptr_t a1, UnkObject* a2)
    {
		const auto settings = Settings::Main::GetSingleton();
		auto colorSpace = settings->scRGBFrameBuffer ? DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709 : DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020;

		a2->swapChainInterface->SetColorSpace1(colorSpace);

		_UnkFunc(a1, a2);
    }

#ifndef NDEBUG
    DXGI_FORMAT DebugHooks::Hook_GetFormat(uint32_t a_format)
    {
		auto format = _GetFormat(a_format);
		if (format == DXGI_FORMAT_R8G8B8A8_UNORM || format == DXGI_FORMAT_R8G8B8A8_UNORM_SRGB) {
		    return DXGI_FORMAT_R16G16B16A16_FLOAT;
		}

		return format;
    }

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
		Hooks::Hook();
		Patches::Patch();

#ifndef NDEBUG
		DebugHooks::Hook();
#endif
	}
}