#pragma once

#include <GL/glew.h>
#include <string>
#include <unordered_map>
#include <glm.hpp>

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader {
public:
	Shader() = default;
	Shader(std::string filepath);
	~Shader();

	void Bind() const;
	void UnBind() const;

	void AddUniform(const std::string& uniformName);

	void setUniformInteger(const std::string& uniformName, int value);
	void setUniformFloat(const std::string& uniformName, float value);
	void setVec3(const std::string& uniformName, const glm::vec3& value);
	void setVec4(const std::string& uniformName, const glm::vec4& value);
	void setMat3(const std::string& uniformName, const glm::mat3* value);
	void setMat4(const std::string& uniformName, const glm::mat4* value);


private:

	ShaderProgramSource ParseShader(const std::string& filepath);
	GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	GLuint CompileShader(GLuint type, const std::string& source);
private:

	GLuint m_rendererID;
	std::string m_filepath;
	std::unordered_map<std::string, GLuint> m_uniform;
};