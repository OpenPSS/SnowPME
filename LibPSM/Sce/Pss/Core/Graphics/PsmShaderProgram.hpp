#ifndef LIB_PSS_PSMSHADERPROGRAM_H
#define LIB_PSS_PSMSHADERPROGRAM_H 1
#include <cstdint>

#include <string>
#include <iostream>
#include <vector>

#include <mono/mono.h>

#include <Sce/Pss/Core/Graphics/ShaderUniformType.hpp>
#include <Sce/Pss/Core/Graphics/ShaderAttributeType.hpp>
#include <Sce/Pss/Core/Vector2.hpp>
#include <Sce/Pss/Core/Vector3.hpp>
#include <Sce/Pss/Core/Vector4.hpp>
#include <Sce/Pss/Core/Matrix4.hpp>


namespace Sce::Pss::Core::Graphics {
	using namespace Sce::Pss::Core;

	class PsmShaderProgram {
	public:
		static int FromFile(MonoString* vpFileName, MonoString* fpFileName, MonoString*  constKeys, int* constVals, int* result);
		static int FromImage(MonoArray* vpFileImage, MonoArray* fpFileImage, MonoArray* constKeys, int* constVals, int* result);
		static int Delete(int handle);
		static int AddRef(int handle);
		static int GetUniformCount(int handle, int *result);
		static int GetAttributeCount(int handle, int *result);
		static int FindUniform(int handle, MonoString* name, int *result);
		static int FindAttribute(int handle, MonoString* name, int *result);
		static int GetUniformBinding(int handle, int index, MonoString* result);
		static int SetUniformBinding(int handle, int index, MonoString* name);
		static int GetAttributeBinding(int handle, int index, MonoString* result);
		static int SetAttributeBinding(int handle, int index, MonoString* name);
		static int GetUniformType(int handle, int index, ShaderUniformType *result);
		static int GetAttributeType(int handle, int index, ShaderAttributeType *result);
		static int GetUniformName(int handle, int index, MonoString* result);
		static int GetAttributeName(int handle, int index, MonoString* result);
		static int GetUniformSize(int handle, int index, int *result);
		static int GetAttributeSize(int handle, int index, int *result);
		static int SetUniformValue(int handle, int index, int offset, void *value, ShaderUniformType type);
		static int SetUniformValue2(int handle, int index, void *value, ShaderUniformType type, int to, int from, int count);
		static int SetAttributeValue2(int handle, int index, float *value);
		static int GetUniformTexture(int handle, int index, int *result);
		static int GetAttributeStream(int handle, int index, int *result);
		static int SetAttributeStream(int handle, int index, int stream);
	};
}
#endif
