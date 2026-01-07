#ifndef LIB_PSS_GRAPHICSOBJECT_H
#define LIB_PSS_GRAPHICSOBJECT_H 1
#include <string>
#include <vector>
#include <atomic>
#include <Sce/Pss/Core/Errorable.hpp>
#include <Sce/Pss/Core/PsmMutexObject.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <Sce/Pss/Core/PsmRefCount.hpp>

#include <glad/glad.h>

namespace Sce::Pss::Core::Graphics {
	template<typename T> class GraphicsObject : public PsmRefCount<T> {
		template<typename U> friend class GraphicsObject;

	protected:
		GraphicsObject() = default;
		virtual ~GraphicsObject() = default;

	public:

		virtual int ActiveStateChanged() {
			return PSM_ERROR_NO_ERROR;
		};

		int Handle() {
			return this->handle;
		}

		bool Active;
		GLenum GLHandle;

		CUSTOM_ALLOC();

	};

};
#endif
