#ifndef LIB_PSS_PSM_OBJECT_H
#define LIB_PSS_PSM_OBJECT_H 1
#include <Sce/Pss/Core/Errorable.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>

namespace Sce::Pss::Core {
	using Sce::Pss::Core::System::Handles;

	template<typename T> class PsmObject : public Errorable {
	private:
	public:
		PsmObject() {
			this->Handle = Handles::Create(static_cast<T*>(this));
		};
		~PsmObject() {
			this->Dispose();
		};
		void Dispose() {
			this->IsDisposed = true;
			if (Handles::IsValid(this->Handle))
				Handles::Delete(this->Handle);
			this->Handle = Handles::NoHandle;
		};
		bool IsDisposed = false;
		int Handle = System::Handles::NoHandle;
	};
}

#endif