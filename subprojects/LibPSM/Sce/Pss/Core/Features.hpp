#ifndef LIB_PSS_FEATURES_H
#define LIB_PSS_FEATURES_H 1

// mono features
#define TARGET_PSS
#define PSS_USE_CRYPTO

// LibPsm Features

//#define DEBUGGING_UNIMPLEMENTED_IS_ERROR

#define COMPAT_VITA_2_01_RUNTIME_FEATURES
#define COMPAT_WINDOWS_2_00_RUNTIME_FEATURES

#define INACCURATE_DONT_ENFORCE_MEM_LIMIT // it's currently broken, 
#define INACCURATE_ALLOW_0BYTE_IMAGE // remove once fonts are implemented.

// validate feature flags

#if !defined(COMPAT_VITA_2_01_RUNTIME_FEATURES) && !defined(COMPAT_WINDOWS_2_00_RUNTIME_FEATURES)
#error either vita compat 2.01 or windows runtime compat 2.00 must be enabled.
#endif

#endif