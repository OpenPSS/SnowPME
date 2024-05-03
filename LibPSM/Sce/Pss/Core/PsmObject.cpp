#include <Sce/Pss/Core/PsmObject.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>


namespace Sce::Pss::Core {
	using Sce::Pss::Core::System::Handles;

	PsmObject::PsmObject() {
		this->Handle = Handles::CreateHandle((uintptr_t)this);
	}

	PsmObject::~PsmObject() {
		this->Dispose();
	}

	void PsmObject::Dispose() {
		this->IsDisposed = true;
		if (Handles::IsValid(this->Handle))
			Handles::DeleteHandle(this->Handle);
		this->Handle = Handles::NoHandle;
	}
}