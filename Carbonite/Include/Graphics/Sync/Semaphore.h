#pragma once

#include "Graphics/Device.h"

namespace Graphics::Sync
{
	struct Semaphore : Handle<vk::Semaphore>
	{
	public:
		static void WaitForSemaphores(const std::vector<Semaphore*>& semaphores, std::uint64_t timeout);

	public:
		Semaphore(Device& device);
		~Semaphore();

		void          waitFor(std::uint64_t timeout);
		std::uint64_t getValue();

		auto getDevice() const
		{
			return m_Device;
		}

	private:
		virtual void createImpl() override;
		virtual bool destroyImpl() override;

	private:
		Device* m_Device;
	};
} // namespace Graphics::Sync