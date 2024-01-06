#include <Sce/Pss/Core/System/Handles.hpp>
#include <Sce/Pss/Core/Error.hpp>
namespace Sce::Pss::Core::System {
	static uintptr_t addresses[Handles::MaxHandle];
	static bool wasInit = false;

	void Handles::init() {
		memset(addresses, NULL, sizeof(addresses));
		wasInit = true;
	}

	bool Handles::IsValid(int handle) {
		if (!wasInit)
			init();

		if (handle > Handles::MaxHandle)
			return false;
		else if (handle < Handles::MinHandle)
			return false;
		else if (handle == Handles::NoHandle)
			return false;
		else if (addresses[handle] == NULL)
			return false;
		else
			return true;
	}

	int Handles::CreateHandle(uintptr_t address) {
		if (!wasInit)
			init();

		for (int i = Handles::MinHandle; i < Handles::MaxHandle; i++) {
			if (addresses[i] == NULL)
			{
				addresses[i] = address;
				return i;
			}
		}

		return PSM_ERROR_BUFFER_FULL;
	}

	uintptr_t Handles::GetHandle(int handle) {
		if (!wasInit)
			init();

		if (!IsValid(handle))
			return NULL;
		else 
			return addresses[handle];
	}

	void Handles::DeleteHandle(int handle) {
		if (!wasInit)
			init();

		if (!IsValid(handle))
			return;

		addresses[handle] = NULL;
	}


}