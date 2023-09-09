#include "Settings.h"

namespace Settings
{
	void Main::Load() noexcept
	{
		static std::once_flag ConfigInit;
		std::call_once(ConfigInit, [&]() {
			config.Bind(ImageSpaceBufferFormat, 0);
			config.Bind(UpgradeUIRenderTarget, true);
			config.Bind(UpgradeRenderTargets, 2);
			config.Bind(FrameBufferFormat, 0);
		});

		config.Load();

		INFO("Config loaded"sv)
	}
}