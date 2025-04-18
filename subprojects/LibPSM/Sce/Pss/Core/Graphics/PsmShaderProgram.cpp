#include <Sce/Pss/Core/Graphics/PsmShaderProgram.hpp>
#include <Sce/Pss/Core/Graphics/PsmGraphicsContext.hpp>
#include <Sce/Pss/Core/Error.hpp>

#include <Sce/Pss/Core/Threading/Thread.hpp>
#include <Sce/Pss/Core/Graphics/CGX.hpp>
#include <Sce/Pss/Core/Graphics/ShaderProgram.hpp>
#include <Sce/Pss/Core/ExceptionInfo.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
#include <Sce/Pss/Core/Io/ICall.hpp>
#include <Sce/Pss/Core/Mono/MonoUtil.hpp>

#include <iostream>
#include <string>
#include <LibShared.hpp>

using namespace Shared::Debug;

using namespace Sce::Pss::Core;
using namespace Sce::Pss::Core::Threading;
using namespace Sce::Pss::Core::Graphics;
using namespace Sce::Pss::Core::Io;
using namespace Sce::Pss::Core::System;

namespace Sce::Pss::Core::Graphics {


	#define MAIN_THREAD() \
		if(!Thread::IsMainThread()) { \
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed from multiple threads.\n"); \
			return PSM_ERROR_COMMON_INVALID_OPERATION; \
		}

	#define GET_PROG() \
		Logger::Debug(__FUNCTION__); \
		MAIN_THREAD() \
		ShaderProgram* prog = Handles::Get<ShaderProgram>(handle); \
		if (prog == NULL) { \
			Logger::Error("handle was null."); \
			return PSM_ERROR_COMMON_OBJECT_DISPOSED; \
		}

	int PsmShaderProgram::FromFile(MonoString* vpFileName, MonoString* fpFileName, MonoString* constKeys, int* constVals, int *result) {
		Logger::Debug(__FUNCTION__);
		MAIN_THREAD();
		char* vertexProgramFileName = mono_string_to_utf8(vpFileName);
		char* fragmentProgramFileName = mono_string_to_utf8(fpFileName);

		ShaderProgram* shdrPrg = new ShaderProgram(vertexProgramFileName, fragmentProgramFileName);
		ReturnErrorable(shdrPrg);

		*result = shdrPrg->Handle;

		if(vertexProgramFileName != nullptr)
			mono_free(vertexProgramFileName);

		if (fragmentProgramFileName != nullptr)
			mono_free(fragmentProgramFileName);

		return PSM_ERROR_NO_ERROR;
	}
	int PsmShaderProgram::FromImage(MonoArray* vpFileImage, MonoArray* fpFileImage, MonoArray* constKeys, int* constVals, int *result){
		Logger::Debug(__FUNCTION__);
		MAIN_THREAD();

		size_t vertexShaderSz = Sce::Pss::Core::Mono::MonoUtil::MonoArrayBytesLength(vpFileImage);
		size_t fragmentShaderSz = Sce::Pss::Core::Mono::MonoUtil::MonoArrayBytesLength(fpFileImage);
		uint8_t* vertexShaderBuf = nullptr;
		uint8_t* fragmentShaderBuf = nullptr;

		if(vpFileImage != nullptr)
			vertexShaderBuf = (uint8_t*)mono_array_addr_with_size(vpFileImage, 1, 0);
		if(fpFileImage != nullptr)
			fragmentShaderBuf = (uint8_t*)mono_array_addr_with_size(fpFileImage, 1, 0);

		ShaderProgram* shdrPrg = new ShaderProgram(vertexShaderBuf, vertexShaderSz, fragmentShaderBuf, fragmentShaderSz);
		ReturnErrorable(shdrPrg);

		*result = shdrPrg->Handle;
		return PSM_ERROR_NO_ERROR;
	}
	
	int PsmShaderProgram::Delete(int handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}

	int PsmShaderProgram::AddRef(int handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}

	int PsmShaderProgram::GetUniformCount(int handle, int* result) {
		GET_PROG();
		*result = prog->UniformCount();
		return PSM_ERROR_NO_ERROR;
	}

	int PsmShaderProgram::GetAttributeCount(int handle, int* result) {
		GET_PROG();
		*result = prog->AttributeCount();
		return PSM_ERROR_NO_ERROR;
	}

	int PsmShaderProgram::FindUniform(int handle, MonoString* name, int* result) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}

	int PsmShaderProgram::FindAttribute(int handle, MonoString* name, int* result) {
		GET_PROG();

		std::string attributeName;
    	Mono::MonoUtil::MonoStringToStdString(name, attributeName);

		for (const auto& binding : prog->GetAttributeBindings()) {
			if (binding.second == attributeName) {
				*result = binding.first;
				return PSM_ERROR_NO_ERROR;
			}
		}
		return PSM_ERROR_COMMON_INVALID_OPERATION;
	}

	int PsmShaderProgram::GetUniformBinding(int handle, int index, MonoString** result) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}

	int PsmShaderProgram::SetUniformBinding(int handle, int index, MonoString* name) {
		GET_PROG();
		
		std::string uniformName;
		Mono::MonoUtil::MonoStringToStdString(name, uniformName);

		bool found = false;
		for (ProgramUniform uniform : prog->Uniforms)
		{
			if (uniform.Name == uniformName) {
				Logger::Debug("Setting uniform binding of " + uniformName + " to " + std::to_string(index));
				uniform.Binding = index;
				found = true;
			}
		}

		if (!found) {
			Logger::Error("No uniform with name " + uniformName + " was found.");
			return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;
		}


		return PSM_ERROR_NO_ERROR;
	}
	int PsmShaderProgram::GetAttributeBinding(int handle, int index, MonoString** result) {
		GET_PROG();

		auto bindingName = prog->GetAttributeBinding(index);
		if(bindingName == "") {
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}

		*result = Mono::MonoUtil::StdStringToMonoString(bindingName);
		return PSM_ERROR_NO_ERROR;
	}

	int PsmShaderProgram::SetAttributeBinding(int handle, int index, MonoString* name) {
		GET_PROG();

		std::string attributeName;
		Mono::MonoUtil::MonoStringToStdString(name, attributeName);

		prog->SetAttributeBinding(index, attributeName);
		if(prog->GetError() != PSM_ERROR_NO_ERROR) {
			return prog->GetError();
		}

		return PSM_ERROR_NO_ERROR;
	}

	int PsmShaderProgram::GetUniformType(int handle, int index, ShaderUniformType* result) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}

	int PsmShaderProgram::GetAttributeType(int handle, int index, ShaderAttributeType* result) {
		GET_PROG();
		prog->GetAttributeType(index, result);
		return PSM_ERROR_NO_ERROR;
	}

	int PsmShaderProgram::GetUniformName(int handle, int index, MonoString** result){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::GetAttributeName(int handle, int index, MonoString** result) {
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
	int PsmShaderProgram::SetUniformValue(int handle, int index, int offset, void* value, ShaderUniformType type) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValue2(int handle, int index, void* value, ShaderUniformType type, int to, int from, int count) {
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
