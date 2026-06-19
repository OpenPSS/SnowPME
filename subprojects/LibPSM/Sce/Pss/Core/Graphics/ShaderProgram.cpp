#include <Sce/Pss/Core/Graphics/ShaderProgram.hpp>
#include <Sce/Pss/Core/ExceptionInfo.hpp>
#include <Sce/Pss/Core/Graphics/CGX/CGXParser.hpp>
#include <Sce/Pss/Core/Graphics/OpenGL.hpp>
#include <Sce/Pss/Core/Io/IoCall.hpp>
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <Sce/Pss/Core/Graphics/GlError.hpp>

#include <Sce/Pss/Core/Error.hpp>
#include <LibShared.hpp>
#include <glad/glad.h>
#include <string.h>

using namespace Shared::Windowing;
using namespace Shared::Debug;
using namespace Shared::String;

using namespace Sce::Pss::Core::Io;
using namespace Sce::Pss::Core::Memory;
using namespace Sce::Pss::Core::Graphics::CGX;

namespace Sce::Pss::Core::Graphics {

	int ShaderProgram::GetUniformTypeVectorSize(ShaderUniformType type)
	{
		switch (type) {
		case ShaderUniformType::Float:
			return 0x04;
		case ShaderUniformType::Float2:
			return 0x08;
		case ShaderUniformType::Float3:
			return 0x0C;
		case ShaderUniformType::Float4:
			return 0x10;
		case ShaderUniformType::Float2x2:
			return 0x10;
		case ShaderUniformType::Float3x3:
			return 0x24;
		case ShaderUniformType::Float4x4:
			return 0x40;
		case ShaderUniformType::Int:
			return 0x04;
		case ShaderUniformType::Int2:
			return 0x08;
		case ShaderUniformType::Int3:
			return 0x0C;
		case ShaderUniformType::Int4:
			return 0x10;
		case ShaderUniformType::Bool:
			return 0x04;
		case ShaderUniformType::Bool2:
			return 0x08;
		case ShaderUniformType::Bool3:
			return 0x0C;
		case ShaderUniformType::Bool4:
			return 0x10;
		case ShaderUniformType::Sampler2D:
			return 0x08;
		case ShaderUniformType::SamplerCube:
			return 0x0C;
		}

		UNREACHABLE();
	}
	ShaderAttributeType ShaderProgram::glAttributeTypeToPsmType(int glType)
	{
		switch (glType) {
		case GL_FLOAT:
			return ShaderAttributeType::Float;
		case GL_FLOAT_VEC2:
			return ShaderAttributeType::Float2;
		case GL_FLOAT_VEC3:
			return ShaderAttributeType::Float3;
		case GL_FLOAT_VEC4:
			return ShaderAttributeType::Float4;
		default:
			return ShaderAttributeType::None;
		}
		UNREACHABLE();
	}
	ShaderUniformType ShaderProgram::glUniformTypeToPsmType(int glType)
	{
		switch (glType) {
		case GL_FLOAT:
			return ShaderUniformType::Float;
		case GL_FLOAT_VEC2:
			return ShaderUniformType::Float2;
		case GL_FLOAT_VEC3:
			return ShaderUniformType::Float3;
		case GL_FLOAT_VEC4:
			return ShaderUniformType::Float4;
		case GL_INT:
			return ShaderUniformType::Int;
		case GL_INT_VEC2:
			return ShaderUniformType::Int2;
		case GL_INT_VEC3:
			return ShaderUniformType::Int3;
		case GL_INT_VEC4:
			return ShaderUniformType::Int4;
		case GL_BOOL:
			return ShaderUniformType::Bool;
		case GL_BOOL_VEC2:
			return ShaderUniformType::Bool2;
		case GL_BOOL_VEC3:
			return ShaderUniformType::Bool3;
		case GL_BOOL_VEC4:
			return ShaderUniformType::Bool4;
		case GL_FLOAT_MAT2:
			return ShaderUniformType::Float2x2;
		case GL_FLOAT_MAT3:
			return ShaderUniformType::Float3x3;
		case GL_FLOAT_MAT4:
			return ShaderUniformType::Float4x4;
		case GL_SAMPLER_2D:
			return ShaderUniformType::Sampler2D;
		case GL_SAMPLER_CUBE:
			return ShaderUniformType::SamplerCube;
		default:
			return ShaderUniformType::None;
		}
		UNREACHABLE();
	}

