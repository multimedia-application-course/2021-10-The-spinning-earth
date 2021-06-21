#pragma once
#include<string>
#include<unordered_map>
#include"GL/glew.h"
#include"glm/glm.hpp"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};


class Shader
{
private	:
	std::string m_FilePath;
	unsigned int m_RendererID;
	mutable std::unordered_map<std::string, GLint> m_UniformLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	//Set uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
private:
	/* 创建一个平台，在这个平台上，编译顶点着色器和片元着色器 */
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	/* 根据shader类型编译shader代码 */
	unsigned int CompileShader(unsigned int type, const std::string& source);
	/* 读取shader文件 */
	ShaderProgramSource ParseShader(const std::string& filepath);
	int GetUniformLocation(const std::string& name) const;
};