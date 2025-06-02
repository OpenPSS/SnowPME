#ifndef LIB_PSS_PSMFILEHANDLE_H
#define LIB_PSS_PSMFILEHANDLE_H 1
#include <Sce/Pss/Core/Io/IUnderlying.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/Errorable.hpp>
#include <Sce/Pss/Core/PsmObject.hpp>
#include <iostream>
#include <mono/mono.h>


namespace Sce::Pss::Core::Io {
	class PsmFileHandle : public PsmObject<PsmFileHandle> {
	private:
		ScePssFileOpenFlag_t flags;

		std::string pathInSandbox = "";
		std::string pathOnDisk = "";

		IUnderlying* underlying = nullptr;


		void signalClosed();
	public:
		bool IsOpen();
		bool IsDirectory();
		bool IsEncrypted();
		bool IsRewritable();


		std::string PathInSandbox();
		std::string PathOnDisk();

		ScePssFileOpenFlag_t PssFlags();
		std::ios_base::openmode OpenMode();

		IUnderlying* GetUnderlying();
		int SetUnderyling(IUnderlying* edataStream);

		PsmFileHandle(std::string pathInSandbox, std::string pathOnDisk, ScePssFileOpenFlag_t flags);
		PsmFileHandle(std::string pathInSandbox, std::string pathOnDisk, ScePssFileOpenFlag_t flags, IUnderlying* underlying);

		~PsmFileHandle();
	};
}

#endif