#pragma once
#include <GL/glew.h>
#include <stdio.h>
#include <windows.h>

#define SKYBOX_VERTEX_SHADER "C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/Shaders/SkyboxVertexShader.txt"
#define SKYBOX_FRAGMENT_SHADER "C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/Shaders/SkyboxFragmentShader.txt"
#define LIGHT_VERTEX_SHADER "C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/Shaders/LightVertexShader.txt"
#define LIGHT_FRAGMENT_SHADER "C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/Shaders/LightFragmentShader.txt"
#define LIGHT_VERTEX_SHADER2 "C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/Shaders/LightVertexShader2.txt"
#define LIGHT_FRAGMENT_SHADER2 "C:/Users/Robert/Documents/Visual Studio 2015/Projects/CS4052 Lab 1/CS4052 Lab 1/Shaders/LightFragmentShader2.txt"

class Shader {
public:
	Shader(const char* VertFileName, const char* FragFileName);

	char* ReadShaderSource(const char* shaderFile);
    void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	GLuint CompileShaders();

private: 
	const char* vertFileName;
	const char* fragFileName;
	GLuint shaderProgramID;
};
