#pragma once
#define CONFIG_ENTRY ""
#include "DKUtil/Config.hpp"

namespace Settings
{
    using namespace DKUtil::Alias;

    class Main : public DKUtil::model::Singleton<Main>
    {
    public:
		Integer ImageSpaceBufferFormat{ "ImageSpaceBufferFormat", "Main" };
		Boolean UpgradeUIRenderTarget{ "UpgradeUIRenderTarget", "Main" };
		Integer UpgradeRenderTargets{ "UpgradeRenderTargets", "Main" };

		Integer FrameBufferFormat{ "FrameBufferFormat", "HDR" };

		String RenderTargetsToUpgrade{ "RenderTargetsToUpgrade", "RenderTargets" };

        void Load() noexcept;

    private:
		TomlConfig config = COMPILE_PROXY("NativeAutoHDR.toml"sv);
    };
}