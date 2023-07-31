#ifndef LIB_PSS_SHADERPROGRAM_H
#define LIB_PSS_SHADERPROGRAM_H 1
#include <string>
#include <vector>
#include <Sce/Pss/Core/Graphics/GraphicsObject.hpp>
#include <Sce/Pss/Core/Graphics/ShaderProgramOption.hpp>

namespace Sce::Pss::Core::Graphics {


	class ShaderProgram : public GraphicsObject {
	private:
		std::byte* cgxData = nullptr;
		std::byte* vertexCgx = nullptr;
		std::byte* fragmentCgx = nullptr;
		int vertexCgxLen;
		int fragmentCgxLen;

		std::vector<ProgramUniform> uniforms;
		std::vector<ProgramAttribute> attributes;
		int compileShader(int type, char* source);

		ShaderProgramOption* programOptions;
	public:
		int ActiveStateChanged(bool state);
		int UniformCount();
		int AttributeCount();

		std::vector<ProgramUniform>* Uniforms();
		std::vector<ProgramAttribute>* Attributes();

		std::byte* LoadFile(char* shaderPath, int* shaderLen);
		std::byte* CopyFile(std::byte* shaderSrc, int shaderLen);
		int LoadProgram(std::byte* vertexShaderBuf, int vertexShaderSz, std::byte* fragmentShaderBuf, int fragmentShaderSz);

		ShaderProgram(char* vertexShaderPath, char* fragmentShaderPath);
		ShaderProgram(std::byte* vertexShaderBuf, int vertexShaderSz, std::byte* fragmentShaderBuf, int fragmentShaderSz);
		~ShaderProgram();
	};
}

#endif