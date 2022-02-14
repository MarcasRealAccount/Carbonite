#pragma once

#include "GraphicsShaderProgram.h"

struct Material
{
public:
	Material()                = default;
	Material(const Material&) = default;
	Material(Material&&)      = default;
	Material(GraphicsShaderProgram* shaderProgram);

public:
	GraphicsShaderProgram* m_ShaderProgram = nullptr;
};