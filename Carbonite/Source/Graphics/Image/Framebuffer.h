#pragma once

#include "Graphics/Common.h"

namespace Graphics
{
	struct RenderPass;
	struct ImageView;

	struct Framebuffer : public Handle<vk::Framebuffer, true, true>
	{
	public:
		Framebuffer(RenderPass& renderPass);
		~Framebuffer();

		auto& getRenderPass() { return m_RenderPass; }
		auto& getRenderPass() const { return m_RenderPass; }

	private:
		virtual void createImpl() override;
		virtual bool destroyImpl() override;

	public:
		std::vector<ImageView*> m_Attachments;

		std::uint32_t m_Width  = 1;
		std::uint32_t m_Height = 1;
		std::uint32_t m_Layers = 1;

	private:
		RenderPass&             m_RenderPass;
		std::vector<ImageView*> m_UsedAttachments;
	};
} // namespace Graphics
