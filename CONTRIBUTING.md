SnowPME is a PlayStation Mobile emulator;


first: 

please dont use AI here, their generally bad at understanding common Vita internals like e.g NIDs, 
and its also generally bad for reverse-engineering in general; since you have to know what the program acutally does to validate results !!
 .. but also, [anarchist rants about LLMS](https://silica.codes/ramblings/ai.htm)


relevant file structure is: 

  subprojects/LibPSM -- main psm libraries; 
  subprojects/LibCXML -- parsing app.info, cxml stuffs;
  subprojects/LibSnowPME -- custom GUI, handling of certain functions
  subprojects/LibShared -- stuff shared between multiple projects;
  
  tests/ -- various tests for the emulator; written in C# using the PSM SDK;
  
the project uses Meson build system, but also MSVC for windows; 
its primary dependancies are SDL2, SDL2_ttf, Mono, ImGui;

the Mono used here is itself a fork of SCE's mono fork (pss-mono) 

some notes while contributing: 

try to make things similuar to the internals of PSM.exe or ScePsm on vita, (doesn't have to me, some stuff like the ::impl:: classes for instance)
this is mostly just so its probably going to work the same, most of whats here has been gathered by reverse engineering these binarys

try to write some tests using the PSM SDK that actually make use of those functions, but also validate those tests behaviour on the actual PSM Runtime.

you can use the android version to cross-reference for symbols, 
but as its an older version of PSM, please try to avoid copying its implementation too much, instead focusing on PSM.exe or ScePsm;


reverse engineering using IDA or whatever, various tools and stuff are avalible here; https://git.silica.codes/OpenPSS/reverse-pss

please use ifdef guards instead of pragma once following the format 
```
#ifndef LIB_PSM_{FILIENAME}_H 
#define LIB_PSM_{FILIENAME}_H 1 
```

(mostly just because thats what we've done here),
