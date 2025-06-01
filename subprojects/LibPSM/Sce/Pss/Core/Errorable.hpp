#ifndef LIB_PSS_ERRORABLE_H
#define LIB_PSS_ERRORABLE_H 1
#include <vector>
#include <string>
#include <LibShared.hpp>
#include <Sce/Pss/Core/ExceptionInfo.hpp>
#include <Sce/Pss/Core/Error.hpp>

#define ReturnErrorable(x) \
		if(x->GetError() != PSM_ERROR_NO_ERROR) { \
			int error = x->GetError(); \
			delete x; \
			x = nullptr; \
			return error; \
		}

#define PassErrorable(x) \
		if(x->GetError() != PSM_ERROR_NO_ERROR) { \
			int error = x->GetError(); \
			this->SetError(error); \
			delete x; \
			x = nullptr; \
			return PSM_ERROR_NO_ERROR; \
		} 

#define ReturnErrorableAsBool(x) \
		if(x->GetError() != PSM_ERROR_NO_ERROR) { \
			int error = x->GetError(); \
			delete x; \
			x = nullptr; \
			return false; \
		}

#define SetErrorAndReturn(x) \
		do { \
			this->SetError(x); \
			return; \
		} while(0)


#define ErrorableUnimplemented(msg) \
		do { \
			Sce::Pss::Core::ExceptionInfo::AddMessage(std::string(__FUNCTION__) + ":" + std::string(msg) + std::string(" is not yet implemented.\n")); \
			this->SetError(PSM_ERROR_NOT_IMPLEMENTED); \
			return; \
		} while (0)


namespace Sce::Pss::Core {

	class Errorable {
	private:
		uint32_t lastError = PSM_ERROR_NO_ERROR;
	public:
		Errorable();
		~Errorable();
		uint32_t SetError(uint32_t errorCode);
		uint32_t GetClearError();
		uint32_t GetError();
	};
}

#endif