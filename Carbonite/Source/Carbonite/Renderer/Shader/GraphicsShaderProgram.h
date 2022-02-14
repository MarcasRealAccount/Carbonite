#pragma once

#include "Graphics/Pipeline/Descriptor/DescriptorPool.h"
#include "Graphics/Pipeline/Descriptor/DescriptorSet.h"
#include "Graphics/Pipeline/Descriptor/DescriptorSetLayout.h"
#include "Graphics/Pipeline/GraphicsPipeline.h"
#include "Graphics/Pipeline/PipelineLayout.h"
#include "Shader.h"

#include <vector>

struct GraphicsShaderProgram
{
public:
	GraphicsShaderProgram(Graphics::Device& device, Graphics::RenderPass& renderPass);

	void updateShaderData();

	auto& getPipelineLayout() { return m_PipelineLayout; }
	auto& getPipelineLayout() const { return m_PipelineLayout; }
	auto& getPipeline() { return m_Pipeline; }
	auto& getPipeline() const { return m_Pipeline; }
	auto& getDescriptorSetLayout() { return m_DescriptorSetLayout; }
	auto& getDescriptorSetLayout() const { return m_DescriptorSetLayout; }
	auto& getDescriptorPool() { return m_DescriptorPool; }
	auto& getDescriptorPool() const { return m_DescriptorPool; }
	auto& getDescriptorSets() { return m_DescriptorSets; }
	auto& getDescriptorSets() const { return m_DescriptorSets; }

public:
	std::vector<Shader> m_Shaders;

private:
	Graphics::PipelineLayout             m_PipelineLayout;
	Graphics::GraphicsPipeline           m_Pipeline;
	Graphics::DescriptorSetLayout        m_DescriptorSetLayout;
	Graphics::DescriptorPool             m_DescriptorPool;
	std::vector<Graphics::DescriptorSet> m_DescriptorSets;
};