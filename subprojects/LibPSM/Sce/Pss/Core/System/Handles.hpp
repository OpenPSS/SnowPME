#ifndef LIB_PSS_HANDLES_H
#define LIB_PSS_HANDLES_H 1
#include <cstddef>
#include <stdint.h>
#include <unordered_map>
#include <Sce/Pss/Core/PsmMutexObject.hpp>

namespace Sce::Pss::Core::System {
	class Handles : public PsmMutexObject<Handles> {
	private:
		static std::unordered_map<int, void*> handles;
		static int lastHandle;
	public:
		static const int NoHandle = 0x0;
		static bool IsValid(uint64_t handle) {
			return Handles::IsValid(static_cast<int>(handle));
		}
		static bool IsValid(int handle) {
			return handles.contains(handle);
		}
		template<typename T> static int Create(T* address) {
			LOCK_GUARD_STATIC();
			int handle = ++lastHandle;
			assert(!Handles::IsValid(handle));
			handles.emplace(handle, address);
			return handle;
		}

		template<typename T> static T* Get(uint64_t handle) {
			return Handles::Get<T>(static_cast<int>(handle));
		}

		template<typename T> static T* Get(int handle) {
			LOCK_GUARD_STATIC();
			auto it = handles.find(handle);
			if(it == handles.end()) return nullptr;
			return reinterpret_cast<T*>(handles[handle]);
		}
		static void Delete(int handle) {
			LOCK_GUARD_STATIC();
			if (!Handles::IsValid(handle)) return;
			handles.erase(handle);
		}
	};
}

#endif
