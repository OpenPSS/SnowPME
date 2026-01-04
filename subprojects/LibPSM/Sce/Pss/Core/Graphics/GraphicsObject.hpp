#ifndef LIB_PSS_GRAPHICSOBJECT_H
#define LIB_PSS_GRAPHICSOBJECT_H 1
#include <string>
#include <vector>
#include <atomic>
#include <Sce/Pss/Core/Errorable.hpp>
#include <Sce/Pss/Core/PsmMutexObject.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>

#include <glad/glad.h>

namespace Sce::Pss::Core::Graphics {
	template<typename T> class GraphicsObject : public PsmMutexObject<T>, public Errorable {
		template<typename U> friend class GraphicsObject;

	protected:
		std::atomic<size_t> totalReferences = 0;
		int handle = Sce::Pss::Core::System::Handles<T>::NoHandle;

		GraphicsObject() = default;
		virtual ~GraphicsObject() = default;

	public:
		template <typename... Args, typename = T> static T* Create(Args&&... args) {
			T* obj = new T(std::forward<Args>(args)...);
			obj->handle = Sce::Pss::Core::System::Handles<T>::Create(obj);
			return obj;
		}

		static T* Create(T* obj) {
			obj->handle = Sce::Pss::Core::System::Handles<T>::Create(obj);
			return obj;
		}

		virtual int ActiveStateChanged() {
			return PSM_ERROR_NO_ERROR;
		};

		static bool AddRef(int handle) {
			if (Sce::Pss::Core::System::Handles<T>::IsValid(handle)) {
				T* object = Sce::Pss::Core::System::Handles<T>::GetRaw(handle);

				object->totalReferences++;
				return true;
			}

			return false;
		}

		static bool Release(int handle) {
			if (Sce::Pss::Core::System::Handles<T>::IsValid(handle)) {
				T* object = Sce::Pss::Core::System::Handles<T>::GetRaw(handle);
				return T::Release(object);
			}

			return false;
		}

		static bool Release(T* object) {
			if (object != nullptr) {
				object->totalReferences--;
				if (object->TotalReferences() >= 0)
					return false;

				object->ActiveStateChanged();

				Sce::Pss::Core::System::Handles<T>::Delete(object->Handle());
				delete object;
				return true;
			}

			return false;
		}

		size_t TotalReferences() {
			return this->totalReferences;
		}

		int Handle() {
			return this->handle;
		}

		bool Active;
		GLenum GLHandle;

		void* operator new(size_t size) {
			Logger::Debug("Allocating: " + std::to_string(size) + " // " + typeid(T).name());
			std::shared_ptr<Sce::Pss::Core::Memory::HeapAllocator> alloc = Sce::Pss::Core::Memory::HeapAllocator::UniqueObject();
			return alloc->sce_psm_malloc(size);
		}

		void operator delete(void* ptr) {
			Logger::Debug("Freeing: " + std::to_string(reinterpret_cast<uintptr_t>(ptr)) + " // " + typeid(T).name());
			std::shared_ptr<Sce::Pss::Core::Memory::HeapAllocator> alloc = Sce::Pss::Core::Memory::HeapAllocator::UniqueObject();
			alloc->sce_psm_free(ptr);
		}

	};

};
#endif
