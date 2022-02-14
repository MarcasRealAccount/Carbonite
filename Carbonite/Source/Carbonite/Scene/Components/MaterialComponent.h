#pragma once

#include "Carbonite/Renderer/Shader/Material.h"

#include <vector>

struct MaterialComponent
{
public:
	MaterialComponent()                         = default;
	MaterialComponent(const MaterialComponent&) = default;
	MaterialComponent(MaterialComponent&&)      = default;
	MaterialComponent(Material* material);

public:
	Material* m_Material = nullptr;
};