#ifndef LIB_PSM_PSMSHADERPROGRAM_H
#define LIB_PSM_PSMSHADERPROGRAM_H 1
#include <cstdint>

#include <string>
#include <iostream>
#include <vector>

#include <mono/mono.h>

#include <Sce/PlayStation/Core/Graphics/ShaderUniformType.hpp>
#include <Sce/PlayStation/Core/Graphics/ShaderAttributeType.hpp>
#include <Sce/PlayStation/Core/Vector2.hpp>
#include <Sce/PlayStation/Core/Vector3.hpp>
#include <Sce/PlayStation/Core/Vector4.hpp>
#include <Sce/PlayStation/Core/Matrix4.hpp>
using namespace Sce::PlayStation::Core;


namespace Sce::PlayStation::Core::Graphics {
	class PsmShaderProgram {
	public:
		static int FromFile(MonoString* vpFileName, MonoString* fpFileName, MonoString*  constKeys, int* constVals, int* result);
		static int FromImage(MonoArray* vpFileName, MonoArray* fpFileImage, MonoArray* constKeys, int* constVals, int* result);
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
		static int SetUniformValueMatrix4(int handle, int index, int, Matrix4 *value, ShaderUniformType type);
		static int SetUniformValueVector4(int handle, int index, int, Vector4 *value, ShaderUniformType type);
		static int SetUniformValueVector3(int handle, int index, int, Vector3 *value, ShaderUniformType type);
		static int SetUniformValueVector2(int handle, int index, int, Vector2 *value, ShaderUniformType type);
		static int SetUniformValueFloat(int handle, int index, int, float *value, ShaderUniformType type);
		static int SetUniformValueInt(int handle, int index, int, int *value, ShaderUniformType type);
		static int SetUniformValue2Matrix4(int handle, int index, Matrix4 *value, ShaderUniformType type, int to, int from, int count);
		static int SetUniformValue2Vector4(int handle, int index, Vector4 *value, ShaderUniformType type, int to, int from, int count);
		static int SetUniformValue2Vector3(int handle, int index, Vector3 *value, ShaderUniformType type, int to, int from, int count);
		static int SetUniformValue2Vector2(int handle, int index, Vector2 *value, ShaderUniformType type, int to, int from, int count);
		static int SetUniformValue2Float(int handle, int index, float *value, ShaderUniformType type, int to, int from, int count);
		static int SetUniformValue2Int(int handle, int index, int *value, ShaderUniformType type, int to, int from, int count);
		static int SetAttributeValue2(int handle, int index, float *value);
		static int GetUniformTexture(int handle, int index, int *result);
		static int GetAttributeStream(int handle, int index, int *result);
		static int SetAttributeStream(int handle, int index, int stream);
	};
}
#endif
