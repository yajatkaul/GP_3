#include "Shader.h"

#include "Renderer.h"

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath)
{
    string vp = ParseShader(vertexPath);
    string fp = ParseShader(fragmentPath);

    m_RendererID = CreateShader(vp, fp);
    glUseProgram(m_RendererID);
}

Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}

string Shader::ParseShader(const string &filepath)
{
    ifstream file(filepath);
    if (!file)
    {
        cout << "Error opening file!" << endl;
    }

    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

unsigned int Shader::CompileShader(unsigned int type, const string &soruce)
{
    unsigned int id = glCreateShader(type);
    const char *src = soruce.c_str();

    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (!result)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)alloca(length * sizeof(char));

        glGetShaderInfoLog(id, length, &length, message);

        cout << "Failed to compile  " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << "shader!" << endl;
        cout << message << endl;

        glDeleteShader(id);
    }

    return id;
}

unsigned int Shader::CreateShader(const string &vertexShader, const string &fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void Shader::SetUnifrom1f(const std::string &name, float v0, float v1, float v2, float v3)
{
    glUniform4f(GetUnifromLocation(name), v0, v1, v2, v3);
}

void Shader::SetUnifromMatrix4fv(const string &name, int count, bool transpose, float *value)
{
    glUniformMatrix4fv(GetUnifromLocation(name), count, transpose, value);
}

int Shader::GetUnifromLocation(const std::string &name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
    {
        return m_UniformLocationCache[name];
    }

    int location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location == -1)
    {
        std::cout << "Warning: unifrom" << name << "Doesnt exist!" << std::endl;
    }
    else
    {
        m_UniformLocationCache[name] = location;
    }
    return location;
}