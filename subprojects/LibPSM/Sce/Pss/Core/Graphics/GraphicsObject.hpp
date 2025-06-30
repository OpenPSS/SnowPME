#ifndef LIB_PSS_GRAPHICSOBJECT_H
#define LIB_PSS_GRAPHICSOBJECT_H 1
#include <string>
#include <vector>
#include <Sce/Pss/Core/Errorable.hpp>
#include <Sce/Pss/Core/PsmMutexObject.hpp>

namespace Sce::Pss::Core::Graphics {
	class GraphicsObject {
	public:
		GraphicsObject() = default;
		~GraphicsObject() = default;
		virtual int ActiveStateChanged(bool state) = 0;
		bool Active = false;
		static void Release(GraphicsObject* object);
		uint32_t GLReference;
	};
}
#endif
