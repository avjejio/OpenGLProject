#pragma once

#include <string>
#include <unordered_map>

class Shader {
public:
	Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform1i(const std::string& name, int v);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocations;

	int GetUniformLocation(const std::string& name);

	std::string ReadFromFile(const std::string& path);
	unsigned int CreateShader(int type, const char* src, const char* compileErrMsg);
	unsigned int CompileShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
};