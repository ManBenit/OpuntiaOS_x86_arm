<img src="https://raw.githubusercontent.com/opuntiaOS-Project/opuntiaOS/master/assets/logo/logo_512.png" width="20"> <b> DOCS</b></br></br>

# Getting GN

GN is a meta-build system that generates build files for Ninja.

## Getting a binary

You can download the latest version of GN binary for Linux and macOS from Google's build infrastructure 

| MacOS | Linux |
| ------------- | ------------- |
| [amd64](https://chrome-infra-packages.appspot.com/dl/gn/gn/mac-amd64/+/latest)<br>[arm64](https://chrome-infra-packages.appspot.com/dl/gn/gn/mac-arm64/+/latest) | [amd64](https://chrome-infra-packages.appspot.com/dl/gn/gn/linux-amd64/+/latest)<br>[arm64](https://chrome-infra-packages.appspot.com/dl/gn/gn/linux-arm64/+/latest) |

Alternatively, you can build GN from source with a C++17 compiler:

```bash
git clone https://gn.googlesource.com/gn
cd gn
python build/gen.py
ninja -C out
# To run tests:
out/gn_unittests
```

*Note:* On Linux and Mac, the default compiler is clang++, a recent version is expected to be found in PATH. This can be overridden by setting CC, CXX, and AR.

For more inforamtion, please visit: https://gn.googlesource.com/gn/