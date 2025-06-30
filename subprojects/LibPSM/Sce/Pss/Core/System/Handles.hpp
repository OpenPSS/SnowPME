#ifndef LIB_PSS_HANDLES_H
#define LIB_PSS_HANDLES_H 1
#include <cstddef>
#include <cstdint>
#include <unordered_map>
#include <LibShared.hpp>

namespace Sce::Pss::Core::System {
	template<typename T> class Handles {
	private:
		static std::unordered_map<int, std::shared_ptr<T>> handles;
		static std::atomic<int> lastHandle;
	public:
		static const int NoHandle = 0x0;
		static bool IsValid(uint64_t handle) {
			return Handles::IsValid(static_cast<int>(handle));
		}
		static bool IsValid(int handle) {
			if (handle == Handles::NoHandle) return false;
			return handles.contains(handle);
		}

		static int Create(std::shared_ptr<T> address) {
			int handle = ++lastHandle;
			ASSERT(!Handles::IsValid(handle));
			handles.emplace(handle, address);
			return handle;
		}

		static std::shared_ptr<T> Get(uint64_t handle) {
			return Handles<T>::Get(static_cast<int>(handle));
		}

		static std::shared_ptr<T> Get(int handle) {
			if (Handles::IsValid(handle)) {
				return handles[handle];
			}
			return nullptr;
		}
		static void Delete(int handle) {
			if (!Handles::IsValid(handle)) return;
			handles.erase(handle);
		}
	};

	template<typename T> std::unordered_map<int, std::shared_ptr<T>> Handles<T>::handles;
	template<typename T> std::atomic<int> Handles<T>::lastHandle = Handles::NoHandle;
}

#endif
