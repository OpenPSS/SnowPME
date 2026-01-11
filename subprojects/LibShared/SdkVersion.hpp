#ifndef SHARED_SDK_VERSION_H
#define SHARED_SDK_VERSION_H 1

// SDK 2.00.XX (Windows & Vita Latest)
#define SDK_2_01_00 (0x020100u) // psvita exclusive version.
#define SDK_2_00_00 (0x020000u) // windows latest version.

// SDK 1.21.XX (Android latest)
#define SDK_1_21_02 (0x012102u) // android latest version.
#define SDK_1_21_01 (0x012101u)
#define SDK_1_21_00 (0x012100u)

// Other archived versions ..
#define SDK_1_20_00 (0x012000u)
#define SDK_1_11_01 (0x011001u)
#define SDK_1_10_00 (0x010000u)

// "PlayStation Suite" // pre release versions
#define SDK_0_98_00 (0x009800u)
#define SDK_0_99_00 (0x009900u)
#define SDK_0_99_11 (0x009911u)
#define SDK_0_99_20 (0x009920u)

#define MIN_SDK (SDK_0_98_00)
#define MAX_SDK (SDK_2_01_00)

#define NO_SDK	 INT_MIN

#endif