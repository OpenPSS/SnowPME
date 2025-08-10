#include <Sce/Pss/Core/Graphics/PsmShaderProgram.hpp>
#include <Sce/Pss/Core/Graphics/PsmGraphicsContext.hpp>
#include <Sce/Pss/Core/Error.hpp>

#include <Sce/Pss/Core/Threading/Thread.hpp>
#include <Sce/Pss/Core/Graphics/CGX.hpp>
#include <Sce/Pss/Core/Graphics/ShaderProgram.hpp>
#include <Sce/Pss/Core/ExceptionInfo.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
#include <Sce/Pss/Core/Io/IoCall.hpp>
#include <Sce/Pss/Core/Mono/MonoUtil.hpp>

#include <iostream>
#include <string>
#include <LibShared.hpp>

using namespace Shared::Debug;

using namespace Sce::Pss::Core;
using namespace Sce::Pss::Core::Threading;
using namespace Sce::Pss::Core::Graphics;
using namespace Sce::Pss::Core::Io;
using namespace Sce::Pss::Core::Mono;
using namespace Sce::Pss::Core::System;

namespace Sce::Pss::Core::Graphics {

	int PsmShaderProgram::FromFile(MonoString* vpFileName, MonoString* fpFileName, MonoString* constKeys, int* constVals, int *result) {
		LOG_FUNCTION();
		
		if (!Thread::IsMainThread()) {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed by multiple theads\n"); 
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		};

		char* vertexProgramFileName = mono_string_to_utf8(vpFileName);
		char* fragmentProgramFileName = mono_string_to_utf8(fpFileName);

		ShaderProgram* prog = ShaderProgram::Create(vertexProgramFileName, fragmentProgramFileName);
		RETURN_ERRORABLE_GRAPHICSOBJECT(prog, ShaderProgram);

		*result = prog->Handle();

		if(vertexProgramFileName != nullptr) mono_free(vertexProgramFileName);
		if (fragmentProgramFileName != nullptr) mono_free(fragmentProgramFileName);

		return PSM_ERROR_NO_ERROR;
	}
	int PsmShaderProgram::FromImage(MonoArray* vpFileImage, MonoArray* fpFileImage, MonoArray* constKeys, int* constVals, int *result){
		LOG_FUNCTION();

		if (!Thread::IsMainThread()) {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed by multiple theads\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}

		size_t vertexShaderSz = MonoUtil::MonoArrayBytesLength(vpFileImage);
		size_t fragmentShaderSz = MonoUtil::MonoArrayBytesLength(fpFileImage);
		uint8_t* vertexShaderBuf = nullptr;
		uint8_t* fragmentShaderBuf = nullptr;

		if(vpFileImage != nullptr) vertexShaderBuf = reinterpret_cast<uint8_t*>(mono_array_addr_with_size(vpFileImage, 1, 0));
		if(fpFileImage != nullptr) fragmentShaderBuf = reinterpret_cast<uint8_t*>(mono_array_addr_with_size(fpFileImage, 1, 0));

		ShaderProgram* prog = ShaderProgram::Create(vertexShaderBuf, vertexShaderSz, fragmentShaderBuf, fragmentShaderSz);
		RETURN_ERRORABLE_GRAPHICSOBJECT(prog, ShaderProgram);

		*result = prog->Handle();
		return PSM_ERROR_NO_ERROR;
	}
	
	int PsmShaderProgram::Delete(int handle){
		LOG_FUNCTION();

		if (Handles<ShaderProgram>::IsValid(handle)) {
	
			if (!Thread::IsMainThread()) {
				ShaderProgram::Release(handle);
				return PSM_ERROR_NO_ERROR;
			}
			else {
				UNIMPLEMENTED_MSG("Trying to delete ShaderProgram cross-thread (TODO: Notify main thread?)");
			}
		}
		return PSM_ERROR_NO_ERROR;


	}

