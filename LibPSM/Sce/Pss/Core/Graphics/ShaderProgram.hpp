#ifndef LIB_PSM_SHADERPROGRAM_H
#define LIB_PSM_SHADERPROGRAM_H 1
#include <string>
#include <vector>
#include <Sce/Pss/Core/Errorable.hpp>

namespace Sce::Pss::Core::Graphics {

	typedef struct ProgramUniform {
		std::string Name;
		int Size;
		int Index;
		uint32_t Type;
		int Location;
		int Binding = -1;
	} ProgramUniform;

	typedef ProgramUniform ProgramAttribute;

	class ShaderProgram : public Errorable{
	private:
		int program;
		std::vector<ProgramUniform>* uniforms;
		std::vector<ProgramAttribute>* attributes;
		std::string vertexSourceCode;
		std::string fragmentSourceCode;
		int compileShader(int type, char* source);
	public:
		int Program();
		int UniformCount();
		int AttributeCount();
		std::vector<ProgramUniform>* Uniforms();
		std::vector<ProgramAttribute>* Attributes();

		ShaderProgram(std::string vertexSrc, std::string fragmentSrc);
		~ShaderProgram();
	};
}

#endif