#include <Sce/Pss/Core/Graphics/ShaderProgram.hpp>
#include <Sce/Pss/Core/ExceptionInfo.hpp>
#include <Sce/Pss/Core/Graphics/ShaderProgram.hpp>
#include <Sce/Pss/Core/Graphics/CGX.hpp>
#include <Sce/Pss/Core/Io/IoCall.hpp>
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <Sce/Pss/Core/Graphics/GlError.hpp>

#include <Sce/Pss/Core/Error.hpp>
#include <LibShared.hpp>
#include <glad/glad.h>
#include <string.h>

using namespace Shared::Debug;
using namespace Sce::Pss::Core::Io;
using namespace Sce::Pss::Core::Memory;

namespace Sce::Pss::Core::Graphics {

	int ShaderProgram::compileShader(int type, char* source) {
		
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

	int ShaderProgram::LoadProgram(uint8_t* vertexShaderBuf, int vertexShaderSz, uint8_t* fragmentShaderBuf, int fragmentShaderSz) {

		if (vertexShaderBuf != nullptr) {
			std::unique_ptr<CGX> cgxFile = std::make_unique<CGX>(vertexShaderBuf, vertexShaderSz);
			RETURN_ERRORABLE_SMARTPTR(cgxFile);

			std::string src = cgxFile->FindVertexShader("GLSL");
			RETURN_ERRORABLE_SMARTPTR(cgxFile);
			this->vertexSrc = src;

			if(fragmentShaderBuf == nullptr) {
				std::string src = cgxFile->FindFragmentShader("GLSL");
				RETURN_ERRORABLE_SMARTPTR(cgxFile);
				this->fragmentSrc = src;
			}

		}

		if (fragmentShaderBuf != nullptr) {
			std::unique_ptr<CGX> cgxFile = std::make_unique<CGX>(fragmentShaderBuf, fragmentShaderSz);
			RETURN_ERRORABLE_SMARTPTR(cgxFile);

			std::string src = cgxFile->FindFragmentShader("GLSL");
			RETURN_ERRORABLE_SMARTPTR(cgxFile);
			this->fragmentSrc = src;
		}

		this->GLReference = glCreateProgram();

		// ugly hack - append #version 150 to the shaders
		// required because the version directive is not included in CGX file's GLSL shaders
		// i dont know why.
		this->fragmentSrc = "#version 100\r\nprecision mediump float;\r\n" + this->fragmentSrc;
		this->vertexSrc = "#version 100\r\nprecision mediump float;\r\n" + this->vertexSrc;

		int compileFragmentShader = compileShader(GL_FRAGMENT_SHADER, (char*)this->fragmentSrc.c_str());
		if (compileFragmentShader == 0)
		{
			this->SetError(PSM_ERROR_GRAPHICS_SYSTEM);
			return 0;
		}

		int compileVertexShader = compileShader(GL_VERTEX_SHADER, (char*)this->vertexSrc.c_str());
		if (compileVertexShader == 0)
		{
			this->SetError(PSM_ERROR_GRAPHICS_SYSTEM);
			return 0;
		}

		glAttachShader(this->GLReference, compileFragmentShader);
		glAttachShader(this->GLReference, compileVertexShader);

		glLinkProgram(this->GLReference);

		glDeleteShader(compileFragmentShader);
		glDeleteShader(compileVertexShader);

		int status = 0;
		glGetProgramiv(this->GLReference, GL_LINK_STATUS, &status);

		if (status == GL_FALSE) {
			char log[0x1000];
			memset(log, 0, sizeof(log));

			int sz = 0;
			glGetProgramInfoLog(this->GLReference, 0xFFF, &sz, log);
			glDeleteProgram(this->GLReference);

			this->SetError(PSM_ERROR_GRAPHICS_SYSTEM);
			Logger::Error("Shader compile failed; " + std::string(log));
			return 0;
		}


		int uniformCount = 0;
		int attributeCount = 0;

		glGetProgramiv(this->GLReference, GL_ACTIVE_UNIFORMS, &uniformCount);

		Logger::Debug("CGX : fragment source code : \n" + this->fragmentSrc);
		Logger::Debug("CGX : vertex source code : \n" + this->vertexSrc);


		for (int i = 0; i < uniformCount; i++) {
			ProgramUniform uniform = ProgramUniform();

			int nameLen;
			char name[0x100];

			glGetActiveUniform(this->GLReference, i, sizeof(name), &nameLen, &uniform.Size, &uniform.Type, name);
			uniform.Location = glGetUniformLocation(this->GLReference, name);
			uniform.Index = i;
			uniform.Name = std::string(name, nameLen);
			size_t pos = uniform.Name.find('[');
			if (pos != std::string::npos) {
				uniform.Name = uniform.Name.substr(0, pos);
			}

			Logger::Debug("Uniform: " + uniform.Name + " location: " + std::to_string(uniform.Location));
			this->Uniforms.push_back(uniform);
		}

		glGetProgramiv(this->GLReference, GL_ACTIVE_ATTRIBUTES, &attributeCount);

		for (int i = 0; i < attributeCount; i++) {
			ProgramAttribute attribute = ProgramAttribute();

			int nameLen;
			char name[0x100];

			glGetActiveAttrib(this->GLReference, i, sizeof(name), &nameLen, &attribute.Size, &attribute.Type, name);
			attribute.Location = glGetAttribLocation(this->GLReference, name);
			attribute.Index = i;
			attribute.Name = std::string(name, nameLen);
			size_t pos = attribute.Name.find('[');
			if (pos != std::string::npos) {
				attribute.Name = attribute.Name.substr(0, pos);
			}

			Logger::Debug("Attribute: " + attribute.Name + " location: " + std::to_string(attribute.Location));
			this->Attributes.push_back(attribute);
		}
		

		return this->GLReference;
	}

	int ShaderProgram::ActiveStateChanged(bool state) {
		return PSM_ERROR_NO_ERROR;
	}

	uint8_t* ShaderProgram::LoadFile(char* shaderPath, int* shaderLen) {
		if (shaderLen != nullptr)
			*shaderLen = 0;

		if (shaderPath != nullptr) {
			uint64_t file;
			IoCall::PsmFileOpen(shaderPath, SCE_PSS_FILE_OPEN_FLAG_READ | SCE_PSS_FILE_OPEN_FLAG_BINARY | SCE_PSS_FILE_OPEN_FLAG_NOTRUNCATE, &file);
			if (file) {
				uint32_t cgxLen = 0;
				IoCall::PsmFileGetSize(file, &cgxLen);

				std::shared_ptr<HeapAllocator> resourceHeap = HeapAllocator::UniqueObject();
				uint8_t* cgxData = reinterpret_cast<uint8_t*>(resourceHeap->sce_psm_malloc(cgxLen));

				if (cgxData != nullptr) {
					uint32_t totalRead;
					IoCall::PsmFileRead(file, cgxData, cgxLen, &totalRead);
					IoCall::PsmClose(file);
					
					if (shaderLen != nullptr)
						*shaderLen = cgxLen;

					return cgxData;
				}
				else {
					IoCall::PsmClose(file);
					this->SetError(PSM_ERROR_COMMON_OUT_OF_MEMORY);
					return nullptr;
				}
			}
			else {
				this->SetError(PSM_ERROR_COMMON_FILE_NOT_FOUND);
				return nullptr;
			}

		}
		else {
			shaderLen = 0;
			return nullptr;
		}
	}

	uint8_t* ShaderProgram::CopyFile(uint8_t* shaderSrc, int shaderLen) {
		std::shared_ptr<HeapAllocator> resourceHeap = HeapAllocator::UniqueObject();
		uint8_t* cgxData = reinterpret_cast<uint8_t*>(resourceHeap->sce_psm_malloc(shaderLen));
		if (cgxData != nullptr) {
			memcpy(cgxData, shaderSrc, shaderLen);
			return cgxData;
		}
		else {
			this->SetError(PSM_ERROR_COMMON_OUT_OF_MEMORY);
			return nullptr;
		}
	}


	ShaderProgram::ShaderProgram(uint8_t* vertexShaderBuf, int vertexShaderSz, uint8_t* fragmentShaderBuf, int fragmentShaderSz) {
		LOCK_GUARD();
		if (vertexShaderBuf != nullptr) {
			this->vertexCgx = this->CopyFile(vertexShaderBuf, vertexShaderSz);
		}
		else {
			this->vertexCgx = nullptr;
		}

		if (fragmentShaderBuf != nullptr) {
			this->fragmentCgx = this->CopyFile(fragmentShaderBuf, fragmentShaderSz);
		}
		else {
			this->fragmentCgx = nullptr;
		}

		this->vertexCgxLen = vertexShaderSz;
		this->fragmentCgxLen = fragmentShaderSz;

		this->GLReference = this->LoadProgram(this->vertexCgx, this->vertexCgxLen, this->fragmentCgx, this->fragmentCgxLen);

	}

	ShaderProgram::ShaderProgram(char* vertexShaderPath, char* fragmentShaderPath) {
		LOCK_GUARD();
		if (vertexShaderPath != nullptr) {
			this->vertexCgx = this->LoadFile(vertexShaderPath, &this->vertexCgxLen);
		}
		else {
			this->vertexCgx = nullptr;
		}

		if (fragmentShaderPath != nullptr) {
			this->fragmentCgx = this->LoadFile(fragmentShaderPath, &this->fragmentCgxLen);
		}
		else {
			this->fragmentCgx = nullptr;
		}

		this->GLReference = this->LoadProgram(this->vertexCgx, this->vertexCgxLen, this->fragmentCgx, this->fragmentCgxLen);

	}

	ShaderProgram::~ShaderProgram() {
		LOCK_GUARD();
		std::shared_ptr<HeapAllocator> resourceHeap = HeapAllocator::UniqueObject();

		if(this->vertexCgx != nullptr)
			resourceHeap->sce_psm_free(this->vertexCgx);
		
		if(this->fragmentCgx != nullptr)
			resourceHeap->sce_psm_free(this->fragmentCgx);
	}

	int ShaderProgram::UniformCount() {
		return this->Uniforms.size();
	}

	int ShaderProgram::AttributeCount() {
		return this->Attributes.size();
	}


	int ShaderProgram::FindAttribute(std::string& name) {
		for (ProgramAttribute attribute : this->Attributes) {
			if (attribute.Name == name) {
				return attribute.Index;
			}
		}

		return -1;
	}

	int ShaderProgram::SetAttributeBinding(int index, std::string& name) {
		if (this->FindAttribute(name) == -1) {
			ExceptionInfo::AddMessage("Attribute variable '" + name + "' is not found\n");
			return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;
		}

		GL_CALL(glBindAttribLocation(this->GLReference, index, name.c_str()));
		if (attributeBindings.size() <= static_cast<size_t>(index)) attributeBindings.resize(index + 1);
		attributeBindings[index] = name;
		return PSM_ERROR_NO_ERROR;
	}
	
	std::string ShaderProgram::GetAttributeBinding(int index) const 
	{
		if(attributeBindings.size() <= static_cast<size_t>(index)) return "";
		return attributeBindings[index];
    }

	std::string ShaderProgram::GetAttributeName(int index) const
	{
		if (Attributes.size() <= static_cast<size_t>(index)) return "";
		return Attributes[index].Name;
	}

    int ShaderProgram::GetAttributeLocation(std::string &name) const 
	{
		return glGetAttribLocation(this->GLReference, name.c_str());
    }

	ShaderAttributeType ShaderProgram::GetAttributeType(int index) const
    {
        GLint params = 0;
		GL_CALL(glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_TYPE, &params));
		GLenum err = glGetError();
		ASSERT(err != GL_NO_ERROR);

		ASSERT(params != GL_BYTE);
		ASSERT(params != GL_UNSIGNED_BYTE);
		ASSERT(params != GL_SHORT);

		switch(params) {
			case GL_FLOAT:
				return ShaderAttributeType::Float;
		}
		return ShaderAttributeType::None;
    }

    std::string ShaderProgram::GetUniformName(int index) {
		GLchar nameBuf[0xff];
		GLsizei nameLength;

		GL_CALL(glGetActiveUniform(this->GLReference, index, sizeof(nameBuf), &nameLength, nullptr, nullptr, nameBuf));
		return std::string(nameBuf, nameLength);
	}
}
