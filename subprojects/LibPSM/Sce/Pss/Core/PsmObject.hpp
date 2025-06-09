#ifndef LIB_PSS_PSM_OBJECT_H
#define LIB_PSS_PSM_OBJECT_H 1
#include <Sce/Pss/Core/Errorable.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
#include <Sce/Pss/Core/PsmMutexObject.hpp>
#include <mutex>
#include <memory>

namespace Sce::Pss::Core {
	template<typename T> class PsmObject : public std::enable_shared_from_this<T>, public Errorable, public PsmMutexObject<T> {
	private:
		int handle = Sce::Pss::Core::System::Handles::NoHandle;

	public:
		bool IsDisposed = false;
		~PsmObject() {
			LOCK_GUARD();
			this->IsDisposed = true;

			if (Sce::Pss::Core::System::Handles::IsValid(this->handle)) {
				Sce::Pss::Core::System::Handles::Delete(this->handle);
			}

			this->handle = Sce::Pss::Core::System::Handles::NoHandle;
		};

		int Handle() {
			if (!Sce::Pss::Core::System::Handles::IsValid(this->handle)) {
				this->handle = Sce::Pss::Core::System::Handles::Create(reinterpret_cast<T*>(this));
			}
			return this->handle;
		}
	};

}

#endif