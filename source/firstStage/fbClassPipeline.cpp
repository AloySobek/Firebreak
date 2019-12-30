/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassPipeline.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 18:42:38 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/16 19:26:37 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firebreak.hpp"

Pipeline::Pipeline()
{
	sShaderCreateInfo.sType				= VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	sShaderStageCreateInfo.sType		= VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	sAssemblyStateCreateInfo.sType		= VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	sVertexInputStateCreateInfo.sType	= VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	sViewportStateCreateInfo.sType		= VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	sRasterizationStateCreateInfo.sType	= VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	sMultisampeStateCreateInfo.sType	= VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	sDepthStencilStateCreateInfo.sType	= VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	sColorBlendStateCreateInfo.sType	= VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	sDynamicStateCreateInfo.sType		= VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	sLayoutCreateInfo.sType				= VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	memset(pShaders, 0, sizeof(VkShaderModule) * FB_SHADERS_AMOUNT);
}

VkPipeline	Pipeline::getSelf()
{
	assert(self);
	return (self);
}

VkPipelineLayout		Pipeline::getLayout()
{
	assert(layoutSelf);
	return (layoutSelf);
}

VkAllocationCallbacks		*Pipeline::getAllocationInfo()
{
	return (&sAllocation);
}

VkShaderModuleCreateInfo	*Pipeline::getShaderCreateInfo()
{
	return (&sShaderCreateInfo);
}

VkPipelineShaderStageCreateInfo	*Pipeline::getShaderStageCreateInfo()
{
	return (&sShaderStageCreateInfo);
}

VkPipelineInputAssemblyStateCreateInfo	*Pipeline::getAssemblyStateCreateInfo()
{
	return (&sAssemblyStateCreateInfo);
}

VkPipelineVertexInputStateCreateInfo	*Pipeline::getVertexInputStateCreateInfo()
{
	return (&sVertexInputStateCreateInfo);
}

VkViewport	*Pipeline::getViewPortSettings()
{
	return (&sViewport);
}

VkRect2D	*Pipeline::getScissorSettings()
{
	return (&sScissor);
}

VkPipelineViewportStateCreateInfo	*Pipeline::getViewportStateCreateInfo()
{
	return (&sViewportStateCreateInfo);
}

VkPipelineRasterizationStateCreateInfo	*Pipeline::getRasteriazationStateCreateInfo()
{
	return (&sRasterizationStateCreateInfo);
}

VkPipelineMultisampleStateCreateInfo	*Pipeline::getMultisampleStateCreateInfo()
{
	return (&sMultisampeStateCreateInfo);
}

VkPipelineDepthStencilStateCreateInfo	*Pipeline::getDepthStencilStateCreateInfo()
{
	return (&sDepthStencilStateCreateInfo);
}

VkPipelineColorBlendAttachmentState		*Pipeline::getColorBlendAttachmentSettings()
{
	return (&sColorBlendAttachment);
}

VkPipelineColorBlendStateCreateInfo		*Pipeline::getColorBlendStateCreateInfo()
{
	return (&sColorBlendStateCreateInfo);
}

VkPipelineDynamicStateCreateInfo	*Pipeline::getDynamicStateCreateInfo()
{
	return (&sDynamicStateCreateInfo);
}

VkPipelineLayoutCreateInfo				*Pipeline::getLayoutCreateInfo()
{
	return (&sLayoutCreateInfo);
}

VkGraphicsPipelineCreateInfo	*Pipeline::getCreateInfo()
{
	return (&sCreateInfo);
}

void	Pipeline::createShaderModule(Device &device, uint32_t type, int mode)
{
	if ((codeOfError = vkCreateShaderModule(device.getSelf(), &sShaderCreateInfo, mode ? &sAllocation : nullptr, &pShaders[type])) != VK_SUCCESS)
	{
		std::cout << "Code of error" << codeOfError << std::endl;
		throw std::runtime_error("Failed to create shader module");
	}
	sShaderStageCreateInfo.module = pShaders[type];
	pShaderStageCreateInfos[shadersCount++] = sShaderStageCreateInfo;
}

void	Pipeline::createLayout(Device &device, int mode)
{
	if ((codeOfError = vkCreatePipelineLayout(device.getSelf(), &sLayoutCreateInfo, mode ? &sAllocation : nullptr, &layoutSelf)) != VK_SUCCESS)
	{
		std::cout << "Code of error" << codeOfError << std::endl;
		throw std::runtime_error("Failed to create Pipeline layout");
	}
}

void	Pipeline::create(Device &device, int mode)
{
	sCreateInfo.stageCount = shadersCount;
	sCreateInfo.pStages = pShaderStageCreateInfos;
	if ((codeOfError = vkCreateGraphicsPipelines(device.getSelf(), VK_NULL_HANDLE, 1, &sCreateInfo, nullptr, &self)) != VK_SUCCESS)
	{
		std::cout << "Code of error: " << codeOfError << std::endl;
		throw std::runtime_error("Failed to create pipeline");
	}
}