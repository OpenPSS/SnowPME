#include <Sce/Pss/Core/Mono/MonoUtil.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <cstring>

#include <mono/mono.h>

namespace Sce::Pss::Core::Mono {


	size_t MonoUtil::MonoArrayBytesLength(MonoArray* ar) {
		if (ar == nullptr) return 0;

		MonoClass* cls = mono_object_get_class(reinterpret_cast<MonoObject*>(ar));
		if (cls == nullptr) return 0;

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
		
		if (fields == nullptr)
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
				return true;
		}

		return false;
	}
	int MonoUtil::MonoStringToStdString(MonoString* mstr, std::string& string) {
		if (!mstr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;
		char* str = mono_string_to_utf8(mstr);
		if (str != nullptr) {
			string = std::string(str);
			mono_free(str);
			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_OUT_OF_MEMORY;
	}

	MonoString* MonoUtil::StdStringToMonoString(const std::string& str) {
		MonoDomain* domain = mono_domain_get();
		if (domain != nullptr) {
			MonoString* monoStr = mono_string_new_len(domain, str.c_str(), str.length());
			return monoStr;
		}
		return nullptr;
	}

	MonoAssembly* MonoUtil::MonoAssemblyOpenFull(MonoDomain* domain, const char* exePath) {
		if (strlen(exePath) == 0)
			return mono_domain_assembly_open(domain, exePath);

		// check if any invalid characters in the string
		for (size_t i = 0; i < strlen(exePath); ++i) if (exePath[i] < ' ' || exePath[i] > '~') return nullptr;

		return mono_domain_assembly_open(domain, exePath);
	}

	MonoType* MonoUtil::MonoArrayElementsType(MonoArray* ar) {
		if (ar == nullptr)
			return nullptr;

		MonoClass* cls = mono_object_get_class(reinterpret_cast<MonoObject*>(ar));

		if (cls == nullptr)
			return nullptr;

		MonoClass* elmClass = mono_class_get_element_class(cls);

		if (elmClass == nullptr)
			return nullptr;

		MonoType* type = mono_class_get_type(elmClass);
		
		if (type == nullptr)
			return nullptr;

		return type;
	}

}