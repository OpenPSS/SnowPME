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
	public:
		bool Update = false;
		static void Release(GraphicsObject* object);


		PsmHandle Handle();
		GraphicsObject();
		~GraphicsObject();
	};
}
#endif