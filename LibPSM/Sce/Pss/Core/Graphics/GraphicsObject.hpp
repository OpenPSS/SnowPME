#ifndef LIB_PSS_GRAPHICSOBJECT_H
#define LIB_PSS_GRAPHICSOBJECT_H 1
#include <string>
#include <vector>
#include <Sce/Pss/Core/PsmObject.hpp>
#include <Sce/Pss/Core/Errorable.hpp>

namespace Sce::Pss::Core::Graphics {
	class GraphicsObject : public PsmObject {
	private:
	public:
		virtual int ActiveStateChanged(bool state) = 0;
		bool Active = false;
		static void Release(GraphicsObject* object);
		uint32_t GLReference;

		GraphicsObject();
		~GraphicsObject();
	};
}
#endif
