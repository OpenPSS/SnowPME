#ifndef LIB_PSS_IUNDERLYINGL_H
#define LIB_PSS_IUNDERLYINGL_H 1
#include <cstdint>
#include <Sce/Pss/Core/Errorable.hpp>

namespace Sce::Pss::Core::Io {
	class IUnderlying : public Errorable {
		protected:
		public:
			IUnderlying() = default;
			~IUnderlying() = default;
			virtual uint64_t Tell() = 0;
			virtual void Close() = 0;
			virtual uint32_t Read(void* buffer, uint32_t length) = 0;

			virtual bool IsDirectory() = 0;
			virtual bool IsEncrypted() = 0;
			virtual bool IsOpen() = 0;

	};
}

#endif