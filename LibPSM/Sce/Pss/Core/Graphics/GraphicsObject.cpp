#include <Sce/Pss/Core/Graphics/GraphicsObject.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
using namespace Sce::Pss::Core::System;

namespace Sce::Pss::Core::Graphics {

	GraphicsObject::GraphicsObject() {
		this->GLReference = NULL;
		this->Handle = Handles::CreateHandle((uintptr_t)this);
	}
	GraphicsObject::~GraphicsObject() {
		Handles::DeleteHandle(this->Handle);
		this->Handle = NULL;
	}

	void GraphicsObject::Release(GraphicsObject* object)
	{
		object->Active = false;
	}
}