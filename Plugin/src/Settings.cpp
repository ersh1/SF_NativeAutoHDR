#include "Settings.h"

namespace Settings
{
	void Main::Load() noexcept
	{
		static std::once_flag ConfigInit;
		std::call_once(ConfigInit, [&]() {
			config.Bind(scRGBFrameBuffer, true);
			config.Bind(scRGBImageSpaceBuffer, true);
			config.Bind(scRGBScaleformCompositeBuffer, true);
		});

		config.Load();

		INFO("Config loaded"sv)
	}
}