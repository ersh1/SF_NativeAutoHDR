# 📑 Starfield Native HDR
Native dll plugin upgrading the Starfield's swapchain to a HDR format.

 [Nexus Mods page](https://www.nexusmods.com/starfield/mods/588)

## ⚙ Requirements

- [CMake](https://cmake.org/)
  - Add this to your `PATH`
- [DKUtil](https://github.com/gottyduke/DKUtil)
  - Init & update with git submodule
- [SFSE](https://github.com/ianpatt/sfse)
  - Init & update with git submodule
- [PowerShell](https://github.com/PowerShell/PowerShell/releases/latest)
- [Vcpkg](https://github.com/microsoft/vcpkg)
  - Add the environment variable `VCPKG_ROOT` with the value as the path to the folder containing vcpkg
- [Visual Studio Community 2022](https://visualstudio.microsoft.com/)
  - Desktop development with C++
- [Starfield Steam Distribution](#-deployment)
  - Add the environment variable `SFPath` with the value as the path to the game installation
  
## Get started

### 💻 Register Visual Studio as a Generator

- Open `x64 Native Tools Command Prompt`
- Run `cmake`
- Close the cmd window

### 🔨 Building

```
git clone https://github.com/ersh1/SF_NativeHDR.git
cd SF_NativeHDR
git submodule init
git submodule update
.\build-release.ps1
```

### ➕ DKUtil addon

This project bundles [DKUtil](https://github.com/gottyduke/DKUtil).

## 📖 License

[GPL-3.0-or-later](COPYING) WITH [Modding Exception AND GPL-3.0 Linking Exception (with Corresponding Source)](EXCEPTIONS). Specifically, the Modded Code is Starfield (and its variants) and Modding Libraries include [Starfield Script Extender](https://github.com/ianpatt/sfse) and [DKUtil](https://github.com/gottyduke/DKUtil/) (and variants).

## ❓ Credits

- [ianpatt's Starfield Script Extender](https://github.com/ianpatt/sfse)
- [Original plugin template](https://github.com/gottyduke/SF_PluginTemplate)
