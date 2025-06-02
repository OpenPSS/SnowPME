#ifndef LIB_PSS_IUNDERLYINGL_H
#define LIB_PSS_IUNDERLYINGL_H 1
#include <cstdint>
#include <Sce/Pss/Core/PsmObject.hpp>

namespace Sce::Pss::Core::Io {
	class IUnderlying : public PsmObject<IUnderlying> {
		protected:
		public:
			IUnderlying() = default;
			~IUnderlying() = default;
			virtual uint64_t Tell() = NULL;
			virtual void Close() = NULL;
			virtual uint32_t Read(void* buffer, uint32_t length) = NULL;

			virtual bool IsDirectory() = NULL;
			virtual bool IsEncrypted() = NULL;
			virtual bool IsOpen() = NULL;

	};
}

#endif