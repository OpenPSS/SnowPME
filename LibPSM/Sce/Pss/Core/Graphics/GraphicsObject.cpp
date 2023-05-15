#include <Sce/Pss/Core/Graphics/GraphicsObject.hpp>
#include <Sce/Pss/Core/Handles.hpp>

namespace Sce::Pss::Core::Graphics {

	GraphicsObject::GraphicsObject() {
		this->glReference = NULL;
		this->handle = Handles::CreateHandle((uintptr_t)this);
	}
	GraphicsObject::~GraphicsObject() {
		Handles::DeleteHandle(this->Handle());
		this->handle = NULL;
	}

	PsmHandle GraphicsObject::Handle() {
		return this->handle;
	}

	uint32_t GraphicsObject::GlReference() {
		return this->glReference;
	}

	void GraphicsObject::Release(GraphicsObject* object)
	{
		object->Update = false;
	}
}