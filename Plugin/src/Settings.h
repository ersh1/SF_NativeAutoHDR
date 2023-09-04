#pragma once
#include "DKUtil/Config.hpp"

namespace Settings
{
    using namespace DKUtil::Alias;

    class Main : public DKUtil::model::Singleton<Main>
    {
    public:
		Boolean scRGB = { "scRGB", "Main" };

        void Load() noexcept;

    private:
		TomlConfig config = COMPILE_PROXY("NativeHDR.toml"sv);
    };
}