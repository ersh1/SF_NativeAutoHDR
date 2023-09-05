#pragma once
#include "DKUtil/Config.hpp"

namespace Settings
{
    using namespace DKUtil::Alias;

    class Main : public DKUtil::model::Singleton<Main>
    {
    public:
		Boolean scRGBFrameBuffer = { "scRGBFrameBuffer", "Main" };
		Boolean scRGBImageSpaceBuffer{ "scRGBImageSpaceBuffer", "Main" };
		Boolean scRGBScaleformCompositeBuffer{ "scRGBScaleformCompositeBuffer", "Main" };
        
		//Boolean upgradeScaleformCompositeBuffer = { "upgradeScaleformCompositeBuffer", "Main" };

        void Load() noexcept;

    private:
		TomlConfig config = COMPILE_PROXY("Data/SFSE/Plugins/NativeHDR.toml"sv);
    };
}