#include "PsmShaderProgram.hpp"

namespace Sce::PlayStation::Core::Graphics {
	int PsmShaderProgram::FromFile(string vpFileName, string fpFileName, string* constKeys, int* constVals, int *result){
		cout << "Sce::PlayStation::Core::Graphics::FromFile(string, string, string*, int*, int *) Unimplemented." << endl;
		return 0;
	}
	int PsmShaderProgram::FromImage(byte* vpFileName, byte* fpFileImage, string* constKeys, int* constVals, int *result){
		cout << "Sce::PlayStation::Core::Graphics::FromImage(byte*, byte*, string*, int*, int *) Unimplemented." << endl;
		return 0;
	}
	int PsmShaderProgram::Delete(int handle){
		cout << "Sce::PlayStation::Core::Graphics::Delete(int) Unimplemented." << endl;
		return 0;
	}
	int PsmShaderProgram::AddRef(int handle){
		cout << "Sce::PlayStation::Core::Graphics::AddRef(int) Unimplemented." << endl;
		return 0;
	}
	int PsmShaderProgram::GetUniformCount(int handle, int* result){
		cout << "Sce::PlayStation::Core::Graphics::GetUniformCount(int, int *) Unimplemented." << endl;
		return 0;
	}
	int PsmShaderProgram::GetAttributeCount(int handle, int* result){
		cout << "Sce::PlayStation::Core::Graphics::GetAttributeCount(int, int *) Unimplemented." << endl;
		return 0;
	}
	int PsmShaderProgram::FindUniform(int handle, string name, int* result){
		cout << "Sce::PlayStation::Core::Graphics::FindUniform(int, string, int *) Unimplemented." << endl;
		return 0;
	}
	int PsmShaderProgram::FindAttribute(int handle, string name, int* result) {
		cout << "Sce::PlayStation::Core::Graphics::FindAttribute(int, string, int *) Unimplemented." << endl;
		return 0;
	}
	int PsmShaderProgram::GetUniformBinding(int handle, int index, string* result) {
		cout << "Sce::PlayStation::Core::Graphics::GetUniformBinding(int, int, string *) Unimplemented." << endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformBinding(int handle, int index, string name) {
		cout << "Sce::PlayStation::Core::Graphics::SetUniformBinding(int, int, string) Unimplemented." << endl;
		return 0;
	}
	int PsmShaderProgram::GetAttributeBinding(int handle, int index, string* result) {
		cout << "Sce::PlayStation::Core::Graphics::GetAttributeBinding(int, int, string *) Unimplemented." << endl;
		return 0;
	}
	int PsmShaderProgram::SetAttributeBinding(int handle, int index, string name) {
		cout << "Sce::PlayStation::Core::Graphics::SetAttributeBinding(int, int, string) Unimplemented." << endl;
		return 0;
	}
	int PsmShaderProgram::GetUniformType(int handle, int index, ShaderUniformType* result) {
		cout << "Sce::PlayStation::Core::Graphics::GetUniformType(int, int, Sce::PlayStation::Core::Graphics::ShaderUniformType *) Unimplemented." << endl;
		return 0;
	}
	int PsmShaderProgram::GetAttributeType(int handle, int index, ShaderAttributeType* result) {
		cout << "Sce::PlayStation::Core::Graphics::GetAttributeType(int, int, Sce::PlayStation::Core::Graphics::ShaderAttributeType *) Unimplemented." << endl;
		return 0;
	}
	int PsmShaderProgram::GetUniformName(int handle, int index, string* result){
		cout << "Sce::PlayStation::Core::Graphics::GetUniformName(int, int, string *) Unimplemented." << endl;
		return 0;
	}
	int PsmShaderProgram::GetAttributeName(int handle, int index, string* result) {
		cout << "Sce::PlayStation::Core::Graphics::GetAttributeName(int, int, string *) Unimplemented." << endl;
		return 0;
	}
	int PsmShaderProgram::GetUniformSize(int handle, int index, int* result) {
		cout << "Sce::PlayStation::Core::Graphics::GetUniformSize(int, int, int *) Unimplemented." << endl;
		return 0;
	}
	int PsmShaderProgram::GetAttributeSize(int handle, int index, int* result) {
		cout << "Sce::PlayStation::Core::Graphics::GetAttributeSize(int, int, int *) Unimplemented." << endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValueMatrix4(int handle, int index, int, Matrix4* value, ShaderUniformType type) {
		cout << "Sce::PlayStation::Core::Graphics::SetUniformValue(int, int, int, Sce::PlayStation::Core::Matrix4 *, Sce::PlayStation::Core::Graphics::ShaderUniformType) Unimplemented." << endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValueVector4(int handle, int index, int, Vector4* value, ShaderUniformType type) {
		cout << "Sce::PlayStation::Core::Graphics::SetUniformValue(int, int, int, Sce::PlayStation::Core::Vector4 *, Sce::PlayStation::Core::Graphics::ShaderUniformType) Unimplemented." << endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValueVector3(int handle, int index, int, Vector3* value, ShaderUniformType type) {
		cout << "Sce::PlayStation::Core::Graphics::SetUniformValue(int, int, int, Sce::PlayStation::Core::Vector3 *, Sce::PlayStation::Core::Graphics::ShaderUniformType) Unimplemented." << endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValueVector2(int handle, int index, int, Vector2* value, ShaderUniformType type) {
		cout << "Sce::PlayStation::Core::Graphics::SetUniformValue(int, int, int, Sce::PlayStation::Core::Vector2 *, Sce::PlayStation::Core::Graphics::ShaderUniformType) Unimplemented." << endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValueFloat(int handle, int index, int, float* value, ShaderUniformType type) {
		cout << "Sce::PlayStation::Core::Graphics::SetUniformValue(int, int, int, float *, Sce::PlayStation::Core::Graphics::ShaderUniformType) Unimplemented." << endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValueInt(int handle, int index, int, int* value, ShaderUniformType type) {
		cout << "Sce::PlayStation::Core::Graphics::SetUniformValue(int, int, int, int *, Sce::PlayStation::Core::Graphics::ShaderUniformType) Unimplemented." << endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValue2Matrix4(int handle, int index, Matrix4* value, ShaderUniformType type, int to, int from, int count) {
		cout << "Sce::PlayStation::Core::Graphics::SetUniformValue2(int, int, Sce::PlayStation::Core::Matrix4*, Sce::PlayStation::Core::Graphics::ShaderUniformType, int, int, int) Unimplemented." << endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValue2Vector4(int handle, int index, Vector4* value, ShaderUniformType type, int to, int from, int count) {
		cout << "Sce::PlayStation::Core::Graphics::SetUniformValue2(int, int, Sce::PlayStation::Core::Vector4*, Sce::PlayStation::Core::Graphics::ShaderUniformType, int, int, int) Unimplemented." << endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValue2Vector3(int handle, int index, Vector3* value, ShaderUniformType type, int to, int from, int count) {
		cout << "Sce::PlayStation::Core::Graphics::SetUniformValue2(int, int, Sce::PlayStation::Core::Vector3*, Sce::PlayStation::Core::Graphics::ShaderUniformType, int, int, int) Unimplemented." << endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValue2Vector2(int handle, int index, Vector2* value, ShaderUniformType type, int to, int from, int count) {
		cout << "Sce::PlayStation::Core::Graphics::SetUniformValue2(int, int, Sce::PlayStation::Core::Vector2*, Sce::PlayStation::Core::Graphics::ShaderUniformType, int, int, int) Unimplemented." << endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValue2Float(int handle, int index, float* value, ShaderUniformType type, int to, int from, int count) {
		cout << "Sce::PlayStation::Core::Graphics::SetUniformValue2(int, int, float*, Sce::PlayStation::Core::Graphics::ShaderUniformType, int, int, int) Unimplemented." << endl;
		return 0;
	}
	int PsmShaderProgram::SetUniformValue2Int(int handle, int index, int* value, ShaderUniformType type, int to, int from, int count) {
		cout << "Sce::PlayStation::Core::Graphics::SetUniformValue2(int, int, int*, Sce::PlayStation::Core::Graphics::ShaderUniformType, int, int, int) Unimplemented." << endl;
		return 0;
	}
	int PsmShaderProgram::SetAttributeValue2(int handle, int index, float* value) {
		cout << "Sce::PlayStation::Core::Graphics::SetAttributeValue2(int, int, float*) Unimplemented." << endl;
		return 0;
	}
	int PsmShaderProgram::GetUniformTexture(int handle, int index, int* result) {
		cout << "Sce::PlayStation::Core::Graphics::GetUniformTexture(int, int, int *) Unimplemented." << endl;
		return 0;
	}
	int PsmShaderProgram::GetAttributeStream(int handle, int index, int* result) {
		cout << "Sce::PlayStation::Core::Graphics::GetAttributeStream(int, int, int *) Unimplemented." << endl;
		return 0;
	}
	int PsmShaderProgram::SetAttributeStream(int handle, int index, int stream) {
		cout << "Sce::PlayStation::Core::Graphics::SetAttributeStream(int, int, int) Unimplemented." << endl;
		return 0;
	}
}
