#include "PsmShaderProgram.hpp"
#include "PsmGraphicsContext.hpp"
#include "../Error.hpp"
#include <iostream>
#include <string>
#include <LibSnowPME.hpp>
using namespace SnowPME::Debug;
using namespace SnowPME::Util;

namespace Sce::PlayStation::Core::Graphics {
	int PsmShaderProgram::FromFile(std::string vpFileName, std::string fpFileName, std::string* constKeys, int* constVals, int *result){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::FromImage(MonoArray* vpFileName, MonoArray* fpFileImage, MonoArray* constKeys, int* constVals, int *result){
		Logger::Debug(__FUNCTION__);
		if (CTX_CHECK) return PSM_ERROR_GRAPHICS_SYSTEM;
		if (THREAD_CHECK) {
			

			size_t nameLen = MonoUtil::MonoArrayLength(vpFileName);
			size_t imageLen = MonoUtil::MonoArrayLength(fpFileImage);
			char* fnameBuf = NULL;
			char* fimgBuf = NULL;

			if(vpFileName != NULL)
				fnameBuf = mono_array_addr_with_size(vpFileName, 1, 0);
			if(fpFileImage != NULL)
				fimgBuf = mono_array_addr_with_size(fpFileImage, 1, 0);

			std::string shaderFileName = "";
			std::string shaderSource = "";

			if(fnameBuf != NULL) 
				shaderFileName = std::string(fnameBuf, nameLen);
			if(fimgBuf != NULL)
				shaderSource = std::string(fimgBuf, imageLen);

			Logger::Debug("Program Name: " + shaderFileName+"\n\n");

			return PSM_ERROR_NO_ERROR;
		}
		else {
			Logger::Error("Sce::PlayStation::Core::Graphics cannot be accessed from multiple threads.");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}

	}
	int PsmShaderProgram::Delete(int handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::AddRef(int handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::GetUniformCount(int handle, int* result){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::GetAttributeCount(int handle, int* result){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::FindUniform(int handle, std::string name, int* result){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::FindAttribute(int handle, std::string name, int* result) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::GetUniformBinding(int handle, int index, std::string* result) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformBinding(int handle, int index, std::string name) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::GetAttributeBinding(int handle, int index, std::string* result) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetAttributeBinding(int handle, int index, std::string name) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::GetUniformType(int handle, int index, ShaderUniformType* result) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::GetAttributeType(int handle, int index, ShaderAttributeType* result) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::GetUniformName(int handle, int index, std::string* result){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::GetAttributeName(int handle, int index, std::string* result) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::GetUniformSize(int handle, int index, int* result) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::GetAttributeSize(int handle, int index, int* result) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValueMatrix4(int handle, int index, int, Matrix4* value, ShaderUniformType type) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValueVector4(int handle, int index, int, Vector4* value, ShaderUniformType type) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValueVector3(int handle, int index, int, Vector3* value, ShaderUniformType type) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValueVector2(int handle, int index, int, Vector2* value, ShaderUniformType type) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValueFloat(int handle, int index, int, float* value, ShaderUniformType type) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValueInt(int handle, int index, int, int* value, ShaderUniformType type) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValue2Matrix4(int handle, int index, Matrix4* value, ShaderUniformType type, int to, int from, int count) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValue2Vector4(int handle, int index, Vector4* value, ShaderUniformType type, int to, int from, int count) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValue2Vector3(int handle, int index, Vector3* value, ShaderUniformType type, int to, int from, int count) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValue2Vector2(int handle, int index, Vector2* value, ShaderUniformType type, int to, int from, int count) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValue2Float(int handle, int index, float* value, ShaderUniformType type, int to, int from, int count) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValue2Int(int handle, int index, int* value, ShaderUniformType type, int to, int from, int count) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetAttributeValue2(int handle, int index, float* value) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::GetUniformTexture(int handle, int index, int* result) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::GetAttributeStream(int handle, int index, int* result) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetAttributeStream(int handle, int index, int stream) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
}
