#ifndef LIB_PSM_GRAPHICSOBJECT_H
#define LIB_PSM_GRAPHICSOBJECT_H 1
#include <string>
#include <vector>
#include <Sce/Pss/Core/Handles.hpp>
#include <Sce/Pss/Core/Errorable.hpp>

namespace Sce::Pss::Core::Graphics {
	class GraphicsObject : public Errorable {
	private:
		PsmHandle handle;
	protected:
		uint32_t glReference;
	public:
		virtual int ActiveStateChanged(bool state) = NULL;
		bool Active = false;
		static void Release(GraphicsObject* object);

		uint32_t GlReference();
		PsmHandle Handle();
		GraphicsObject();
		~GraphicsObject();
	};
}
#endif