	int PsmShaderProgram::AddRef(int handle){
		LOG_FUNCTION();
		if (Thread::IsMainThread()) {
			return (ShaderProgram::AddRef(handle) != false) ? PSM_ERROR_NO_ERROR : PSM_ERROR_COMMON_OBJECT_DISPOSED;
		}
		ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed by multiple theads\n");
		return PSM_ERROR_COMMON_INVALID_OPERATION;
	}

	int PsmShaderProgram::GetUniformCount(int handle, int* result) {
		LOG_FUNCTION();
		if (!Thread::IsMainThread()) {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed by multiple theads\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}


		if (!Handles<ShaderProgram>::IsValid(handle)) {
			return PSM_ERROR_COMMON_OBJECT_DISPOSED;
		};

		ShaderProgram* prog = Handles<ShaderProgram>::GetRaw(handle);

		*result = prog->UniformCount();
		return PSM_ERROR_NO_ERROR;
	}

	int PsmShaderProgram::GetAttributeCount(int handle, int* result) {
		LOG_FUNCTION();
		if (!Thread::IsMainThread()) {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed by multiple theads\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}


		if (!Handles<ShaderProgram>::IsValid(handle)) {
			return PSM_ERROR_COMMON_OBJECT_DISPOSED;
		};

		ShaderProgram* prog = Handles<ShaderProgram>::GetRaw(handle);

		*result = prog->AttributeCount();
		return PSM_ERROR_NO_ERROR;
	}

	int PsmShaderProgram::FindUniform(int handle, MonoString* name, int* result) {
		UNIMPLEMENTED();
	}

	int PsmShaderProgram::FindAttribute(int handle, MonoString* name, int* result) {
		LOG_FUNCTION();
		if (!Thread::IsMainThread()) {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed by multiple theads\n"); 
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}

		if (!Handles<ShaderProgram>::IsValid(handle)) {
			return PSM_ERROR_COMMON_OBJECT_DISPOSED;
		};

		ShaderProgram* prog = Handles<ShaderProgram>::GetRaw(handle);

		std::string attributeName;
    	MonoUtil::MonoStringToStdString(name, attributeName);

		// if not found, *result = -1
		// do NOT return error, that isnt what psm expects
		*result = prog->GetAttributeLocation(attributeName);
		return PSM_ERROR_NO_ERROR;
	}

	int PsmShaderProgram::GetUniformBinding(int handle, int index, MonoObject** result) {
		UNIMPLEMENTED();
	}

