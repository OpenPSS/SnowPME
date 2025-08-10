#ifndef LIB_PSS_SHADERPROGRAM_H
#define LIB_PSS_SHADERPROGRAM_H 1
#include <string>
#include <vector>
#include <Sce/Pss/Core/Graphics/GraphicsObject.hpp>
#include <Sce/Pss/Core/Graphics/ShaderProgramOption.hpp>
#include <Sce/Pss/Core/Graphics/ShaderAttributeType.hpp>
#include <Sce/Pss/Core/PsmObject.hpp>

namespace Sce::Pss::Core::Graphics {

	class ShaderProgram : public GraphicsObject<ShaderProgram> {
	private:
		uint8_t* vertexCgx = nullptr;
		uint8_t* fragmentCgx = nullptr;
		int vertexCgxLen = 0;
		int fragmentCgxLen = 0;

		std::string fragmentSrc = "";
		std::string vertexSrc = "";
		std::unique_ptr<ShaderProgramOption> programOptions = nullptr;

		std::vector<std::string> attributeBindings; 


		int compileShader(int type, const char* source);
	public:
		int UniformCount();
		int AttributeCount();

		uint8_t* LoadFile(char* shaderPath, int* shaderLen);
		uint8_t* CopyOrMove(uint8_t* shaderSrc, int shaderLen);
		int LoadProgram(uint8_t* vertexShaderBuf, int vertexShaderSz, uint8_t* fragmentShaderBuf, int fragmentShaderSz);

		ShaderProgram(char* vertexShaderPath, char* fragmentShaderPath);
		ShaderProgram(uint8_t* vertexShaderBuf, int vertexShaderSz, uint8_t* fragmentShaderBuf, int fragmentShaderSz);
		~ShaderProgram();

		int FindAttribute(std::string& name);
		int SetAttributeBinding(int index, std::string& name);
		std::string GetAttributeBinding(int index) const;
		std::string GetAttributeName(int index) const;
		ShaderAttributeType GetAttributeType(int index) const;
		int GetAttributeLocation(std::string& name) const;
		int GetAttributeStream(int index) const;

		std::string GetUniformName(int index);

		std::vector<ProgramUniform> Uniforms;
		std::vector<ProgramAttribute> Attributes;

	};
}

#endif