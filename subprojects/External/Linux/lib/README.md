# Info about external libaries

monosgen-2.0.lib, eglib.lib, etc are built from https://github.com/OpenPSS/pss-mono 
which itself is a slightly modified (to actually build, and to port to MSVC2022) version of Sony's original Fork of Mono for PSM.

Mono is licensed under the GPLv2, and so sony actually had to release the source code for PSM's Mono Runtime. and we can use it here without issue because sony's fork is also licensed under the GPLv2.

