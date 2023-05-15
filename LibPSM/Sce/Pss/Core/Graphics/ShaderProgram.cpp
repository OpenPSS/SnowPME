#include <Sce/Pss/Core/ExceptionInfo.hpp>
#include <Sce/Pss/Core/Graphics/ShaderProgram.hpp>

#include <Sce/PlayStation/Core/Error.hpp>
#include <LibShared.hpp>
#include <glad/glad.h>

using namespace Shared::Debug;
using namespace Sce::Pss::Core;

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

	ShaderProgram::ShaderProgram(std::string vertexSrc, std::string fragmentSrc) {
		this->uniforms = new std::vector<ProgramUniform>();
		this->attributes = new std::vector<ProgramAttribute>();

		this->glReference = glCreateProgram();
		
		// ugly hack - append #version 150 to the shaders
		// required because the version directive is not included in CGX file's GLSL shaders
		// i dont know why.
		fragmentSrc = "#version 150\r\n" + fragmentSrc;
		vertexSrc = "#version 150\r\n" + vertexSrc;
		
		this->vertexSourceCode = vertexSrc;
		this->fragmentSourceCode = fragmentSrc;

		int compileFragmentShader = compileShader(GL_FRAGMENT_SHADER, (char*)fragmentSrc.c_str());
		if (compileFragmentShader == 0)
		{
			this->SetError(PSM_ERROR_GRAPHICS_SYSTEM);
			return;
		}

		int compileVertexShader = compileShader(GL_VERTEX_SHADER, (char*)vertexSrc.c_str());
		if (compileVertexShader == 0)
		{
			this->SetError(PSM_ERROR_GRAPHICS_SYSTEM);
			return;
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
			return;
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


	}

	ShaderProgram::~ShaderProgram() {
		delete this->uniforms;
		delete this->attributes;
	}

	int ShaderProgram::UniformCount() {
		return this->Uniforms()->size();
	}

	int ShaderProgram::AttributeCount() {
		return this->Attributes()->size();
	}

	std::vector<ProgramUniform>* ShaderProgram::Uniforms() {
		return this->uniforms;
	}

	std::vector<ProgramAttribute>* ShaderProgram::Attributes() {
		return this->attributes;
	}

}