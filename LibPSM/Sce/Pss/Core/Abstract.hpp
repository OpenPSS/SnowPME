#ifndef LIB_PSM_ABSTRACT_H
#define LIB_PSM_ABSTRACT_H 1
#include <LibShared.hpp>

#include <Sce/Pss/Core/Errorable.hpp>
#include <Sce/PlayStation/Core/Error.hpp>

namespace Sce::Pss::Core {

	#define DefineAbstract(x) \
	x { \
		Shared::Debug::Logger::Error("Abstract function: " + std::string(__FUNCTION__) + " was called."); \
		this->SetError(PSM_ERROR_NOT_IMPLEMENTED); \
		return PSM_ERROR_NOT_IMPLEMENTED; \
	}

	class Abstract : public Errorable
	{

	};
}
#endif