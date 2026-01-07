#ifndef LIB_PSS_FEATURES_H
#define LIB_PSS_FEATURES_H 1

// mono features
#define TARGET_PSS
#define PSS_USE_CRYPTO

// LibPsm Features

//#define DEBUGGING_UNIMPLEMENTED_IS_ERROR // all "unimplemented functions" will throw an error.

#define INACCURATE_DONT_ENFORCE_MAX_SDK // include SDK functions, even if their removed in a later SDK.
//#define INACCURATE_DONT_ENFORCE_MIN_SDK // include SDK functions, even if their only added in a newer SDK.

#define INACCURATE_DONT_ENFORCE_MEM_LIMIT // it's currently broken, 

#define USE_DX1 // not sure what this is about, but the implementation in PSM seems maybe wrong.

#endif