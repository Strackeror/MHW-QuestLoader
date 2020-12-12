# Stracker's Loader

## Build instructions

### Prerequisites

> TODO: add prerequisites details. VC++ toolchain and w/e

The project now uses [vcpkg](https://github.com/microsoft/vcpkg#getting-started).
You'll need to clone `vcpkg`, bootstrap it, and add it to your path.
Open up powershell and run this:

```pwsh
git clone git@github.com:microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg.exe integrate install

$vcpkg=(Get-Location).Path
$env:Path += ";$vcpkg"
[Environment]::SetEnvironmentVariable("Path", $env:Path, [System.EnvironmentVariableTarget]::User)
```

You'll also need to add a couple of environment variables because manifests is still a beta feature and x64 isn't default for some reason:

```pwsh
$env:VCPKG_FEATURE_FLAGS = "manifests"
$env:VCPKG_DEFAULT_TRIPLET="x64-windows-static"

[Environment]::SetEnvironmentVariable("VCPKG_DEFAULT_TRIPLET", $env:VCPKG_DEFAULT_TRIPLET, [System.EnvironmentVariableTarget]::User)
[Environment]::SetEnvironmentVariable("VCPKG_FEATURE_FLAGS", $env:VCPKG_FEATURE_FLAGS, [System.EnvironmentVariableTarget]::User)
```

### Build

If you want to build from the cli, in the project root:
```pwsh
msbuild .\StrackerLoader.sln /p:Configuration=Release
```

Visual Studio and `msbuild` will install dependencies automatically to _<PROJECT_DIR>/vcpkg_installed/_ similar to node_packages.

> Under the hood, it's doing `vcpkg install`
