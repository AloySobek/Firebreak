/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassPipeline.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 18:43:13 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/14 16:56:19 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_PIPELINE_HPP
# define FB_CLASS_PIPELINE_HPP

# include "firebreak.hpp"

typedef enum	shaders_e
{
	FB_VERTEX_SHADER,
	FB_TESSELATION_SHADER,
	FB_GEOMETRY_SHADER,
	FB_FRAGMENT_SHADER,
	FB_SHADERS_AMOUNT
}				shaders_t;

class Pipeline
{
	public:
		VkPipeline			self;
		VkPipelineLayout	layoutSelf;

		Pipeline();
		Pipeline(Pipeline &anotherPipeline) { }

		VkPipeline								getSelf();
		VkPipelineLayout						getLayout();
		VkAllocationCallbacks					*getAllocationInfo();
		VkShaderModuleCreateInfo				*getShaderCreateInfo();
		VkPipelineShaderStageCreateInfo			*getShaderStageCreateInfo();
		VkPipelineInputAssemblyStateCreateInfo	*getAssemblyStateCreateInfo();
		VkPipelineVertexInputStateCreateInfo	*getVertexInputStateCreateInfo();
		VkViewport								*getViewPortSettings();
		VkRect2D								*getScissorSettings();
		VkPipelineViewportStateCreateInfo		*getViewportStateCreateInfo();
		VkPipelineRasterizationStateCreateInfo	*getRasteriazationStateCreateInfo();
		VkPipelineMultisampleStateCreateInfo	*getMultisampleStateCreateInfo();
		VkPipelineDepthStencilStateCreateInfo	*getDepthStencilStateCreateInfo();
		VkPipelineColorBlendAttachmentState		*getColorBlendAttachmentSettings();
		VkPipelineColorBlendStateCreateInfo		*getColorBlendStateCreateInfo();
		VkPipelineDynamicStateCreateInfo		*getDynamicStateCreateInfo();
		VkPipelineLayoutCreateInfo				*getLayoutCreateInfo();
		VkGraphicsPipelineCreateInfo			*getCreateInfo();

		void	createShaderModule(Device &device, uint32_t	type, int mode = VK_NULL_HANDLE);
		void	createLayout(Device &device, int mode = VK_NULL_HANDLE);
		void	create(Device &device, int mode = VK_NULL_HANDLE);

		~Pipeline() { }

	private:
		VkGraphicsPipelineCreateInfo	sCreateInfo				= {};
		VkAllocationCallbacks			sAllocation				= {};

		VkShaderModuleCreateInfo		sShaderCreateInfo		= {};
		VkPipelineShaderStageCreateInfo	sShaderStageCreateInfo	= {};
		VkShaderModule					pShaders[FB_SHADERS_AMOUNT];
		VkPipelineShaderStageCreateInfo			pShaderStageCreateInfos[FB_SHADERS_AMOUNT];
		VkPipelineInputAssemblyStateCreateInfo	sAssemblyStateCreateInfo	= {};
		VkPipelineVertexInputStateCreateInfo	sVertexInputStateCreateInfo	= {};
		VkPipelineViewportStateCreateInfo		sViewportStateCreateInfo		= {};
		VkPipelineRasterizationStateCreateInfo	sRasterizationStateCreateInfo	= {};
		VkPipelineMultisampleStateCreateInfo	sMultisampeStateCreateInfo		= {};
		VkPipelineDepthStencilStateCreateInfo	sDepthStencilStateCreateInfo	= {};
		VkPipelineColorBlendAttachmentState		sColorBlendAttachment			= {};
		VkPipelineColorBlendStateCreateInfo		sColorBlendStateCreateInfo		= {};
		VkPipelineDynamicStateCreateInfo		sDynamicStateCreateInfo			= {};
		VkPipelineLayoutCreateInfo				sLayoutCreateInfo				= {};
		VkViewport	sViewport	= {};
		VkRect2D	sScissor	= {};

		int32_t		codeOfError		= false;
		uint32_t	shadersCount	= 0;
};

#endif