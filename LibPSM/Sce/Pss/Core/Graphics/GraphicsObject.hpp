#ifndef LIB_PSS_GRAPHICSOBJECT_H
#define LIB_PSS_GRAPHICSOBJECT_H 1
#include <string>
#include <vector>

#include <Sce/Pss/Core/Handles.hpp>
#include <Sce/Pss/Core/Errorable.hpp>

namespace Sce::Pss::Core::Graphics {
	class GraphicsObject : public Errorable {
	private:
	public:
		virtual int ActiveStateChanged(bool state) = NULL;
		bool Active = false;
		static void Release(GraphicsObject* object);

		PsmHandle Handle;
		uint32_t GLReference;

		GraphicsObject();
		~GraphicsObject();
	};
}
#endif