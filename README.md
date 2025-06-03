![logo](https://github.com/user-attachments/assets/e0f4cc30-6901-4ba4-aa4e-b8a494b60b71)

a [PlayStation Mobile](https://en.wikipedia.org/wiki/PlayStation_Mobile) Emulator for Linux and Windows;

# Notice 

Please note; this is in active development; most graphics related functionality is not done yet;
so not much will run under this as of yet, mostly every retail game will just crash very early on;

alot more also needs to still be done; currently only [a couple basic tests](https://github.com/OpenPSS/PSS-TESTS) run currently;

if you just want to running psm software on your PC,
the best way at the moment is manually decrypting all the files;
then running ``app.exe`` under the "PSM Simulator" from the PSM SDK.

# Setup

Before you can do anything; you need to extract the .NET Runtime Libraries ``System.dll`` ``mscorlib.dll`` and ``Sce.PlayStation.Core.dll``
from the "PSM Runtime Package" (PCSI10011), the "PSM Developer Assistant" (PCSI10007), or from the "PlayStation Mobile SDK";

these files have to be PFS decrypted- but do not have to be PSSE decrypted;

please note that software made for PlayStation Mobile for Unity (PCSI10009, & PCSI10010) runtimes;
are not yet supported at all; and are not planned at this time;