	int PsmShaderProgram::SetUniformBinding(int handle, int index, MonoString* name) {
		LOG_FUNCTION();
		if (!Thread::IsMainThread()) {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed by multiple theads\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}

		if (!Handles<ShaderProgram>::IsValid(handle)) {
			return PSM_ERROR_COMMON_OBJECT_DISPOSED;
		};

		ShaderProgram* prog = Handles<ShaderProgram>::GetRaw(handle);
		
		std::string uniformName;
		MonoUtil::MonoStringToStdString(name, uniformName);

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
	int PsmShaderProgram::GetAttributeBinding(int handle, int index, MonoObject** result) {
		LOG_FUNCTION();
		if (!Thread::IsMainThread()) {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed by multiple theads\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}


		if (!Handles<ShaderProgram>::IsValid(handle)) {
			return PSM_ERROR_COMMON_OBJECT_DISPOSED;
		} 
		
		ShaderProgram* prog = Handles<ShaderProgram>::GetRaw(handle);;

		std::string bindingName = prog->GetAttributeBinding(index);
		if (!bindingName.empty()) {
			MonoString* monoBindingName = MonoUtil::StdStringToMonoString(bindingName);
			mono_gc_wbarrier_generic_store(result, reinterpret_cast<MonoObject*>(monoBindingName));
		}
		else {
			mono_gc_wbarrier_generic_store(result, nullptr);
		}

		return PSM_ERROR_NO_ERROR;
	}

	int PsmShaderProgram::SetAttributeBinding(int handle, int index, MonoString* name) {
		LOG_FUNCTION();
		if (!Thread::IsMainThread()) {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed by multiple theads\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}

		if (!Handles<ShaderProgram>::IsValid(handle)) {
			return PSM_ERROR_COMMON_OBJECT_DISPOSED;
		};

		ShaderProgram* prog = Handles<ShaderProgram>::GetRaw(handle);

		if (index < 0 || index >= static_cast<int>(prog->Attributes.size())) {
			return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;
		}

		std::string attributeName = "";
		MonoUtil::MonoStringToStdString(name, attributeName);
		return prog->SetAttributeBinding(index, attributeName);
	}

	int PsmShaderProgram::GetUniformType(int handle, int index, ShaderUniformType* result) {
		UNIMPLEMENTED();
	}

	int PsmShaderProgram::GetAttributeType(int handle, int index, ShaderAttributeType* result) {
		LOG_FUNCTION();
		if (!Thread::IsMainThread()) {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed by multiple theads\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
		if (!Handles<ShaderProgram>::IsValid(handle)) {
			return PSM_ERROR_COMMON_OBJECT_DISPOSED;
		};

		ShaderProgram* prog = Handles<ShaderProgram>::GetRaw(handle);

		if (index < 0 || index >= static_cast<int>(prog->Attributes.size())) {
			return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;
		}

		*result = prog->GetAttributeType(index);
		return PSM_ERROR_NO_ERROR;
	}

	int PsmShaderProgram::GetUniformName(int handle, int index, MonoObject** result) {
		LOG_FUNCTION();
		if (!Thread::IsMainThread()) {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed by multiple theads\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}


		if (!Handles<ShaderProgram>::IsValid(handle)) {
			return PSM_ERROR_COMMON_OBJECT_DISPOSED;
		};

		ShaderProgram* prog = Handles<ShaderProgram>::GetRaw(handle);

		if (index < 0 || index >= static_cast<int>(prog->Attributes.size())) {
			return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;
		}

		std::string uniformName = prog->GetUniformName(index);
		MonoString* monoUniformName = MonoUtil::StdStringToMonoString(uniformName);
		mono_gc_wbarrier_generic_store(result, reinterpret_cast<MonoObject*>(monoUniformName));

		return PSM_ERROR_NO_ERROR;
	}

	int PsmShaderProgram::GetAttributeName(int handle, int index, MonoObject** result) {
		LOG_FUNCTION();
		if (!Thread::IsMainThread()) {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed by multiple theads\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}

		if (!Handles<ShaderProgram>::IsValid(handle)) {
			return PSM_ERROR_COMMON_OBJECT_DISPOSED;
		}

		std::shared_ptr<ShaderProgram> prog = Handles<ShaderProgram>::Get(handle);

		if (index < 0 || index >= static_cast<int>(prog->Attributes.size())) {
			return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;
		}

		std::string attributeName = prog->GetAttributeName(index);
		MonoString* monoAttributeName = MonoUtil::StdStringToMonoString(attributeName);
		mono_gc_wbarrier_generic_store(result, reinterpret_cast<MonoObject*>(monoAttributeName));

		return PSM_ERROR_NO_ERROR;
	}
	int PsmShaderProgram::GetUniformSize(int handle, int index, int* result) {
		UNIMPLEMENTED();
	}
	int PsmShaderProgram::GetAttributeSize(int handle, int index, int* result) {
		UNIMPLEMENTED();
	}
	int PsmShaderProgram::SetUniformValue(int handle, int index, int offset, void* value, ShaderUniformType type) {
		UNIMPLEMENTED();
	}
	int PsmShaderProgram::SetUniformValue2(int handle, int index, void* value, ShaderUniformType type, int to, int from, int count) {
		UNIMPLEMENTED();
	}
	int PsmShaderProgram::SetAttributeValue2(int handle, int index, float* value) {
		UNIMPLEMENTED();
	}
	int PsmShaderProgram::GetUniformTexture(int handle, int index, int* result) {
		UNIMPLEMENTED();
	}
	int PsmShaderProgram::GetAttributeStream(int handle, int index, int* result) {
		UNIMPLEMENTED();
	}
	int PsmShaderProgram::SetAttributeStream(int handle, int index, int stream) {
		UNIMPLEMENTED();
	}
}
