#ifndef LIB_PSS_PSM_OBJECT_H
#define LIB_PSS_PSM_OBJECT_H 1
#include <Sce/Pss/Core/Errorable.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
#include <Sce/Pss/Core/PsmMutexObject.hpp>
#include <mutex>

namespace Sce::Pss::Core {
	template<typename T> class PsmObject : public Errorable, public PsmMutexObject<T> {
	public:
		PsmObject() {
			this->Handle = System::Handles::Create(static_cast<T*>(this));
		};
		~PsmObject() {
			this->Dispose();
		};
		void Dispose() {
			LOCK_GUARD();
			this->IsDisposed = true;
			if (System::Handles::IsValid(this->Handle))
				System::Handles::Delete(this->Handle);
			this->Handle = System::Handles::NoHandle;
		};

		bool IsDisposed = false;
		int Handle = System::Handles::NoHandle;

	};

}

#endif