#include <Sce/Pss/Core/ExceptionInfo.hpp>
#include <Sce/Pss/Core/Graphics/ShaderProgram.hpp>
#include <Sce/Pss/Core/Graphics/CGX.hpp>
#include <Sce/Pss/Core/Io/ICall.hpp>

#include <Sce/PlayStation/Core/Error.hpp>
#include <LibShared.hpp>
#include <glad/glad.h>

using namespace Shared::Debug;
using namespace Sce::Pss::Core::Io;

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

	int ShaderProgram::LoadProgram(std::byte* vertexShaderBuf, int vertexShaderSz, std::byte* fragmentShaderBuf, int fragmentShaderSz) {
		std::string fragmentSrc;
		std::string vertexSrc;

		if (vertexShaderBuf != nullptr) {
			CGX* cgx = new CGX(vertexShaderBuf, vertexShaderSz);
			ReturnErrorable(cgx);
			fragmentSrc = cgx->FragmentShader("GLSL");
			vertexSrc = cgx->VertexShader("GLSL");
			delete cgx;
		}
		if (fragmentShaderBuf != nullptr) {
			CGX* cgx = new CGX(fragmentShaderBuf, fragmentShaderSz);
			ReturnErrorable(cgx);
			fragmentSrc = cgx->FragmentShader("GLSL");
			vertexSrc = cgx->VertexShader("GLSL");
			delete cgx;
		}

		this->uniforms = std::vector<ProgramUniform>();
		this->attributes = std::vector<ProgramAttribute>();

		this->glReference = glCreateProgram();


		// ugly hack - append #version 150 to the shaders
		// required because the version directive is not included in CGX file's GLSL shaders
		// i dont know why.
		fragmentSrc = "#version 150\r\n" + fragmentSrc;
		vertexSrc = "#version 150\r\n" + vertexSrc;

		int compileFragmentShader = compileShader(GL_FRAGMENT_SHADER, (char*)fragmentSrc.c_str());
		if (compileFragmentShader == 0)
		{
			this->SetError(PSM_ERROR_GRAPHICS_SYSTEM);
			return 0;
		}

		int compileVertexShader = compileShader(GL_VERTEX_SHADER, (char*)vertexSrc.c_str());
		if (compileVertexShader == 0)
		{
			this->SetError(PSM_ERROR_GRAPHICS_SYSTEM);
			return 0;
		}

		glAttachShader(glReference, compileFragmentShader);
		glAttachShader(glReference, compileVertexShader);

		glLinkProgram(glReference);

		glDeleteShader(compileFragmentShader);
		glDeleteShader(compileVertexShader);

		int status = 0;
		glGetProgramiv(glReference, GL_LINK_STATUS, &status);

		if (status == GL_FALSE) {
			char log[0x1000];
			memset(log, 0, sizeof(log));

			int sz = 0;
			glGetProgramInfoLog(glReference, 0xFFF, &sz, log);
			glDeleteProgram(glReference);

			this->SetError(PSM_ERROR_GRAPHICS_SYSTEM);
			ExceptionInfo::AddMessage("Compile failed; " + std::string(log));
			return 0;
		}


		int uniformCount = 0;
		int attributeCount = 0;

		glGetProgramiv(glReference, GL_ACTIVE_UNIFORMS, &uniformCount);

		for (int i = 0; i < uniformCount; i++) {
			ProgramUniform uniform = ProgramUniform();

			int nameLen;
			char name[0x100];


			glGetActiveUniform(glReference, i, sizeof(name), &nameLen, &uniform.Size, &uniform.Type, name);
			uniform.Location = glGetUniformLocation(glReference, name);
			uniform.Index = i;
			uniform.Name = std::string(name, nameLen);


			Logger::Debug("Uniform: " + uniform.Name + " location: " + std::to_string(uniform.Location));

			if (uniform.Name.find(']') != std::string::npos) {
				Logger::Error(uniform.Name + " has a [], theres some special processing for these, but i dunno what it is.");
			}

			this->Uniforms()->push_back(uniform);
		}

		glGetProgramiv(glReference, GL_ACTIVE_ATTRIBUTES, &attributeCount);


		for (int i = 0; i < attributeCount; i++) {
			ProgramAttribute attribute = ProgramAttribute();

			int nameLen;
			char name[0x100];


			glGetActiveAttrib(glReference, i, sizeof(name), &nameLen, &attribute.Size, &attribute.Type, name);
			attribute.Location = glGetAttribLocation(glReference, name);
			attribute.Index = i;
			attribute.Name = std::string(name, nameLen);

			Logger::Debug("Attribute: " + attribute.Name + " location: " + std::to_string(attribute.Location));

			if (attribute.Name.find(']') != std::string::npos) {
				Logger::Error(attribute.Name + "  has a [], theres some special processing for these, but i dunno what it is.");
			}

			this->Attributes()->push_back(attribute);
		}
		
		return this->glReference;
	}

	int ShaderProgram::ActiveStateChanged(bool state) {
		Logger::Debug(__FUNCTION__);
		return PSM_ERROR_NO_ERROR;
	}

	std::byte* ShaderProgram::LoadFile(char* shaderPath, int* shaderLen) {

		uint64_t file;
		uint32_t totalRead;
		ICall::PsmFileOpen(shaderPath, SCE_PSS_FILE_OPEN_FLAG_READ | SCE_PSS_FILE_OPEN_FLAG_BINARY | SCE_PSS_FILE_OPEN_FLAG_NOTRUNCATE, &file);

		uint32_t cgxSz;
		ICall::PsmFileGetSize(file, &cgxSz);
		this->cgxData = new std::byte[cgxSz];

		ICall::PsmFileRead(file, this->cgxData, cgxSz, &totalRead);
		ICall::PsmClose(file);

		*shaderLen = cgxSz;
		return this->cgxData;

	}

	std::byte* ShaderProgram::CopyFile(std::byte* shaderSrc, int shaderLen) {
		this->cgxData = new std::byte[shaderLen];
		std::memcpy(this->cgxData, shaderSrc, shaderLen);
		return this->cgxData;
	}


	ShaderProgram::ShaderProgram(std::byte* vertexShaderBuf, int vertexShaderSz, std::byte* fragmentShaderBuf, int fragmentShaderSz) {
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

		this->glReference = this->LoadProgram(this->vertexCgx, this->vertexCgxLen, this->fragmentCgx, this->fragmentCgxLen);

	}

	ShaderProgram::ShaderProgram(char* vertexShaderPath, char* fragmentShaderPath) {
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

		this->glReference = this->LoadProgram(this->vertexCgx, this->vertexCgxLen, this->fragmentCgx, this->fragmentCgxLen);

	}

	ShaderProgram::~ShaderProgram() {
		if(this->cgxData != nullptr)
			delete this->cgxData;
		if(this->vertexCgx != nullptr)
			delete this->vertexCgx;
		if(this->fragmentCgx != nullptr)
			delete this->fragmentCgx;
	}

	int ShaderProgram::UniformCount() {
		return this->Uniforms()->size();
	}

	int ShaderProgram::AttributeCount() {
		return this->Attributes()->size();
	}

	std::vector<ProgramUniform>* ShaderProgram::Uniforms() {
		return &this->uniforms;
	}

	std::vector<ProgramAttribute>* ShaderProgram::Attributes() {
		return &this->attributes;
	}

}