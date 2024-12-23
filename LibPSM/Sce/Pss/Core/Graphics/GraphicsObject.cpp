#include <Sce/Pss/Core/Graphics/GraphicsObject.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>

namespace Sce::Pss::Core::Graphics {
	using namespace Sce::Pss::Core::System;

	GraphicsObject::GraphicsObject() {
		this->GLReference = NULL;
	}
	GraphicsObject::~GraphicsObject() {
	}

	void GraphicsObject::Release(GraphicsObject* object)
	{
		object->Active = false;
	}
}