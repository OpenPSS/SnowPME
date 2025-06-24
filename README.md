![logo](https://raw.githubusercontent.com/OpenPSS/SnowPME/refs/heads/main/SnowPME/resources/logo.png)


[![Build Artifacts](https://github.com/OpenPSS/SnowPME/actions/workflows/build_artifacts.yml/badge.svg?branch=main)](https://github.com/OpenPSS/SnowPME/actions/workflows/build_artifacts.yml)

SnowPME is a emulator for [PlayStation Mobile](https://en.wikipedia.org/wiki/PlayStation_Mobile).

well actually, 'emulator' is maybe not the right term, PSM software is built targeting the [Common Intermediate Language](https://en.wikipedia.org/wiki/Common_Intermediate_Language);
and the are very much _designed_ to work on multiple devices, it's built upon the [.NET CLR](https://en.wikipedia.org/wiki/Common_Language_Runtime) and even offically uses a fork of [Mono](https://www.mono-project.com/)

PlayStation Mobile games were originally distributed on both the [PS Vita](https://en.wikipedia.org/wiki/PlayStation_Vita), 
and some android phones such as the [Xperia Play](https://en.wikipedia.org/wiki/Xperia_Play) 
a windows version of it also exists though explicitly for developers, included in the SDK;

however, PSM also has quite alot of custom functionality built in as well, for graphics, music, leaderboards, controllers, etc 
which is why you can't just run ``app.exe`` and have it work; the custom functionality is mostly what SnowPME tries to replicate;

however, unlike Mono/.NET PSM makes some effort to isolate itself from the rest of your OS, (io sandbox, no p/invoke, managed code only) 
and the CLR is still a CPU architecture, just not one anyone ever made with electronics;
and an emulator is generlaly understood to run something made for one thing, on a different thing;
and don't even get me started on 'server emulators'... so- you could argue either way; its just silly semantics anyway;

but- i already chose the name SnowPME and "PME" was meant to mean "Playstation Mobile Emulator" so thats what we're going with;

# Notice 

Please note; this is in active development; most graphics related functionality is not done yet;
so not much will run under this as of yet, mostly every retail game will just crash very early on;

alot more also needs to still be done; currently only [a couple basic tests](https://github.com/OpenPSS/PSS-TESTS) run currently;

if you just want to running psm software on your PC,
the best way at the moment is manually decrypting all the files;
then running ``app.exe`` under the "PSM Simulator" from the PSM SDK.

# Setup

Before you can do anything; you need to extract the .NET Runtime Libraries ``System.dll`` ``mscorlib.dll`` and ``Sce.PlayStation.Core.dll``
from the "PSM Runtime Package" (PCSI10011), or "PSM Developer Assistant" (PCSI10007), on PS VITA, or from the "PlayStation Mobile SDK";

if your extracting files from a PS Vita, they do have to be PFS decrypted; 
but do not have to be PSSE decrypted;

please note that software made for PlayStation Mobile for Unity (PCSI10009, & PCSI10010) runtimes;
are not yet supported at all; and are not planned at this time;
