#include "DescriptorSet.h"
#include "DescriptorPool.h"

namespace Graphics
{
	DescriptorSet::DescriptorSet(DescriptorPool& descriptorPool, vk::DescriptorSet handle)
	    : Handle(handle), m_DescriptorPool(descriptorPool)
	{
		m_DescriptorPool.addChild(this);
	}

	DescriptorSet::~DescriptorSet()
	{
		if (isValid())
			destroy();
		m_DescriptorPool.removeChild(this);
	}
} // namespace Graphics