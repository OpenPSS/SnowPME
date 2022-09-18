#include <Runtime/Resources.hpp>
#include <mono/mono.h>

namespace SnowPME::Runtime {
	void Resources::ResourceLimitReachedCallback(int resourceType, uintptr_t value, int isSoft) {
		if (resourceType < MONO_RESOURCE_JIT_CODE || resourceType <= MONO_RESOURCE_GC_HEAP || resourceType != MONO_RESOURCE_GC_HEAP) {
			if (resourceType <= MONO_RESOURCE_METADATA)
				std::cout << "ERROR : resource exhausted (type: " << std::to_string(resourceType) << "value: " << std::to_string(value) << "soft: " << std::to_string(isSoft) << std::endl;

		}
	}
	void Resources::ThreadsExhaustedCallback() {
		std::cout << "ERROR: threads exhausted!" << std::endl;
		mono_gc_out_of_memory(0);
	}
}