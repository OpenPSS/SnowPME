#include <Util/MonoUtil.hpp>

namespace SnowPME::Util {

	size_t MonoUtil::MonoArrayLength(MonoArray* ar) {
		if (ar == NULL)
			return 0;

		MonoClass* cls = mono_object_get_class((MonoObject*)ar);
		size_t elmSize = mono_array_element_size(cls);
		return elmSize * mono_array_length(ar);
	}

}