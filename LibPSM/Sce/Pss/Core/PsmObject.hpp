#ifndef LIB_PSS_PSM_OBJECT_H
#define LIB_PSS_PSM_OBJECT_H 1
#include <Sce/Pss/Core/Errorable.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>

namespace Sce::Pss::Core {
	class PsmObject : public Errorable {
	private:
	public:
		PsmObject();
		~PsmObject();
		void Dispose();
		bool IsDisposed = false;
		int Handle = System::Handles::NoHandle;
	};
}

#endif