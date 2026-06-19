#ifndef LIB_PSS_SHADERPROGRAM_H
#define LIB_PSS_SHADERPROGRAM_H 1
#include <string>
#include <vector>
#include <Sce/Pss/Core/Graphics/GraphicsObject.hpp>
#include <Sce/Pss/Core/Graphics/ShaderProgramOption.hpp>
#include <Sce/Pss/Core/Graphics/CGX/ShaderAttributeType.hpp>
#include <Sce/Pss/Core/Graphics/CGX/ShaderUniformType.hpp>
#include <Sce/Pss/Core/Graphics/CGX/CGXParser.hpp>
#include <Sce/Pss/Core/PsmObject.hpp>

namespace Sce::Pss::Core::Graphics {

	enum class ShaderType : uint32_t {
		Vertex = 0,
		Fragment = 1
	};

	class ShaderProgram : public GraphicsObject<ShaderProgram> {
	private:
		uint8_t* vertexCgx = nullptr;
		uint8_t* fragmentCgx = nullptr;
		int vertexCgxLen = 0;
		int fragmentCgxLen = 0;

		std::string fragmentSrc = "";
		std::string vertexSrc = "";
		std::unique_ptr<ShaderProgramOption> programOptions = nullptr;

		Sce::Pss::Core::Graphics::CGX::ShaderUniformType glUniformTypeToPsmType(int glType);
		Sce::Pss::Core::Graphics::CGX::ShaderAttributeType glAttributeTypeToPsmType(int glType);
	public:
		int UniformCount();
		int AttributeCount();

		uint8_t* LoadFile(char* shaderPath, int* shaderLen);
		uint8_t* CopyOrMove(uint8_t* shaderSrc, int shaderLen);
		int LoadProgram(uint8_t* vertexShaderBuf, int vertexShaderSz, uint8_t* fragmentShaderBuf, int fragmentShaderSz, ShaderProgramOption* option);
		int LoadShader(int type, const char* source);
		bool ParseParams(Sce::Pss::Core::Graphics::CGX::VariantEntry* entry, ShaderType type, bool chk);
		int CheckParameters();
		int CheckSamplers();

		ShaderProgram(char* vertexShaderPath, char* fragmentShaderPath);
		ShaderProgram(uint8_t* vertexShaderBuf, int vertexShaderSz, uint8_t* fragmentShaderBuf, int fragmentShaderSz);
		~ShaderProgram();

		int FindAttribute(std::string& name);
		int FindUniform(std::string& name);

		std::string GetAttributeBinding(int index) const;
		std::string GetAttributeName(int index) const;
		std::string GetUniformName(int index) const;

		Sce::Pss::Core::Graphics::CGX::ShaderAttributeType GetAttributeType(int index) const;
		Sce::Pss::Core::Graphics::CGX::ShaderUniformType GetUniformType(int index) const;
		int GetAttributeLocation(std::string& name);
		int GetAttributeStream(int index) const;
		int GetUniformTexture(int index) const;
		int GetUniformSize(int index) const;
		int GetAttributeSize(int index) const;

		int SetAttributeBinding(int index, std::string& name);
		int SetUniformBinding(int index, std::string& name);
		int SetAttributeStream(int index, int stream);
		int SetUniformValue(int index, void* value, int vectorsize, Sce::Pss::Core::Graphics::CGX::ShaderUniformType type, int offset, int stream, int count);
		
		static int GetUniformTypeVectorSize(Sce::Pss::Core::Graphics::CGX::ShaderUniformType type);

		std::vector<ProgramUniform> Uniforms;
		std::vector<ProgramAttribute> Attributes;

	};
}

#endif