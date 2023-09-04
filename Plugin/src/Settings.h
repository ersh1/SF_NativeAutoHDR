#pragma once
#include "DKUtil/Config.hpp"

namespace Settings
{
    using namespace DKUtil::Alias;

    class Main : public DKUtil::model::Singleton<Main>
    {
    public:
		Integer ImageSpaceBufferFormat{ "ImageSpaceBufferFormat", "Main" };
		Integer ScaleformCompositeBufferFormat{ "ScaleformCompositeBufferFormat", "Main" };

        Integer FrameBufferFormat = { "FrameBufferFormat", "HDR" };

        void Load() noexcept;

    private:
		TomlConfig config = COMPILE_PROXY("NativeHDR.toml"sv);
    };
}