#include <Sce/PlayStation/Core/Graphics/PsmShaderProgram.hpp>
#include <Sce/PlayStation/Core/Graphics/PsmGraphicsContext.hpp>
#include <Sce/PlayStation/Core/Error.hpp>

#include <Sce/Pss/Core/Threading/Thread.hpp>
#include <Sce/Pss/Core/Graphics/CGX.hpp>
#include <Sce/Pss/Core/Graphics/ShaderProgram.hpp>
#include <Sce/Pss/Core/ExceptionInfo.hpp>
#include <Sce/Pss/Core/Handles.hpp>
#include <Sce/Pss/Core/Io/ICall.hpp>

#include <iostream>
#include <string>
#include <LibSnowPME.hpp>
using namespace SnowPME::Debug;
using namespace SnowPME::Util;

using namespace Sce::Pss::Core;
using namespace Sce::Pss::Core::Threading;
using namespace Sce::Pss::Core::Graphics;
using namespace Sce::Pss::Core::Io;

namespace Sce::PlayStation::Core::Graphics {


	int PsmShaderProgram::FromFile(MonoString* vpFileName, MonoString* fpFileName, MonoString* constKeys, int* constVals, int *result) {
		Logger::Debug(__FUNCTION__);
		if (Thread::IsMainThread()) {
			char* vertexProgramFileName = mono_string_to_utf8(vpFileName);
			char* fragmentProgramFileName = mono_string_to_utf8(fpFileName);

			char* useFilename = NULL;
			
			if (vertexProgramFileName != NULL)
				useFilename = vertexProgramFileName;
			if (fragmentProgramFileName != NULL)
				useFilename = fragmentProgramFileName;

			if(vertexProgramFileName == NULL && fragmentProgramFileName == NULL)
				return PSM_ERROR_COMMON_ARGUMENT_NULL;

			if(useFilename == NULL)
				return PSM_ERROR_COMMON_ARGUMENT_NULL;

			uint64_t file;
			uint32_t totalRead;
			int res = ICall::PsmFileOpen(useFilename, SCE_PSS_FILE_OPEN_FLAG_READ | SCE_PSS_FILE_OPEN_FLAG_BINARY | SCE_PSS_FILE_OPEN_FLAG_NOTRUNCATE, &file);

			if (res != PSM_ERROR_NO_ERROR)
				return res;

			uint32_t cgxSz;
			ICall::PsmFileGetSize(file, &cgxSz);
			std::byte* cgx = new std::byte[cgxSz];


			ICall::PsmFileRead(file, cgx, cgxSz, &totalRead);
			ICall::PsmClose(file);


			std::string fragmentShader;
			std::string vertexShader;

			CGX* cgxObj = new CGX(cgx, cgxSz);
			fragmentShader = cgxObj->FragmentShader("GLSL");
			vertexShader = cgxObj->VertexShader("GLSL");
			ReturnErrorable(cgxObj);

			ShaderProgram* shdrPrg = new ShaderProgram(vertexShader, fragmentShader);
			ReturnErrorable(shdrPrg);

			*result = shdrPrg->Handle();

			delete[] cgx;

			return PSM_ERROR_NO_ERROR;
		}
		else {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed from multiple threads.");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}

	}
	int PsmShaderProgram::FromImage(MonoArray* vpFileName, MonoArray* fpFileImage, MonoArray* constKeys, int* constVals, int *result){
		Logger::Debug(__FUNCTION__);
		if (Thread::IsMainThread()) {
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

			std::string fragmentShader;
			std::string vertexShader;

			CGX* cgxObj = new CGX(cgx, cgxSz);
			fragmentShader = cgxObj->FragmentShader("GLSL");
			vertexShader = cgxObj->VertexShader("GLSL");
			ReturnErrorable(cgxObj);

			ShaderProgram* shdrPrg = new ShaderProgram(vertexShader, fragmentShader);
			ReturnErrorable(shdrPrg);

			*result = Handles::CreateHandle((uintptr_t)shdrPrg);
			return PSM_ERROR_NO_ERROR;
		}
		else {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed from multiple threads.");
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
		if (Thread::IsMainThread()) {
			ShaderProgram* prog = (ShaderProgram*)Handles::GetHandle(handle);
			if (prog == NULL) {
				return PSM_ERROR_COMMON_OBJECT_DISPOSED;
			}

			*result = prog->UniformCount();
			return PSM_ERROR_NO_ERROR;
		}
		else {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed from multiple threads.");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
	}
	int PsmShaderProgram::GetAttributeCount(int handle, int* result){
		Logger::Debug(__FUNCTION__);
		if (Thread::IsMainThread()) {
			ShaderProgram* prog = (ShaderProgram*)Handles::GetHandle(handle);
			if (prog == NULL) {
				return PSM_ERROR_COMMON_OBJECT_DISPOSED;
			}

			*result = prog->AttributeCount();
			return PSM_ERROR_NO_ERROR;
		}
		else {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed from multiple threads.");
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
		if (Thread::IsMainThread()) {
			ShaderProgram* prog = (ShaderProgram*)Handles::GetHandle(handle);
			if (prog == NULL) {
				Logger::Error("handle was null.");
				return PSM_ERROR_COMMON_OBJECT_DISPOSED;
			}

			char* str = mono_string_to_utf8(name);
			std::string uniformName(str);

			bool found = false;
			for (ProgramUniform uniform : *prog->Uniforms())
			{
				if (uniform.Name == uniformName) {
					Logger::Debug("Setting uniform binding of " + uniformName + " to " + std::to_string(index));
					uniform.Binding = index;
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
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed from multiple threads.");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
	}
	int PsmShaderProgram::GetAttributeBinding(int handle, int index, MonoString* result) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetAttributeBinding(int handle, int index, MonoString* name) {
		Logger::Debug(__FUNCTION__);
		if (Thread::IsMainThread()) {
			ShaderProgram* prog = (ShaderProgram*)Handles::GetHandle(handle);
			if (prog == NULL) {
				Logger::Error("handle was null.");
				return PSM_ERROR_COMMON_OBJECT_DISPOSED;
			}

			char* str = mono_string_to_utf8(name);
			std::string attributeName(str);

			bool found = false;
			for (ProgramAttribute attribute : *prog->Attributes())
			{
				if (attribute.Name == attributeName) {
					Logger::Debug("Setting attribute binding of " + attributeName + " to " + std::to_string(index));
					attribute.Binding = index;
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
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed from multiple threads."); 
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
