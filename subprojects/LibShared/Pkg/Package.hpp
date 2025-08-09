#ifndef SHARED_PACKAGE_H
#define SHARED_PACKAGE_H 1
#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif

int expand_package(const char* pkg_file, const char* out_folder, void (*progress_callback)(const char*, uint64_t, uint64_t));

#ifdef __cplusplus
}
#endif

#endif