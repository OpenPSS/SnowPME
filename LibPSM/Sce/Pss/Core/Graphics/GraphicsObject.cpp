#include <Sce/Pss/Core/Graphics/GraphicsObject.hpp>
#include <Sce/Pss/Core/Handles.hpp>

namespace Sce::Pss::Core::Graphics {

	GraphicsObject::GraphicsObject() {
		this->handle = Handles::CreateHandle((uintptr_t)this);
	}
	GraphicsObject::~GraphicsObject() {
		Handles::DeleteHandle(this->Handle());
		this->handle = NULL;
	}

	PsmHandle GraphicsObject::Handle() {
		return this->handle;
	}

	void GraphicsObject::Release(GraphicsObject* object)
	{
		object->Update = false;
	}
}