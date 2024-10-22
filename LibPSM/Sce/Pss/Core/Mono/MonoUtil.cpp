#include <Sce/Pss/Core/Mono/MonoUtil.hpp>
#include <mono/mono.h>

namespace Sce::Pss::Core::Mono {

	size_t MonoUtil::MonoArrayLength(MonoArray* ar) {
		if (ar == nullptr)
			return NULL;

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
	std::string* MonoUtil::MonoStringToStdString(MonoString* mstr, std::string& string) {
		if (!mstr)
			return &string;
		char* str = mono_string_to_utf8(mstr);
		if (str != nullptr) {
			string = std::string(str);
			mono_free(str);
		}
		return &string;
	}

	MonoString* MonoUtil::StdStringToMonoString(const std::string& str) {
		MonoDomain* domain = mono_domain_get();
		MonoString* monoStr = mono_string_new_len(domain, str.c_str(), str.length());
		return monoStr;
	}

	MonoAssembly* MonoUtil::MonoAssemblyOpenFull(MonoDomain* domain, const char* exePath) {
		if (strlen(exePath) == 0)
			return mono_domain_assembly_open(domain, exePath);

		// TODO:
		// figure out why does psm.exe do this ???
		// is this filtering out special characters or something?
		int i = 0;
		while ((exePath[i] - 0x20) <= 0x5E)
		{
			if (++i >= strlen(exePath)) {
				return mono_domain_assembly_open(domain, exePath);
			}
		}

		return nullptr;
	}

	MonoType* MonoUtil::MonoArrayElementsType(MonoArray* ar) {
		if (ar == nullptr)
			return NULL;

		MonoClass* cls = mono_object_get_class((MonoObject*)ar);

		if (cls == nullptr)
			return NULL;

		MonoClass* elmClass = mono_class_get_element_class(cls);

		if (elmClass == nullptr)
			return NULL;

		MonoType* type = mono_class_get_type(elmClass);
		
		if (type == nullptr)
			return NULL;

		return type;
	}

}