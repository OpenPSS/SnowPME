#include <Sce/Pss/Core/Mono/Resources.hpp>
#include <mono/mono.h>
#include <LibShared.hpp>


namespace Sce::Pss::Core::Mono {
	using namespace Shared::Debug;

	void Resources::ResourceLimitReachedCallback(int resourceType, uintptr_t value, int isSoft) {
		if (resourceType < MONO_RESOURCE_JIT_CODE || resourceType <= MONO_RESOURCE_GC_HEAP || resourceType != MONO_RESOURCE_GC_HEAP) {
			if (resourceType <= MONO_RESOURCE_METADATA)
				Logger::Error("resource exhausted(type: " + std::to_string(resourceType) + "value : " + std::to_string(value) + "soft : " + std::to_string(isSoft));

		}
	}
	void Resources::ThreadsExhaustedCallback() {
		Logger::Error("threads exhausted!");
		mono_gc_out_of_memory(0);
	}
}