#ifndef LIB_PSS_HANDLES_H
#define LIB_PSS_HANDLES_H 1
#include <cstddef>
#include <cstdint>
#include <memory>
#include <unordered_map>

#include <LibShared.hpp>

using namespace Shared::Debug;
using namespace Shared::String;

namespace Sce::Pss::Core::System {
	template<typename T> class Handles {
	public:
		static const int NoHandle = 0x00;
		static const int NoRawHandle = (INT_MAX / 2);

		static bool IsValid(uint64_t handle) {
			return Handles::IsValid(static_cast<int>(handle));
		}

		static bool IsValid(int handle) {
			if (handle >= NoHandle && handle <= lastHandle) {
				if (handle == NoHandle) return false;
				return handles.contains(handle);
			}
			else if (handle >= NoRawHandle && handle <= lastRawHandle) {
				if (handle == NoRawHandle) return false;
				return rawHandles.contains(handle);
			}
			return false;
		}

		static int Create(T* address) {
			int handle = ++lastRawHandle;
			ASSERT(!Handles::IsValid(handle));
			rawHandles.emplace(handle, address);
			return handle;
		}

		static int Create(std::shared_ptr<T> address) {
			int handle = ++lastHandle;
			ASSERT(!Handles::IsValid(handle));
			handles.emplace(handle, address);
			return handle;
		}

		static T* Get(uint64_t handle) {
			return Handles<T>::Get(static_cast<int>(handle));
		}

		static T* Get(int handle) {
			if (Handles::IsValid(handle)) {
				return std::dynamic_pointer_cast<T>(handles[handle]).get();
			}
			return nullptr;
		}

		static std::shared_ptr<T> GetShared(int handle) {
			if (Handles::IsValid(handle)) {
				return std::dynamic_pointer_cast<T>(handles[handle]);
			}
			return nullptr;
		}

		static T* GetRaw(uint64_t handle) {

			return Handles<T>::GetRaw(static_cast<int>(handle));
		}

		static T* GetRaw(int handle) {
			if (Handles::IsValid(handle)) {
				return dynamic_cast<T*>(rawHandles[handle]);
			}
			return nullptr;
		}

		static void DeleteEverything() {
			auto rawHandlesCpy = rawHandles;
			auto handlesCpy = handles;

			for (auto& handle : rawHandlesCpy) {
				T::Delete(handle.first);
			}
			for (auto& handle : handlesCpy) {
				T::Delete(handle.first);
			}

			handles.clear();
			rawHandles.clear();

			lastHandle = Handles::NoHandle;
			lastRawHandle = Handles::NoRawHandle;
		}

		static void Delete(int handle) {
			Logger::Debug(std::string(typeid(T).name()) + Format::Hex(Handles::GetShared(handle).use_count()));

			if (handle >= NoHandle && handle <= lastHandle) {
				if (handle == NoHandle) return;
				if (handles.contains(handle)) handles.erase(handle);
			}
			else if (handle >= NoRawHandle && handle <= lastRawHandle) {
				if (handle == NoRawHandle) return;
				if (rawHandles.contains(handle)) rawHandles.erase(handle);
			}
		}
	private:
		static inline std::unordered_map<int, std::shared_ptr<T>> handles;
		static inline std::unordered_map<int, T*> rawHandles;
		static inline std::atomic<int> lastHandle = Handles::NoHandle;
		static inline std::atomic<int> lastRawHandle = Handles::NoRawHandle;
	};

}

#endif
