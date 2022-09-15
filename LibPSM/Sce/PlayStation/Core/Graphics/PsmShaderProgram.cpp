#include "PsmShaderProgram.hpp"

namespace Sce::PlayStation::Core::Graphics {
	int PsmShaderProgram::FromFile(std::string vpFileName, std::string fpFileName, std::string* constKeys, int* constVals, int *result){
		std::cout << "Sce::PlayStation::Core::Graphics::FromFile(string, string, string*, int*, int *) Unimplemented." << std::endl;
		return 0;
	}
	int PsmShaderProgram::FromImage(std::byte* vpFileName, std::byte* fpFileImage, std::string* constKeys, int* constVals, int *result){
		std::cout << "Sce::PlayStation::Core::Graphics::FromImage(byte*, byte*, string*, int*, int *) Unimplemented." << std::endl;
		return 0;
	}
	int PsmShaderProgram::Delete(int handle){
		std::cout << "Sce::PlayStation::Core::Graphics::Delete(int) Unimplemented." << std::endl;
		return 0;
	}
	int PsmShaderProgram::AddRef(int handle){
		std::cout << "Sce::PlayStation::Core::Graphics::AddRef(int) Unimplemented." << std::endl;
		return 0;
	}
	int PsmShaderProgram::GetUniformCount(int handle, int* result){
		std::cout << "Sce::PlayStation::Core::Graphics::GetUniformCount(int, int *) Unimplemented." << std::endl;
		return 0;
	}
	int PsmShaderProgram::GetAttributeCount(int handle, int* result){
		std::cout << "Sce::PlayStation::Core::Graphics::GetAttributeCount(int, int *) Unimplemented." << std::endl;
		return 0;
	}
	int PsmShaderProgram::FindUniform(int handle, std::string name, int* result){
		std::cout << "Sce::PlayStation::Core::Graphics::FindUniform(int, string, int *) Unimplemented." << std::endl;
		return 0;
	}
	int PsmShaderProgram::FindAttribute(int handle, std::string name, int* result) {
		std::cout << "Sce::PlayStation::Core::Graphics::FindAttribute(int, string, int *) Unimplemented." << std::endl;
		return 0;
	}
	int PsmShaderProgram::GetUniformBinding(int handle, int index, std::string* result) {
		std::cout << "Sce::PlayStation::Core::Graphics::GetUniformBinding(int, int, string *) Unimplemented." << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformBinding(int handle, int index, std::string name) {
		std::cout << "Sce::PlayStation::Core::Graphics::SetUniformBinding(int, int, string) Unimplemented." << std::endl;
		return 0;
	}
	int PsmShaderProgram::GetAttributeBinding(int handle, int index, std::string* result) {
		std::cout << "Sce::PlayStation::Core::Graphics::GetAttributeBinding(int, int, string *) Unimplemented." << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetAttributeBinding(int handle, int index, std::string name) {
		std::cout << "Sce::PlayStation::Core::Graphics::SetAttributeBinding(int, int, string) Unimplemented." << std::endl;
		return 0;
	}
	int PsmShaderProgram::GetUniformType(int handle, int index, ShaderUniformType* result) {
		std::cout << "Sce::PlayStation::Core::Graphics::GetUniformType(int, int, Sce::PlayStation::Core::Graphics::ShaderUniformType *) Unimplemented." << std::endl;
		return 0;
	}
	int PsmShaderProgram::GetAttributeType(int handle, int index, ShaderAttributeType* result) {
		std::cout << "Sce::PlayStation::Core::Graphics::GetAttributeType(int, int, Sce::PlayStation::Core::Graphics::ShaderAttributeType *) Unimplemented." << std::endl;
		return 0;
	}
	int PsmShaderProgram::GetUniformName(int handle, int index, std::string* result){
		std::cout << "Sce::PlayStation::Core::Graphics::GetUniformName(int, int, string *) Unimplemented." << std::endl;
		return 0;
	}
	int PsmShaderProgram::GetAttributeName(int handle, int index, std::string* result) {
		std::cout << "Sce::PlayStation::Core::Graphics::GetAttributeName(int, int, string *) Unimplemented." << std::endl;
		return 0;
	}
	int PsmShaderProgram::GetUniformSize(int handle, int index, int* result) {
		std::cout << "Sce::PlayStation::Core::Graphics::GetUniformSize(int, int, int *) Unimplemented." << std::endl;
		return 0;
	}
	int PsmShaderProgram::GetAttributeSize(int handle, int index, int* result) {
		std::cout << "Sce::PlayStation::Core::Graphics::GetAttributeSize(int, int, int *) Unimplemented." << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValueMatrix4(int handle, int index, int, Matrix4* value, ShaderUniformType type) {
		std::cout << "Sce::PlayStation::Core::Graphics::SetUniformValue(int, int, int, Sce::PlayStation::Core::Matrix4 *, Sce::PlayStation::Core::Graphics::ShaderUniformType) Unimplemented." << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValueVector4(int handle, int index, int, Vector4* value, ShaderUniformType type) {
		std::cout << "Sce::PlayStation::Core::Graphics::SetUniformValue(int, int, int, Sce::PlayStation::Core::Vector4 *, Sce::PlayStation::Core::Graphics::ShaderUniformType) Unimplemented." << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValueVector3(int handle, int index, int, Vector3* value, ShaderUniformType type) {
		std::cout << "Sce::PlayStation::Core::Graphics::SetUniformValue(int, int, int, Sce::PlayStation::Core::Vector3 *, Sce::PlayStation::Core::Graphics::ShaderUniformType) Unimplemented." << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValueVector2(int handle, int index, int, Vector2* value, ShaderUniformType type) {
		std::cout << "Sce::PlayStation::Core::Graphics::SetUniformValue(int, int, int, Sce::PlayStation::Core::Vector2 *, Sce::PlayStation::Core::Graphics::ShaderUniformType) Unimplemented." << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValueFloat(int handle, int index, int, float* value, ShaderUniformType type) {
		std::cout << "Sce::PlayStation::Core::Graphics::SetUniformValue(int, int, int, float *, Sce::PlayStation::Core::Graphics::ShaderUniformType) Unimplemented." << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValueInt(int handle, int index, int, int* value, ShaderUniformType type) {
		std::cout << "Sce::PlayStation::Core::Graphics::SetUniformValue(int, int, int, int *, Sce::PlayStation::Core::Graphics::ShaderUniformType) Unimplemented." << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValue2Matrix4(int handle, int index, Matrix4* value, ShaderUniformType type, int to, int from, int count) {
		std::cout << "Sce::PlayStation::Core::Graphics::SetUniformValue2(int, int, Sce::PlayStation::Core::Matrix4*, Sce::PlayStation::Core::Graphics::ShaderUniformType, int, int, int) Unimplemented." << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValue2Vector4(int handle, int index, Vector4* value, ShaderUniformType type, int to, int from, int count) {
		std::cout << "Sce::PlayStation::Core::Graphics::SetUniformValue2(int, int, Sce::PlayStation::Core::Vector4*, Sce::PlayStation::Core::Graphics::ShaderUniformType, int, int, int) Unimplemented." << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValue2Vector3(int handle, int index, Vector3* value, ShaderUniformType type, int to, int from, int count) {
		std::cout << "Sce::PlayStation::Core::Graphics::SetUniformValue2(int, int, Sce::PlayStation::Core::Vector3*, Sce::PlayStation::Core::Graphics::ShaderUniformType, int, int, int) Unimplemented." << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValue2Vector2(int handle, int index, Vector2* value, ShaderUniformType type, int to, int from, int count) {
		std::cout << "Sce::PlayStation::Core::Graphics::SetUniformValue2(int, int, Sce::PlayStation::Core::Vector2*, Sce::PlayStation::Core::Graphics::ShaderUniformType, int, int, int) Unimplemented." << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValue2Float(int handle, int index, float* value, ShaderUniformType type, int to, int from, int count) {
		std::cout << "Sce::PlayStation::Core::Graphics::SetUniformValue2(int, int, float*, Sce::PlayStation::Core::Graphics::ShaderUniformType, int, int, int) Unimplemented." << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValue2Int(int handle, int index, int* value, ShaderUniformType type, int to, int from, int count) {
		std::cout << "Sce::PlayStation::Core::Graphics::SetUniformValue2(int, int, int*, Sce::PlayStation::Core::Graphics::ShaderUniformType, int, int, int) Unimplemented." << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetAttributeValue2(int handle, int index, float* value) {
		std::cout << "Sce::PlayStation::Core::Graphics::SetAttributeValue2(int, int, float*) Unimplemented." << std::endl;
		return 0;
	}
	int PsmShaderProgram::GetUniformTexture(int handle, int index, int* result) {
		std::cout << "Sce::PlayStation::Core::Graphics::GetUniformTexture(int, int, int *) Unimplemented." << std::endl;
		return 0;
	}
	int PsmShaderProgram::GetAttributeStream(int handle, int index, int* result) {
		std::cout << "Sce::PlayStation::Core::Graphics::GetAttributeStream(int, int, int *) Unimplemented." << std::endl;
		return 0;
	}
	int PsmShaderProgram::SetAttributeStream(int handle, int index, int stream) {
		std::cout << "Sce::PlayStation::Core::Graphics::SetAttributeStream(int, int, int) Unimplemented." << std::endl;
		return 0;
	}
}
