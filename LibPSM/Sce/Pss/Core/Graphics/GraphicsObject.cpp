#include <Sce/Pss/Core/Graphics/GraphicsObject.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
using namespace Sce::Pss::Core::System;

namespace Sce::Pss::Core::Graphics {

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