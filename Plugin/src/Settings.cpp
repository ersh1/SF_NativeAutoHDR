#include "Settings.h"

namespace Settings
{
	void Main::Load() noexcept
	{
		static std::once_flag ConfigInit;
		std::call_once(ConfigInit, [&]() {
			config.Bind(ImageSpaceBufferFormat, 2);
			config.Bind(ScaleformCompositeBufferFormat, 2);
			config.Bind(FrameBufferFormat, 0);
		});

		config.Load();

		INFO("Config loaded"sv)
	}
}