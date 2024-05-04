#include <Sce/Pss/Core/Mono/Util.hpp>
#include <mono/mono.h>

namespace Sce::Pss::Core::Mono {

	size_t Util::MonoArrayLength(MonoArray* ar) {
		if (ar == NULL)
			return 0;

		MonoClass* cls = mono_object_get_class((MonoObject*)ar);
		size_t elmSize = mono_array_element_size(cls);
		return mono_array_length(ar) * elmSize;
	}

	bool Util::MonoTypeIsValueType(MonoType* type) {

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
				if (!Util::MonoTypeIsValueType(fieldType))
					break;
			}
			fields = mono_class_get_fields(typeClass, &iter);
			if (!fields)
				return true;
		}

		return false;
	}
	std::string* Util::MonoStringToStdString(MonoString* mstr, std::string& string) {
		if (!mstr)
			return &string;
		char* str = mono_string_to_utf8(mstr);
		if (str != nullptr) {
			string = std::string(str);
			mono_free(str);
		}
		return &string;
	}

	MonoString* Util::StdStringToMonoString(const std::string& str) {
		MonoDomain* domain = mono_domain_get();
		MonoString* monoStr = mono_string_new_len(domain, str.c_str(), str.length());
		return monoStr;
	}

	MonoType* Util::MonoArrayElementsType(MonoArray* ar) {
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