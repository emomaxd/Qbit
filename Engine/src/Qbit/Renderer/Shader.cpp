#include "Shader.hpp"

#include <sstream>
#include <fstream>
#include <iostream>
#include <gtc/type_ptr.hpp>



ShaderProgramSource Shader::ParseShader(const std::string& filepath) {
	std::ifstream stream(filepath);

	enum class ShaderType {
		NONE     = -1,
		VERTEX   = 0,
		FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else {
			ss[(int)type] << line << "\n";
		}
	}

	return { ss[0].str(), ss[1].str() };


}


Shader::Shader(std::string filepath) : m_filepath(filepath), m_rendererID(0) {
	auto source = ParseShader(filepath);
	m_rendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader() {
	glDeleteProgram(m_rendererID);
}

void Shader::Bind() const {
	glUseProgram(m_rendererID);
}

void Shader::UnBind() const {
	glUseProgram(0);
}

GLuint Shader::CompileShader(GLuint type, const std::string& source) {
	GLuint id = glCreateShader(type);
	const char* src = source.c_str();
	//std::cout << source << std::endl;
	glShaderSource(id, 1, &src, NULL);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader";

		std::cout << message << std::endl;

		glDeleteShader(id);
		return 0;
	}
	return id;
}

GLuint Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
	GLuint program = glCreateProgram();
	GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}


void Shader::AddUniform(const std::string& uniformName) {

	m_uniform[uniformName] = glGetUniformLocation(m_rendererID, uniformName.c_str());
	
}

void Shader::setUniformInteger(const std::string& uniformName, int value) {
	glUniform1i(glGetUniformLocation(m_rendererID, uniformName.c_str()), value);
}

void Shader::setUniformFloat(const std::string& uniformName, float value) {
	glUniform1f(glGetUniformLocation(m_rendererID, uniformName.c_str()), value);
}

void Shader::setVec3(const std::string& uniformName, const glm::vec3& value) {
	glUniform3f(glGetUniformLocation(m_rendererID, uniformName.c_str()), value.x, value.y, value.z);
}


void Shader::setVec4(const std::string& uniformName, const glm::vec4& value) {
	glUniform4f(glGetUniformLocation(m_rendererID, uniformName.c_str()), value.r, value.g, value.b, value.a);
}

void Shader::setMat3(const std::string& uniformName, const glm::mat3* value) {
	glUniformMatrix3fv(glGetUniformLocation(m_rendererID, uniformName.c_str()), 1, GL_FALSE, (GLfloat*)value);
}

void Shader::setMat4(const std::string& uniformName, const glm::mat4* value) {
	glUniformMatrix4fv(glGetUniformLocation(m_rendererID, uniformName.c_str()), 1, GL_FALSE, (GLfloat*)value);
}