	int ShaderProgram::LoadShader(int type, const char* source) {
		
		int shader = glCreateShader(type);
		glShaderSource(shader, 1, &source, 0);
		glCompileShader(shader);

		int status = GL_FALSE;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

		if (status == GL_TRUE) {
			return shader;
		}
		else {
			char* log = reinterpret_cast<char*>(HeapAllocator::UniqueObject()->sce_psm_malloc(0x1000u));

			if (log != nullptr) {
				int sz = 0;

				glGetShaderInfoLog(shader, 0xFFFu, &sz, log);

				if (sz > 0xFFF) {
					sz = 0xFFF;
				}

				log[sz] = 0;

				ExceptionInfo::AddMessage(log);
				HeapAllocator::UniqueObject()->sce_psm_free(log);
			}
			glDeleteShader(shader);
			return 0;
		}
	}

	int ShaderProgram::ParseParams(VariantEntry* entry, ShaderType type)
	{
		if (type == ShaderType::Vertex)
			return 1;

		if (this->Attributes.size() > 0) {
			UNIMPLEMENTED_MSG("Calling ParseParams while attributes already initalized.");
		}

		Attributes.resize(entry->Attributes.size());
		for (int i = 0; i < entry->Attributes.size(); i++) {
			Attributes[i].Name = entry->Attributes[i].Name;
			Attributes[i].ESize = entry->Attributes[i].Size;
			Attributes[i].Flags = entry->Attributes[i].Flags;
			Attributes[i].Binding = -1;
			Attributes[i].Type = static_cast<ShaderUniformType>(entry->Attributes[i].Type);
			Attributes[i].Size = 0;

			// should be = 'attributeCount' after a whole lot of (seemingly) useless math, see IDA project; ParseParams?? 
			Attributes[i].Stream = 0;
			Attributes[i].Texture = -1;
			Attributes[i].Location = -1;
		}

		if (this->Uniforms.size() > 0) {
			UNIMPLEMENTED_MSG("Calling ParseParams while attributes already initalized.");
		}

		Uniforms.resize(entry->Uniforms.size());
		for (int i = 0; i < entry->Uniforms.size(); i++) {
			Uniforms[i].Name = entry->Uniforms[i].Name;
			Uniforms[i].ESize = entry->Uniforms[i].Size;
			Uniforms[i].Flags = entry->Uniforms[i].Flags;
			Uniforms[i].Binding = -1;
			Uniforms[i].Type = entry->Uniforms[i].Type;
			Uniforms[i].Size = 0;

			// should be = 'attributeCount' after a whole lot of (seemingly) useless math, see IDA project; ParseParams?? 
			Uniforms[i].Stream = 0;
			Uniforms[i].Texture = -1;
			Uniforms[i].Location = -1;
		}

		UNIMPLEMENTED_MSG("Implement sampler2d part; and error checking.");


	}

