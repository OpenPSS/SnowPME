make sure to recursive clone the repo, it has alot of requirements

```
git clone https://github.com/OpenPSS/SnowPME.git --recursive
``` 

or alternatively if you already cloned it, you can use
```
git submodule update --init --recursive
```

# Windows

building for Windows requires Microsoft Visual Studio 2022; 
with "Desktop Development C++" option installed

you can either open the .sln file and click "build"
after selecting a target platform 
or run the following in Visual Studio Developer Command Prompt.

```
msbuild SnowPME.sln /p:Configuration=Release_Static /p:Platform=Win32
``` 

# Linux

before building on linux you begin you'll need to install dependancies; 

```
apt install build-essential meson libsdl2-dev mesa-utils libglu1-mesa-dev freeglut3-dev mesa-common-dev automake libtool-bin gettext
```

after that you should be able to just do:

```
meson setup build
cd build
ninja
```

and the SnowPME executable should be left in the 'build' folder.