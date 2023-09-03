#include "Hooks.h"

namespace Hooks
{
    void Hooks::Hook_UnkFunc(uintptr_t a1, UnkObject* a2)
    {
		const auto settings = Settings::Main::GetSingleton();
		auto colorSpace = settings->scRGB ? DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709 : DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020;

		a2->swapChainInterface->SetColorSpace1(colorSpace);

		_UnkFunc(a1, a2);
    }

	void Install()
	{
		Hooks::Hook();
		Patches::Patch();
	}
}