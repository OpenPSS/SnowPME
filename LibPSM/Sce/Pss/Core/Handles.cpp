#include <Sce/Pss/Core/Handles.hpp>
#include <Sce/PlayStation/Core/Error.hpp>
#include <map>
namespace Sce::Pss::Core {
	static uintptr_t addresses[MAX_HANDLES];
	static bool wasInit = false;

	void Handles::init() {
		memset(addresses, NULL, sizeof(addresses));
		wasInit = true;
	}

	bool Handles::IsValid(PsmHandle handle) {
		if (handle > MAX_HANDLES)
			return false;
		else if (handle < 0)
			return false;
		else
			return true;
	}

	PsmHandle Handles::CreateHandle(uintptr_t address) {
		if (!wasInit)
			init();

		for (PsmHandle i = 0; i < MAX_HANDLES; i++) {
			if (addresses[i] == NULL)
			{
				addresses[i] = address;
				return i;
			}
		}

		return PSM_ERROR_BUFFER_FULL;
	}

	uintptr_t Handles::GetHandle(PsmHandle handle) {
		if (!wasInit)
			init();

		if (!IsValid(handle))
			return NULL;
		else 
			return addresses[handle];
	}

	void Handles::DeleteHandle(PsmHandle handle) {
		if (!wasInit)
			init();

		if (!IsValid(handle))
			return;

		addresses[handle] = NULL;
	}


}