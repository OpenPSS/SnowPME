#ifndef LIB_PSS_SHADERPROGRAM_H
#define LIB_PSS_SHADERPROGRAM_H 1
#include <string>
#include <vector>
#include <Sce/Pss/Core/Graphics/GraphicsObject.hpp>
#include <Sce/Pss/Core/Graphics/ShaderProgramOption.hpp>
#include <Sce/Pss/Core/Graphics/ShaderAttributeType.hpp>

namespace Sce::Pss::Core::Graphics {

	class ShaderProgram : public GraphicsObject {
	private:
		uint8_t* vertexCgx = nullptr;
		uint8_t* fragmentCgx = nullptr;
		int vertexCgxLen = NULL;
		int fragmentCgxLen = NULL;

		std::string fragmentSrc = "";
		std::string vertexSrc = "";
		ShaderProgramOption* programOptions;

		std::unordered_map<int, std::string> attributeBindings; 

		int compileShader(int type, char* source);
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

		void SetAttributeBinding(int index, std::string& name);
		std::string GetAttributeBinding(int index) const;
		const inline std::unordered_map<int, std::string>& GetAttributeBindings() const {
			return attributeBindings;
		}
		int GetAttributeType(int index, ShaderAttributeType* attributeType);

		int GetUniformName(int index, std::string& uniformName) const;
	};
}

#endif