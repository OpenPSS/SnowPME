#include "Resources.hpp"
#include <SnowPME/Mono.h>

namespace SnowPME::Mono {
	void Resources::ResourceLimitReachedCallback(int resourceType, uintptr_t value, int isSoft) {
		if (resourceType < MONO_RESOURCE_JIT_CODE || resourceType <= MONO_RESOURCE_GC_HEAP || resourceType != MONO_RESOURCE_GC_HEAP) {
			if (resourceType <= MONO_RESOURCE_METADATA)
				cout << "ERROR : resource exhausted (type: " << to_string(resourceType) << "value: " << to_string(value) << "soft: " << to_string(isSoft) << endl;

			// TODO: Make this exit the currently running program
			cout << "ABORT: Resources limit exceeded!" << endl;
		}
	}
	void Resources::ThreadsExhaustedCallback() {
		cout << "ERROR: threads exhausted!" << endl;
		mono_gc_out_of_memory(0);
	}
}