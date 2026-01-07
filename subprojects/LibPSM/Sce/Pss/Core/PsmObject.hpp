#ifndef LIB_PSS_PSM_OBJECT_H
#define LIB_PSS_PSM_OBJECT_H 1
#include <Sce/Pss/Core/Errorable.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
#include <Sce/Pss/Core/PsmMutexObject.hpp>
#include <Sce/Pss/Core/PsmUniqueObject.hpp>
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <LibShared.hpp>

#include <mutex>
#include <memory>
#include <utility>
#include <cstdint>

#define TO_BITS(x) ((x) * 8);
#define TO_BYTES(x) ((x) / 8);

namespace Sce::Pss::Core {

	template<typename T> class PsmObject : public Errorable, public PsmMutexObject<PsmObject<T>> {
		template<typename U> friend class PsmObject;

	protected:
		int handle = Sce::Pss::Core::System::Handles<T>::NoHandle;
		PsmObject() = default;
		~PsmObject() {
			this->handle = Sce::Pss::Core::System::Handles<T>::NoHandle;
		};
		
	public:
		
		template <typename... Args, typename = T> static std::shared_ptr<T> Create(Args&&... args) {
			std::shared_ptr<T> obj = std::make_shared<T>(std::forward<Args>(args)...);
			obj->handle = Sce::Pss::Core::System::Handles<T>::Create(obj);
			return obj;
		}

		static std::shared_ptr<T> Create(std::shared_ptr<T> obj) {
			std::reinterpret_pointer_cast<T>(obj)->handle = Sce::Pss::Core::System::Handles<T>::Create(obj);
			return obj;
		}

		static void Delete(std::shared_ptr<T> obj) {
			if (CheckHandle(obj->Handle()))
				Sce::Pss::Core::System::Handles<T>::Delete(obj->Handle());
			obj = nullptr;
		}
		
		int Handle() {
			return this->handle;
		}

		static std::shared_ptr<T> LookupHandle(uint64_t handle) {
			return T::LookupHandle(static_cast<int>(handle));
		}

		static std::shared_ptr<T> LookupHandle(int handle) {
			return Sce::Pss::Core::System::Handles<T>::Get(handle);
		}

		static bool CheckHandle(uint64_t handle) {
			return T::CheckHandle(static_cast<int>(handle));
		}

		static bool CheckHandle(int handle) {
			return Sce::Pss::Core::System::Handles<T>::IsValid(handle);
		}

		CUSTOM_ALLOC();

	};

}

#endif