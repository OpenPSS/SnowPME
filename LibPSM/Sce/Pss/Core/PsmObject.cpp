#include <Sce/Pss/Core/PsmObject.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>


namespace Sce::Pss::Core {
	using Sce::Pss::Core::System::Handles;

	PsmObject::PsmObject() {
		this->Handle = Handles::Create(this);
	}

	PsmObject::~PsmObject() {
		this->Dispose();
	}

	void PsmObject::Dispose() {
		this->IsDisposed = true;
		if (Handles::IsValid(this->Handle))
			Handles::Delete(this->Handle);
		this->Handle = Handles::NoHandle;
	}
}