#include <Sce/Pss/Core/Graphics/GraphicsObject.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>

using namespace Sce::Pss::Core::System;
namespace Sce::Pss::Core::Graphics {


	void GraphicsObject::Release(GraphicsObject* object)
	{
		object->Active = false;
	}
}