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
    int GetUnifromLocation(const string &name);
    unordered_map<string, int> m_UniformLocationCache;

public:
    Shader(const string &vertexPath, const string &fragmentPath);
    ~Shader();
    void SetUnifrom1f(const string &name, float v0, float v1, float v2, float v3);
    void SetUnifromMatrix4fv(const string &name, int count, bool transpose, float *value);
    unsigned int m_RendererID;
};
