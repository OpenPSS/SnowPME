#ifndef LIB_PSS_HANDLES_H
#define LIB_PSS_HANDLES_H 1
#include <cstddef>
#include <stdint.h>
#include <unordered_map>

namespace Sce::Pss::Core::System {
	class Handles {
	private:
		static std::unordered_map<int, void*> handles;
		static int lastHandle;
	public:
		static const int NoHandle = 0x0;
		static bool IsValid(int handle) {
			return handles.contains(handle);
		}
		template<typename T> static int Create(T* address) {
			int handle = ++lastHandle;
			if(handles.contains(handle)) {
				*(int*)0 = 0;
			}
			handles.emplace(handle, address);
			return handle;
		}
		template<typename T> static T* Get(int handle) {
			auto it = handles.find(handle);
			if(it == handles.end()) return NULL;
			return reinterpret_cast<T*>(handles[handle]);
		}
		static void Delete(int handle) {
			if (!IsValid(handle))
				return;
			handles.erase(handle);
		};
	};
}

#endif
