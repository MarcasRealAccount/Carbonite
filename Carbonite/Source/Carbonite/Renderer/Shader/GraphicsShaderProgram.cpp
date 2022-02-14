#include "GraphicsShaderProgram.h"

#include "Graphics/Device/Device.h"

GraphicsShaderProgram::GraphicsShaderProgram(Graphics::Device& device, Graphics::RenderPass& renderPass)
    : m_PipelineLayout(device),
      m_Pipeline(renderPass, m_PipelineLayout),
      m_DescriptorSetLayout(device),
      m_DescriptorPool(device)
{
}

void GraphicsShaderProgram::updateShaderData()
{
	if (!m_DescriptorSetLayout.create())
		throw std::runtime_error("Failed to create vulkan descriptor set layout");
	m_DescriptorSetLayout.getDevice().setDebugName(m_DescriptorSetLayout, "m_DescriptorSetLayout");


}