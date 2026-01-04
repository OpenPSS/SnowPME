#ifndef LIB_PSS_HANDLES_H
#define LIB_PSS_HANDLES_H 1
#include <cstddef>
#include <cstdint>
#include <memory>

#include <unordered_map>
#include <LibShared.hpp>

namespace Sce::Pss::Core::System {
	template<typename T> class Handles {
	private:
		static std::unordered_map<int, std::shared_ptr<T>> handles;
		static std::unordered_map<int, T*> rawHandles;
		static std::atomic<int> lastHandle;
		static std::atomic<int> lastRawHandle;

	public:
		static const int NoHandle = 0x0;
		static const int NoRawHandle = 0xFFFF;

		static bool IsValid(uint64_t handle) {
			return Handles::IsValid(static_cast<int>(handle));
		}

		static bool IsValid(int handle) {
			if (handle <= Handles::NoHandle) return false;
			if (rawHandles.contains(handle)) return true;
			else return handles.contains(handle);
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

		static std::shared_ptr<T> Get(uint64_t handle) {
			return Handles<T>::Get(static_cast<int>(handle));
		}

		static std::shared_ptr<T> Get(int handle) {
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

		static void Delete(int handle) {
			if (rawHandles.contains(handle)) rawHandles.erase(handle);
			if (handles.contains(handle)) handles.erase(handle);
		}
	};

	template<typename T> std::unordered_map<int, std::shared_ptr<T>> Handles<T>::handles;
	template<typename T> std::unordered_map<int, T*> Handles<T>::rawHandles;
	template<typename T> std::atomic<int> Handles<T>::lastHandle = Handles::NoHandle;
	template<typename T> std::atomic<int> Handles<T>::lastRawHandle = Handles::NoRawHandle;
}

#endif
