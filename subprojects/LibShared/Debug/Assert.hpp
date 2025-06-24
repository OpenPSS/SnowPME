#ifndef SHARED_ASSERT_H
#define SHARED_ASSERT_H 1
#include <cassert>
#include <cstdlib>
#include <cstdint>
#include <Debug/Logger.hpp>

#define RELEASE_ASSERT(expression) if(expression) { \
										Shared::Debug::Logger::Error("!!! ASSERT FAILED: " + std::string(#expression) + " in file: " + std::string(__FILE__) + " line: " + std::to_string((uint32_t)(__LINE__))); \
										std::abort(); \
									}

#define DEBUG_ASSERT(expression) assert(expression);

#ifdef _DEBUG
#define ASSERT(expression) DEBUG_ASSERT(expression);
#else
#define ASSERT(expression) RELEASE_ASSERT(expression);
#endif

#endif