	int ShaderProgram::CheckParameters()
	{
		// initalize all attributes and uniforms
		// 

		int nameLen;
		int size;
		char name[0x100];
		GLenum type = 0;

		// uniforms ...

		int totalUniforms = 0;
		glGetProgramiv(this->GLHandle, GL_ACTIVE_UNIFORMS, &totalUniforms);
		for (int i = 0; i < totalUniforms; i++) {
			glGetActiveUniform(this->GLHandle, i, sizeof(name), &nameLen, &size, &type, name);

			std::string normalizedName = std::string(name);
			size_t pos = normalizedName.find('[');
			if (pos != std::string::npos) {
				normalizedName = normalizedName.substr(pos, normalizedName.find(']'));
			}


			Uniforms[i].Location = glGetUniformLocation(this->GLHandle, name);
			Uniforms[i].Index = i;
			Uniforms[i].Name = normalizedName;
			Uniforms[i].Size = size;

			if (Uniforms[i].ESize < size)
				Uniforms[i].ESize = size;


			Logger::Debug("Uniforms[" + Format::Hex(i) + "].Location // " + Format::Hex(Uniforms[i].Location));
			Logger::Debug("Uniforms[" + Format::Hex(i) + "].Index // " + Format::Hex(Uniforms[i].Index));
			Logger::Debug("Uniforms[" + Format::Hex(i) + "].Binding // " + Format::Hex(Uniforms[i].Binding));
			Logger::Debug("Uniforms[" + Format::Hex(i) + "].Name // " + Uniforms[i].Name);
			Logger::Debug("Uniforms[" + Format::Hex(i) + "].Type // " + Format::Hex((int)Uniforms[i].Type));
			Logger::Debug("Uniforms[" + Format::Hex(i) + "].Size // " + Format::Hex(Uniforms[i].Size));
			Logger::Debug("Uniforms[" + Format::Hex(i) + "].ESize // " + Format::Hex(Uniforms[i].ESize));
		}
		
		// attributes ...

		int totalAttributes = 0;
		glGetProgramiv(this->GLHandle, GL_ACTIVE_ATTRIBUTES, &totalAttributes);
		for (int i = 0; i < totalAttributes; i++) {

			glGetActiveAttrib(this->GLHandle, i, sizeof(name), &nameLen, &size, &type, name);

			std::string normalizedName = std::string(name);
			size_t pos = normalizedName.find('[');
			if (pos != std::string::npos) {
				normalizedName = normalizedName.substr(pos, normalizedName.find(']'));
			}

			Attributes[i].Location = glGetAttribLocation(this->GLHandle, name);
			Attributes[i].Index = i;
			Attributes[i].Name = normalizedName;
			Attributes[i].Size = size;

			if (Attributes[i].ESize < size)
				Attributes[i].ESize = size;

			Logger::Debug("Attributes[" + Format::Hex(i) + "].Location // " + Format::Hex(Attributes[i].Location));
			Logger::Debug("Attributes[" + Format::Hex(i) + "].Index // " + Format::Hex(Attributes[i].Index));
			Logger::Debug("Attributes[" + Format::Hex(i) + "].Binding // " + Format::Hex(Attributes[i].Binding));
			Logger::Debug("Attributes[" + Format::Hex(i) + "].Name // " + Attributes[i].Name);
			Logger::Debug("Attributes[" + Format::Hex(i) + "].Type // " + Format::Hex((int)Attributes[i].Type));
			Logger::Debug("Attributes[" + Format::Hex(i) + "].Size // " + Format::Hex(Attributes[i].Size));
			Logger::Debug("Attributes[" + Format::Hex(i) + "].ESize // " + Format::Hex(Attributes[i].ESize));
		}

		return 1;
	}

	int ShaderProgram::CheckSamplers()
	{
		UNIMPLEMENTED();
	}


