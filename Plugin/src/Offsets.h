#pragma once
#include "RE/Buffers.h"

class Offsets
{
public:
	using BufferArray = std::array<RE::BufferDefinition*, 204>;
	static inline BufferArray* bufferArray = nullptr;

	using tGetDXGIFormat = DXGI_FORMAT (*)(RE::BS_DXGI_FORMAT a_bgsFormat);
	static inline tGetDXGIFormat GetDXGIFormat = nullptr;

	static void Initialize()
	{
		bufferArray = reinterpret_cast<BufferArray*>(dku::Hook::IDToAbs(477165));
		GetDXGIFormat = reinterpret_cast<tGetDXGIFormat>(dku::Hook::IDToAbs(204483));
	}
};
