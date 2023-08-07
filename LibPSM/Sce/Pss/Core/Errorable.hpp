#ifndef LIB_PSS_ERRORABLE_H
#define LIB_PSS_ERRORABLE_H 1
#include <vector>
#include <string>
#include <Sce/PlayStation/Core/Error.hpp>

namespace Sce::Pss::Core {
	#define ReturnErrorable(x) \
		if(x->GetError() != PSM_ERROR_NO_ERROR) { \
			int error = x->GetError(); \
			delete x; \
			return error; \
		}

	#define PassErrorable(x) \
		if(x->GetError() != PSM_ERROR_NO_ERROR) { \
			int error = x->GetError(); \
			this->SetError(error); \
			delete x; \
			return PSM_ERROR_NO_ERROR; \
		} 

	class Errorable {
	private:
		uint32_t lastError = PSM_ERROR_NO_ERROR;
	public:
		Errorable();
		~Errorable();
		void SetError(uint32_t errorCode);
		uint32_t GetError();
	};
}

#endif