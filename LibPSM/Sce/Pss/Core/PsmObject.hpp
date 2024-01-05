#ifndef LIB_PSS_PSM_OBJECT_H
#define LIB_PSS_PSM_OBJECT_H 1
#include <Sce/Pss/Core/Errorable.hpp>
#include <Sce/Pss/Core/Error.hpp>

namespace Sce::Pss::Core {
	class PsmObject : public Errorable {
	public:
		PsmObject();
		~PsmObject();
	};
}

#endif