/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassComputePipeline.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 18:51:24 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/26 18:49:35 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firebreak.hpp"

VkPipeline	&ComputePipeline::getSelf(uint32_t index)
{
	if (!pSelfs)
		return (self);
	assert(index < amount);
	return (pSelfs[index]);
}

VkComputePipelineCreateInfo	&ComputePipeline::getCreateInfo(uint32_t index)
{
	if (!pCreateInfos)
		return (sCreateInfo);
	assert(index < amount);
	return (pCreateInfos[index]);
}

void	ComputePipeline::setAmount(uint32_t amount)
{
	if (amount < 1)
		return ;
	this->amount = amount;
	pSelfs ? delete[] pSelfs : (void)0;
	pSelfs = new VkPipeline[amount];
	pCreateInfos ? delete[] pCreateInfos : (void)0;
	pCreateInfos = new VkComputePipelineCreateInfo[amount];
}

void	ComputePipeline::create(Device &device)
{
	codeOfError = vkCreateComputePipelines(device.getSelf(), cache, amount, pCreateInfos ? pCreateInfos : &sCreateInfo, sAllocation.pfnAllocation ? &sAllocation : nullptr, pSelfs ? pSelfs : &self);
	THROW_EXCEPTION("Failed to create computer pipeline");
}

void	ComputePipeline::destroy(Device &device, uint32_t index)
{
	if (pSelfs)
	{
		assert(index < amount);
		vkDestroyPipeline(device.getSelf(), pSelfs[index], sAllocation.pfnAllocation ? &sAllocation : nullptr);
		pSelfs[index] = nullptr;
	}
	else
		vkDestroyPipeline(device.getSelf(), self, sAllocation.pfnAllocation ? &sAllocation : nullptr);
}