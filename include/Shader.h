#pragma once

#include <string>
#include <Unordered_map>

using namespace std;

struct ShaderSources
{
    string VertexSource;
    string FragmentSource;
};

class Shader
{
private:
    unsigned int CreateShader(const string &vertexShader, const string &fragmentShader);
    string ParseShader(const string &filepath);
    unsigned int CompileShader(unsigned int type, const string &soruce);
    unsigned int m_RendererID;
    int GetUnifromLocation(const std::string &name);
    std::unordered_map<std::string, int> m_UniformLocationCache;

public:
    Shader(const std::string &vertexPath, const std::string &fragmentPath);
    ~Shader();
    void SetUnifrom1i(const std::string &name, float v0, float v1, float v2, float v3);
};
