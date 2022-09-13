#ifndef LIB_PSM_PSMSHADERPROGRAM_H
#define LIB_PSM_PSMSHADERPROGRAM_H 1
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "ShaderUniformType.hpp"
#include "ShaderAttributeType.hpp"
#include "../Vector2.hpp"
#include "../Vector3.hpp"
#include "../Vector4.hpp"
#include "../Matrix4.hpp"

using namespace Sce::PlayStation::Core;
using namespace std;

namespace Sce::PlayStation::Core::Graphics {
	class PsmShaderProgram {
	public:
		static int FromFile(string vpFileName, string fpFileName, string* constKeys, int* constVals, int* result);
		static int FromImage(byte* vpFileName, byte* fpFileImage, string* constKeys, int* constVals, int* result);
		static int Delete(int handle);
		static int AddRef(int handle);
		static int GetUniformCount(int handle, int *result);
		static int GetAttributeCount(int handle, int *result);
		static int FindUniform(int handle, string name, int *result);
		static int FindAttribute(int handle, string name, int *result);
		static int GetUniformBinding(int handle, int index, string *result);
		static int SetUniformBinding(int handle, int index, string name);
		static int GetAttributeBinding(int handle, int index, string *result);
		static int SetAttributeBinding(int handle, int index, string name);
		static int GetUniformType(int handle, int index, ShaderUniformType *result);
		static int GetAttributeType(int handle, int index, ShaderAttributeType *result);
		static int GetUniformName(int handle, int index, string *result);
		static int GetAttributeName(int handle, int index, string *result);
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
