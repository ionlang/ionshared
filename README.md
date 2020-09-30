### ionshared

A library containing shared utilities and classes used by IonLang,
IonIR, and ILC projects.

### Requirements

* [CMake](https://cmake.org/download/)
* GCC `>=v10`
* [LLVM](https://releases.llvm.org/download.html)¹ `=v9.0.0`
* [Mingw64](http://mingw-w64.org/doku.php/download)² (Windows only)

---
1. _A different, close version of LLVM might work, but you will need to modify
`CMakeLists.txt`, specifically where `find_package(LLVM X.0.0 REQUIRED CONFIG)` occurs._

2. _Mingw64's GCC version is 8 and not 10, so you might have to use
[WinBuild](http://win-builds.org/doku.php)'s GCC 10 along with Mingw64 on Windows._

### Building & installing

```shell
# Clone the repository.¹
$ git clone https://github.com/ionshared
$ cd ionlang

# Generate Makefiles and build.
$ mkdir build
$ cd build
$ cmake ..
$ cmake --build .

# Install the library. Might require additional permissions.²
$ cmake --install .
```

---
1. _Make sure you've selected the correct branch you're intending to
build (`dev` for latest changes, `master` for stable), and initialized
git submodules after cloning the repository and prior to building._

2. _Installing the library might require administrator (or super-user)
permissions, as the installed files will likely be placed under restricted
paths. If you're using Windows, re-open the Command prompt (or PowerShell)
as Administrator. If you're on a Unix-like system, simple prepend `sudo` to
the install command._