	int ShaderProgram::LoadProgram(uint8_t* vertexShaderBuf, int vertexShaderSz, uint8_t* fragmentShaderBuf, int fragmentShaderSz, ShaderProgramOption* option) {

		if (vertexShaderBuf != nullptr) {
			std::unique_ptr<CGX::CGXParser> cgxFile = std::make_unique<CGX::CGXParser>(vertexShaderBuf, vertexShaderSz);
			RETURN_ERRORABLE_SMARTPTR(cgxFile);

			std::string src = cgxFile->FindVertexShader("GLSL");
			RETURN_ERRORABLE_SMARTPTR(cgxFile);
			this->vertexSrc = src;

			if(fragmentShaderBuf == nullptr) {
				std::string src = cgxFile->FindFragmentShader("GLSL");
				RETURN_ERRORABLE_SMARTPTR(cgxFile);
				this->fragmentSrc = src;

			}

			this->ParseParams(cgxFile->VertexVariants.get(), ShaderType::Vertex);
			this->ParseParams(cgxFile->FragmentVariants.get(), ShaderType::Fragment);

		}

		if (fragmentShaderBuf != nullptr) {
			std::unique_ptr<CGXParser> cgxFile = std::make_unique<CGXParser>(fragmentShaderBuf, fragmentShaderSz);
			RETURN_ERRORABLE_SMARTPTR(cgxFile);

			std::string src = cgxFile->FindFragmentShader("GLSL");
			RETURN_ERRORABLE_SMARTPTR(cgxFile);
			this->fragmentSrc = src;

			this->ParseParams(cgxFile->VertexVariants.get(), ShaderType::Vertex);
			this->ParseParams(cgxFile->FragmentVariants.get(), ShaderType::Fragment);
		}


		this->GLHandle = glCreateProgram();

		// in pure OGL, we have to append a version number to the start of the GL Shaders
		// this is not required in GLES; as 100 has the features we need already;
		// (as PSM assumes GLES GLSL or CG.)
		if (WindowControl::GetBackend() == "OpenGL") {
			this->fragmentSrc = "#version 120\r\nprecision mediump float;\r\n" + this->fragmentSrc;
			this->vertexSrc = "#version 120\r\nprecision mediump float;\r\n" + this->vertexSrc;
		}

		int compileFragmentShader = LoadShader(GL_FRAGMENT_SHADER, this->fragmentSrc.c_str());
		if (compileFragmentShader == 0)
		{
			this->SetError(PSM_ERROR_GRAPHICS_SYSTEM);
			return 0;
		}

		int compileVertexShader = LoadShader(GL_VERTEX_SHADER, this->vertexSrc.c_str());
		if (compileVertexShader == 0)
		{
			this->SetError(PSM_ERROR_GRAPHICS_SYSTEM);
			return 0;
		}

		glAttachShader(this->GLHandle, compileFragmentShader);
		glAttachShader(this->GLHandle, compileVertexShader);

		glLinkProgram(this->GLHandle);

		glDeleteShader(compileFragmentShader);
		glDeleteShader(compileVertexShader);

		int status = 0;
		glGetProgramiv(this->GLHandle, GL_LINK_STATUS, &status);

		if (status) {
			if (CheckParameters() && CheckSamplers()) {
				return this->GLHandle;
			}
			else {
				glDeleteProgram(this->GLHandle);
				this->GLHandle = 0;
				return 0;
			}
		}
		else {
			char* log = (char*)HeapAllocator::UniqueObject()->sce_psm_malloc(0x1000u);
			this->SetError(PSM_ERROR_COMMON_FILE_LOAD);

			if (log != nullptr) {
				int sz = 0;
				glGetProgramInfoLog(this->GLHandle, 0xFFF, &sz, log);

				if (sz > 0xFFF) {
					sz = 0xFFF;
				}

				log[sz] = 0;
				ExceptionInfo::AddMessage(log);


				HeapAllocator::UniqueObject()->sce_psm_free(log);
			}

			glDeleteProgram(this->GLHandle);
			return PSM_ERROR_NO_ERROR;
		}
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

	uint8_t* ShaderProgram::CopyOrMove(uint8_t* shaderSrc, int shaderLen) {
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
			this->vertexCgx = this->CopyOrMove(vertexShaderBuf, vertexShaderSz);
		}
		else {
			this->vertexCgx = nullptr;
		}

		if (fragmentShaderBuf != nullptr) {
			this->fragmentCgx = this->CopyOrMove(fragmentShaderBuf, fragmentShaderSz);
		}
		else {
			this->fragmentCgx = nullptr;
		}

		this->vertexCgxLen = vertexShaderSz;
		this->fragmentCgxLen = fragmentShaderSz;

		if (this->GetError() == PSM_ERROR_NO_ERROR) {
			this->GLHandle = this->LoadProgram(this->vertexCgx, this->vertexCgxLen, this->fragmentCgx, this->fragmentCgxLen, nullptr);
		}

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

		if (this->GetError() == PSM_ERROR_NO_ERROR) {
			this->GLHandle = this->LoadProgram(this->vertexCgx, this->vertexCgxLen, this->fragmentCgx, this->fragmentCgxLen, nullptr);
		}

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



	int ShaderProgram::FindUniform(std::string& name) {
		for (ProgramUniform uniform : this->Uniforms) {
			if (uniform.Name == name) {
				return uniform.Index;
			}
		}

		return -1;
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

		if (index > 0xff)
			return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;


		if (index < this->Attributes.size()) {
			index = this->Attributes[index].Index;
		}
		else {
			index = -1;
		}

		int nameIndex = -1;
		if (name != "") {
			int nameIndex = this->FindAttribute(name);
			if (nameIndex == -1) {
				ExceptionInfo::AddMessage("Attribute variable '" + name + "' is not found\n");
				return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;
			}
			nameIndex = this->Attributes[nameIndex].Index;
		}

		if (index >= 0)
			this->Attributes[index].Binding = -1;
		if (nameIndex >= 0)
			this->Attributes[nameIndex].Binding = index;

		return 0;
	}

	int ShaderProgram::SetUniformBinding(int index, std::string& name)
	{
		if (index > 0xff)
			return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;


		if (index < this->Uniforms.size()) {
			index = this->Uniforms[index].Index;
		}
		else {
			index = -1;
		}

		int nameIndex = -1;
		if (name != "") {
			int nameIndex = this->FindUniform(name);
			if (nameIndex == -1) {
				ExceptionInfo::AddMessage("Uniform variable '" + name + "' is not found\n");
				return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;
			}
			nameIndex = this->Uniforms[nameIndex].Index;
		}

		if (index >= 0)
			this->Uniforms[index].Binding = -1;
		if (nameIndex >= 0)
			this->Uniforms[nameIndex].Binding = index;

		return 0;
	}
	
	std::string ShaderProgram::GetAttributeBinding(int index) const 
	{
		if (this->Attributes[this->Attributes[index].Index].Binding >= 0) {
			return this->Attributes[this->Attributes[index].Index].Name;
		}
		else {
			return "";
		}
    }


	int ShaderProgram::GetAttributeStream(int index) const 
	{
		return this->Attributes[this->Uniforms[index].Index].Stream;
	}

	int ShaderProgram::GetAttributeSize(int index) const
	{
		return this->Attributes[this->Uniforms[index].Index].ESize;
	}

	int ShaderProgram::GetUniformTexture(int index) const
	{
		return this->Uniforms[this->Uniforms[index].Index].Texture;
	}

	int ShaderProgram::GetUniformSize(int index) const
	{
		return this->Uniforms[this->Uniforms[index].Index].ESize;
	}

	std::string ShaderProgram::GetAttributeName(int index) const
	{
		if (Attributes.size() <= static_cast<size_t>(index)) return "";
		return Attributes[this->Uniforms[index].Index].Name;
	}

	int ShaderProgram::GetAttributeLocation(std::string& name)
	{
		return this->Attributes[this->FindAttribute(name)].Location;
	}

	ShaderAttributeType ShaderProgram::GetAttributeType(int index) const
	{
		return (ShaderAttributeType)this->Attributes[Attributes[index].Index].Type;
	}

	ShaderUniformType ShaderProgram::GetUniformType(int index) const
	{
		return this->Uniforms[Uniforms[index].Index].Type;
	}

	std::string ShaderProgram::GetUniformName(int index) const {
		if (Uniforms.size() <= static_cast<size_t>(index)) return "";
		return Uniforms[Uniforms[index].Index].Name;
	}

	int ShaderProgram::SetAttributeStream(int index, int stream)
	{
		if(index < 0 || index >= static_cast<int>(this->Attributes.size()))
			return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;

		this->Attributes[index].Stream = stream;
		return PSM_ERROR_NO_ERROR;
	}

	int ShaderProgram::SetUniformValue(int index, void* value, int vectorsize, ShaderUniformType type, int offset, int stream, int count)
	{
		ProgramUniform* uniform = &this->Uniforms[this->Uniforms[index].Index];

		if(value == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;
		if (index < 0 || index >= static_cast<int>(this->Uniforms.size()))
			return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;

		if ( (uniform->Flags & 0x8000) != 0) { // Figure out what flags & 0x8000 is
			Logger::Debug("SetUniformValue RequiredExtension branch reached.");

			if (uniform->Type >= ShaderUniformType::Sampler2D) {
				ExceptionInfo::AddMessage("Sampler variable cannot set new value\n");
			}
			else {
				ExceptionInfo::AddMessage("Constantized variable cannot set new value\n");
			}

			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}

		if (type != uniform->Type) {
			Logger::Debug("SetUniformValue type does not match actual uniform type.");

			if (type == ShaderUniformType::Float && (uniform->Type < ShaderUniformType::Float || uniform->Type > ShaderUniformType::Float4x4)) {
				ExceptionInfo::AddMessage("Incompatible type with shader variable\n");
				return PSM_ERROR_COMMON_NOT_SUPPORTED;
			}
			else if(type == ShaderUniformType::Int && (Uniforms[index].Type < ShaderUniformType::Bool || Uniforms[index].Type > ShaderUniformType::Int4)) {
				ExceptionInfo::AddMessage("Incompatible type with shader variable\n");
				return PSM_ERROR_COMMON_NOT_SUPPORTED;
			}

			type = Uniforms[index].Type;
		}
	
		if (((count | stream | offset) & 0xFF000000) != 0  || offset + count > uniform->ESize)
			return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;

		if (GetUniformTypeVectorSize(type) * (stream + count) > vectorsize)
		{
			ExceptionInfo::AddMessage("Value argument has wrong size\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}

		if (count > uniform->Size - offset)
			count = uniform->Size - offset;

		ShaderProgram* prevShader = OpenGL::SetShaderProgram(this);

		switch (uniform->Type) {
			// float
			case ShaderUniformType::Float:
				glUniform1fv(offset + uniform->Location, count, (reinterpret_cast<float*>(value) + stream * GetUniformTypeVectorSize(type)));
				break;
			case ShaderUniformType::Float2:
				glUniform1fv(offset + uniform->Location, count, (reinterpret_cast<float*>(value) + stream * GetUniformTypeVectorSize(type)));
				break;
			case ShaderUniformType::Float3:
				glUniform1fv(offset + uniform->Location, count, (reinterpret_cast<float*>(value) + stream * GetUniformTypeVectorSize(type)));
				break;
			case ShaderUniformType::Float4:
				glUniform1fv(offset + uniform->Location, count, (reinterpret_cast<float*>(value) + stream * GetUniformTypeVectorSize(type)));
				break;

			// float matrix
			case ShaderUniformType::Float3x3:
				glUniformMatrix3fv(offset + uniform->Location, count, 0, (reinterpret_cast<float*>(value) + stream * GetUniformTypeVectorSize(type)));
				break;
			case ShaderUniformType::Float4x4:
				glUniformMatrix4fv(offset + uniform->Location, count, 0, (reinterpret_cast<float*>(value) + stream * GetUniformTypeVectorSize(type)));
				break;
			case ShaderUniformType::Float2x2:
				glUniformMatrix2fv(offset + uniform->Location, count, 0, (reinterpret_cast<float*>(value) + stream * GetUniformTypeVectorSize(type)));
				break;

			// int 
			case ShaderUniformType::Bool:
			case ShaderUniformType::Int:
				glUniform1iv(offset + uniform->Location, count, (reinterpret_cast<int*>(value) + stream * GetUniformTypeVectorSize(type)));
				break;
			case ShaderUniformType::Bool2:
			case ShaderUniformType::Int2:
				glUniform2iv(offset + uniform->Location, count, (reinterpret_cast<int*>(value) + stream * GetUniformTypeVectorSize(type)));
				break;
			case ShaderUniformType::Bool3:
			case ShaderUniformType::Int3:
				glUniform3iv(offset + uniform->Location, count, (reinterpret_cast<int*>(value) + stream * GetUniformTypeVectorSize(type)));
				break;
			case ShaderUniformType::Bool4:
			case ShaderUniformType::Int4:
				glUniform4iv(offset + uniform->Location, count, (reinterpret_cast<int*>(value) + stream * GetUniformTypeVectorSize(type)));
				break;

			default:
				Logger::Error("Unknown shader uniform type: " + Format::Hex(static_cast<int>(uniform->Type)));
				break;
			
		}

		OpenGL::SetShaderProgram(prevShader);
		return PSM_ERROR_NO_ERROR;

	}

}
