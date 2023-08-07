#ifndef LIB_PSS_SHADERPROGRAM_H
#define LIB_PSS_SHADERPROGRAM_H 1
#include <string>
#include <vector>
#include <Sce/Pss/Core/Graphics/GraphicsObject.hpp>
#include <Sce/Pss/Core/Graphics/ShaderProgramOption.hpp>

namespace Sce::Pss::Core::Graphics {


	class ShaderProgram : public GraphicsObject {
	private:
		uint8_t* vertexCgx = nullptr;
		uint8_t* fragmentCgx = nullptr;
		int vertexCgxLen;
		int fragmentCgxLen;

		int compileShader(int type, char* source);

		ShaderProgramOption* programOptions;
	public:
		int ActiveStateChanged(bool state);
		int UniformCount();
		int AttributeCount();

		std::vector<ProgramUniform> Uniforms = std::vector<ProgramUniform>();
		std::vector<ProgramAttribute> Attributes = std::vector<ProgramAttribute>();

		uint8_t* LoadFile(char* shaderPath, int* shaderLen);
		uint8_t* CopyFile(uint8_t* shaderSrc, int shaderLen);
		int LoadProgram(uint8_t* vertexShaderBuf, int vertexShaderSz, uint8_t* fragmentShaderBuf, int fragmentShaderSz);

		ShaderProgram(char* vertexShaderPath, char* fragmentShaderPath);
		ShaderProgram(uint8_t* vertexShaderBuf, int vertexShaderSz, uint8_t* fragmentShaderBuf, int fragmentShaderSz);
		~ShaderProgram();
	};
}

#endif