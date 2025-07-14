#ifndef LIB_PSS_ERRORABLE_H
#define LIB_PSS_ERRORABLE_H 1
#include <vector>
#include <string>

#include <LibShared.hpp>
#include <Sce/Pss/Core/ExceptionInfo.hpp>
#include <Sce/Pss/Core/Error.hpp>

#define PRINT_ERR(error) \
		do { \
			Shared::Debug::Logger::Error(std::string(__FUNCTION__) + " returned error: " + Shared::String::Format::Hex(error)); \
		} while(0)

#define RETURN_ERRORABLE_SMARTPTR(x) \
		if(x->GetError() != PSM_ERROR_NO_ERROR) { \
			int error = x->GetError(); \
			PRINT_ERR(error); \
			x = nullptr; \
			return error; \
		}

#define RETURN_ERRORABLE_GRAPHICSOBJECT(x, t) \
		if(x->GetError() != PSM_ERROR_NO_ERROR) { \
			int error = x->GetError(); \
			PRINT_ERR(error); \
			t::Release(x); \
			x = nullptr; \
			return error; \
		}

#define RETURN_ERRORABLE_PSMOBJECT(x, t) \
		if(x->GetError() != PSM_ERROR_NO_ERROR) { \
			int error = x->GetError(); \
			PRINT_ERR(error); \
			t::Delete(x); \
			x = nullptr; \
			return error; \
		}

#define RETURN_ERRORABLE(x) \
		if(x->GetError() != PSM_ERROR_NO_ERROR) { \
			int error = x->GetError(); \
			PRINT_ERR(error); \
			delete x; \
			x = nullptr; \
			return error; \
		}

#define PASS_ERRORABLE(x) \
		if(x->GetError() != PSM_ERROR_NO_ERROR) { \
			int error = x->GetError(); \
			this->SetError(error); \
			PRINT_ERR(error); \
			delete x; \
			x = nullptr; \
			return PSM_ERROR_NO_ERROR; \
		} 

#define RETURN_ERRORABLE_AS_BOOL(x) \
		if(x->GetError() != PSM_ERROR_NO_ERROR) { \
			int error = x->GetError(); \
			PRINT_ERR(error); \
			delete x; \
			x = nullptr; \
			return false; \
		}

#define SET_ERROR_AND_RETURN(x) \
		do { \
			this->SetError(x); \
			return; \
		} while(0)




namespace Sce::Pss::Core {

	class Errorable {
	private:
		std::atomic<uint32_t> lastError = PSM_ERROR_NO_ERROR;
	public:
		Errorable() = default;
		~Errorable() = default;
		uint32_t GetClearError();
		uint32_t SetError(uint32_t errorCode);
		uint32_t GetError();
	};
}

#endif