#include <Util/MonoUtil.hpp>
#include <mono/mono.h>

namespace SnowPME::Util {

	size_t MonoUtil::MonoArrayLength(MonoArray* ar) {
		if (ar == NULL)
			return 0;

		MonoClass* cls = mono_object_get_class((MonoObject*)ar);
		size_t elmSize = mono_array_element_size(cls);
		return mono_array_length(ar) * elmSize;
	}

	bool MonoUtil::MonoTypeIsValueType(MonoType* type) {

		int typeEnum = mono_type_get_type(type);
		
		if (typeEnum <= MONO_TYPE_R8)
			return true;
		
		if (typeEnum != MONO_TYPE_VALUETYPE)
			return false;

		MonoClass* typeClass = mono_type_get_class(type);

		void* iter = 0;
		MonoClassField* fields = mono_class_get_fields(typeClass, &iter);
		
		if (fields == NULL)
			return true;

		while (true)
		{
			if ((mono_field_get_flags(fields) & FIELD_ATTRIBUTE_STATIC) == 0)
			{
				MonoType* fieldType = mono_field_get_type(fields);
				if (!MonoUtil::MonoTypeIsValueType(fieldType))
					break;
			}
			fields = mono_class_get_fields(typeClass, &iter);
			if (!fields)
				return 1;
		}
	}

	MonoType* MonoUtil::MonoArrayElementsType(MonoArray* ar) {
		if (ar == NULL)
			return 0;

		MonoClass* cls = mono_object_get_class((MonoObject*)ar);

		if (cls == NULL)
			return 0;

		MonoClass* elmClass = mono_class_get_element_class(cls);

		if (elmClass == NULL)
			return 0;

		MonoType* type = mono_class_get_type(elmClass);
		
		if (type == NULL)
			return 0;

		return type;
	}

}