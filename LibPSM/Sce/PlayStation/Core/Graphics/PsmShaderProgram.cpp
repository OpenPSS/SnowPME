#include "PsmShaderProgram.hpp"
#include "PsmGraphicsContext.hpp"
#include "../Error.hpp"
#include <iostream>
#include <string>
#include <LibSnowPME.hpp>
using namespace SnowPME::Debug;
using namespace SnowPME::Util;

namespace Sce::PlayStation::Core::Graphics {

	int PsmShaderProgram::compileShader(int type, char* source) {
		int shader = glCreateShader(type);
		glShaderSource(shader, 1, &source, 0);
		glCompileShader(shader);

		int status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

		if (status == GL_TRUE) {
			return shader;
		}
		else {
			char log[0x1000];
			memset(log, 0, sizeof(log));

			int sz = 0;

			glGetShaderInfoLog(shader, 0xFFF, &sz, log);
			if (type == GL_VERTEX_SHADER)
				Logger::Error("vertex shader compile failed: " + std::string(log));
			else
				Logger::Error("fragment shader compile failed: " + std::string(log));

			glDeleteShader(shader);
			return 0;
		}
	}

	int PsmShaderProgram::createProgram(std::string vertexSrc, std::string fragmentSrc, int* res) {

		int program = glCreateProgram();

		// ugly hack - append #version 150 to the shaders
		// required because the version directive is not included in CGX file's GLSL shaders
		// i dont know why.
		fragmentSrc = "#version 150\r\n" + fragmentSrc;
		vertexSrc = "#version 150\r\n" + vertexSrc;

		int compileFragmentShader = compileShader(GL_FRAGMENT_SHADER, (char*)fragmentSrc.c_str());
		if (compileFragmentShader == 0)
			return PSM_ERROR_GRAPHICS_SYSTEM;

		int compileVertexShader = compileShader(GL_VERTEX_SHADER, (char*)vertexSrc.c_str());
		if (compileVertexShader == 0)
			return PSM_ERROR_GRAPHICS_SYSTEM;

		glAttachShader(program, compileFragmentShader);
		glAttachShader(program, compileVertexShader);

		glLinkProgram(program);

		glDeleteShader(compileFragmentShader);
		glDeleteShader(compileVertexShader);

		int status = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &status);

		if (status == GL_FALSE) {
			char log[0x1000];
			memset(log, 0, sizeof(log));

			int sz = 0;
			glGetProgramInfoLog(program, 0xFFF, &sz, log);
			Logger::Error("program link error: " + std::string(log));
			glDeleteProgram(program);
			return PSM_ERROR_GRAPHICS_SYSTEM;
		}

		ShaderProgram* shdrPrg = new ShaderProgram();
		shdrPrg->Program = program;
		
		int uniformCount = 0;
		int attributeCount = 0;

		glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &uniformCount);

		for (int i = 0; i < uniformCount; i++) {
			ProgramUniform* uniform = new ProgramUniform();

			int nameLen;
			char name[0x100];


			glGetActiveUniform(program, i, sizeof(name), &nameLen, &uniform->Size, &uniform->Type, name);			
			uniform->Location = glGetUniformLocation(program, name);
			uniform->Index = i;
			uniform->Name = std::string(name, nameLen);
			

			Logger::Debug("Uniform: " + uniform->Name + " location: " + std::to_string(uniform->Location));

			if (uniform->Name.find(']') != std::string::npos) {
				Logger::Error(uniform->Name + " has a [], theres some special processing for these, but i dunno what it is.");
			}
			
			shdrPrg->Uniforms.push_back(uniform);
		}

		glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &attributeCount);


		for (int i = 0; i < attributeCount; i++) {
			ProgramAttribute* attribute = new ProgramAttribute();

			int nameLen;
			char name[0x100];


			glGetActiveAttrib(program, i, sizeof(name), &nameLen, &attribute->Size, &attribute->Type, name);
			attribute->Location = glGetAttribLocation(program, name);
			attribute->Index = i;
			attribute->Name = std::string(name, nameLen);

			Logger::Debug("Attribute: " + attribute->Name + " location: " + std::to_string(attribute->Location));

			if (attribute->Name.find(']') != std::string::npos) {
				Logger::Error(attribute->Name + "  has a [], theres some special processing for these, but i dunno what it is.");
			}

			shdrPrg->Attributes.push_back(attribute);
		}

		shdrPrg->AttributeCount = attributeCount;
		shdrPrg->UniformCount = uniformCount;

		*res = (uint32_t)shdrPrg;
		return PSM_ERROR_NO_ERROR;
	}

	int PsmShaderProgram::FromFile(MonoString*  vpFileName, MonoString* fpFileName, MonoString* constKeys, int* constVals, int *result){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::FromImage(MonoArray* vpFileName, MonoArray* fpFileImage, MonoArray* constKeys, int* constVals, int *result){
		Logger::Debug(__FUNCTION__);
		if (THREAD_CHECK) {
			size_t fnameSz = MonoUtil::MonoArrayLength(vpFileName);
			size_t fimgSz = MonoUtil::MonoArrayLength(fpFileImage);
			std::byte* fnameBuf = NULL;
			std::byte* fimgBuf = NULL;

			if(vpFileName != NULL)
				fnameBuf = (std::byte*)mono_array_addr_with_size(vpFileName, 1, 0);
			if(fpFileImage != NULL)
				fimgBuf = (std::byte*)mono_array_addr_with_size(fpFileImage, 1, 0);
			

			std::byte* cgx;
			size_t cgxSz;

			if (fimgBuf != NULL) {
				cgx = fimgBuf;
				cgxSz = fimgSz;
			}
			else if (fnameBuf != NULL) {
				cgx = fnameBuf;
				cgxSz = fnameSz;
			}
			else {
				return PSM_ERROR_COMMON_ARGUMENT_NULL;
			}


			CGX* cgxObj = NULL;
			std::string fragmentShader;
			std::string vertexShader;

			try {
				cgxObj = new SnowPME::Graphics::CGX(cgx, cgxSz);
				fragmentShader = cgxObj->FragmentShader("GLSL");
				Logger::Debug("Frag Source: " + fragmentShader);

				vertexShader = cgxObj->VertexShader("GLSL");
				Logger::Debug("Vert Source: " + vertexShader);

				if (cgxObj != NULL)
					delete cgxObj;
				cgxObj = NULL;
			}
			catch (std::exception e) {
				if (cgxObj != NULL)
					delete cgxObj;
				cgxObj = NULL;
				return AppGlobals::PsmLastError();
			}

			return createProgram(vertexShader, fragmentShader, result);
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
		Logger::Debug(__FUNCTION__);
		if (THREAD_CHECK) {
			ShaderProgram* prog = (ShaderProgram*)handle;
			if (prog == NULL) {
				return PSM_ERROR_COMMON_OBJECT_DISPOSED;
			}

			*result = prog->UniformCount;
			return PSM_ERROR_NO_ERROR;
		}
		else {
			Logger::Error("Sce::PlayStation::Core::Graphics cannot be accessed from multiple threads.");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
	}
	int PsmShaderProgram::GetAttributeCount(int handle, int* result){
		Logger::Debug(__FUNCTION__);
		if (THREAD_CHECK) {
			ShaderProgram* prog = (ShaderProgram*)handle;
			if (prog == NULL) {
				return PSM_ERROR_COMMON_OBJECT_DISPOSED;
			}

			*result = prog->AttributeCount;
			return PSM_ERROR_NO_ERROR;
		}
		else {
			Logger::Error("Sce::PlayStation::Core::Graphics cannot be accessed from multiple threads.");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
	}
	int PsmShaderProgram::FindUniform(int handle, MonoString* name, int* result){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::FindAttribute(int handle, MonoString* name, int* result) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::GetUniformBinding(int handle, int index, MonoString* result) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformBinding(int handle, int index, MonoString* name) {
		Logger::Debug(__FUNCTION__);
		if (THREAD_CHECK) {
			ShaderProgram* prog = (ShaderProgram*)handle;
			if (prog == NULL) {
				Logger::Error("handle was null.");
				return PSM_ERROR_COMMON_OBJECT_DISPOSED;
			}

			char* str = mono_string_to_utf8(name);
			std::string uniformName(str);

			bool found = false;
			for (ProgramUniform* uniform : prog->Uniforms)
			{
				if (uniform->Name == uniformName) {
					Logger::Debug("Setting uniform binding of " + uniformName + " to " + std::to_string(index));
					uniform->Binding = index;
					found = true;
				}
			}

			mono_free(str);

			if (!found) {
				Logger::Error("No uniform with name " + uniformName + " was found.");
				return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;
			}


			return PSM_ERROR_NO_ERROR;
		}
		else {
			Logger::Error("Sce::PlayStation::Core::Graphics cannot be accessed from multiple threads.");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
	}
	int PsmShaderProgram::GetAttributeBinding(int handle, int index, MonoString* result) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetAttributeBinding(int handle, int index, MonoString* name) {
		Logger::Debug(__FUNCTION__);
		if (THREAD_CHECK) {
			ShaderProgram* prog = (ShaderProgram*)handle;
			if (prog == NULL) {
				Logger::Error("handle was null.");
				return PSM_ERROR_COMMON_OBJECT_DISPOSED;
			}

			char* str = mono_string_to_utf8(name);
			std::string attributeName(str);

			bool found = false;
			for (ProgramAttribute* attribute : prog->Attributes)
			{
				if (attribute->Name == attributeName) {
					Logger::Debug("Setting attribute binding of " + attributeName + " to " + std::to_string(index));
					attribute->Binding = index;
					found = true;
				}
			}
			
			mono_free(str);

			if (!found) {
				Logger::Error("No attribute with name " + attributeName + " was found.");
				return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;
			}
			
			return PSM_ERROR_NO_ERROR;
		}
		else {
			Logger::Error("Sce::PlayStation::Core::Graphics cannot be accessed from multiple threads.");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
	}
	int PsmShaderProgram::GetUniformType(int handle, int index, ShaderUniformType* result) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::GetAttributeType(int handle, int index, ShaderAttributeType* result) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::GetUniformName(int handle, int index, MonoString* result){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::GetAttributeName(int handle, int index, MonoString* result) {
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
