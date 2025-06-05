#ifndef LIB_PSS_PSM_OBJECT_H
#define LIB_PSS_PSM_OBJECT_H 1
#include <Sce/Pss/Core/Errorable.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
#include <Sce/Pss/Core/PsmMutexObject.hpp>
#include <mutex>

namespace Sce::Pss::Core {
	template<typename T> class PsmObject : public Errorable, public PsmMutexObject<T> {
	private:
		void dispose() {
			LOCK_GUARD();
			this->IsDisposed = true;
			if (Sce::Pss::Core::System::Handles::IsValid(this->Handle))
				Sce::Pss::Core::System::Handles::Delete(this->Handle);
			this->Handle = Sce::Pss::Core::System::Handles::NoHandle;
		};

	public:
		PsmObject() {
			this->Handle = Sce::Pss::Core::System::Handles::Create(reinterpret_cast<T*>(this));
		};
		~PsmObject() {
			this->dispose();
		};

		bool IsDisposed = false;
		int Handle = Sce::Pss::Core::System::Handles::NoHandle;

	};

}

#endif