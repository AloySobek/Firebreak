/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vkVulkanMethods.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:55:17 by vrichese          #+#    #+#             */
/*   Updated: 2019/12/06 19:10:13 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firebreak.hpp"

namespace InstanceLayersExtensions
{
	std::vector<const char *> ppDesiredLayers =
	{
		//"VK_LAYER_LUNARG_api_dump",
		//"VK_LAYER_LUNARG_core_validation",
		//"VK_LAYER_KHRONOS_validation",
		//"VK_LAYER_LUNARG_object_tracker",
		//"VK_LAYER_LUNARG_standard_validation",
		//"VK_LAYER_LUNARG_parameter_validation",
		//"VK_LAYER_GOOGLE_threading",
		//"VK_LAYER_GOOGLE_unique_objects"
	};
	std::vector<const char *> ppDesiredExtensions =
	{
		"VK_KHR_surface",
		"VK_KHR_swapchain",
		"VK_MVK_macos_surface",
	};
};

namespace PhysicalDeviceLayersExtensions
{
	std::vector<const char *> ppDesiredLayers =
	{
		//"VK_LAYER_LUNARG_api_dump",
		//"VK_LAYER_LUNARG_core_validation",
		//"VK_LAYER_KHRONOS_validation",
		//"VK_LAYER_LUNARG_object_tracker",
		//"VK_LAYER_LUNARG_standard_validation",
		//"VK_LAYER_LUNARG_parameter_validation",
		//"VK_LAYER_GOOGLE_threading",
		//"VK_LAYER_GOOGLE_unique_objects"
	};
	std::vector<const char *> ppDesiredExtensions =
	{
		//"VK_KHR_surface",
		"VK_KHR_swapchain",
		//"VK_MVK_macos_surface",
	};
}

void Vulkan::run(GLFWwindow *pWindow)
{
	Instance	instance;

	instance.setupAppInfo("Triangle", "NoEngine");
	instance.setupLayers(InstanceLayersExtensions::ppDesiredLayers);
	instance.setupExtensions(InstanceLayersExtensions::ppDesiredExtensions);
	instance.create();

	surface.create(instance, pWindow);

	device.getPhysicalDevices(instance);
	device.attachPhysicalDevice(VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU);
	device.setupLayers(PhysicalDeviceLayersExtensions::ppDesiredLayers);
	device.setupExtensions(PhysicalDeviceLayersExtensions::ppDesiredExtensions);

	surface.getFormats(device);
	surface.getPresentModes(device);
	surface.getCapabilities(device);
	surface.checkSwapChainSupporting(device);

	device.getQueuesFamiliesProperties();
	if (!device.checkCompatibleWithSurface(surface))
		throw std::runtime_error("Surface and device not compatible");
	device.setupQueue(VK_QUEUE_PRESENT_BIT, 1.0f, 1);
	device.setupQueue(VK_QUEUE_GRAPHICS_BIT, 1.0f, 1);
	device.create();
	device.getQueuesFamilies();

	if (!surface.setupFormat(VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR))
		std::cout << "Necessary format or color space not found, standart setting enabled\n";
	if (!surface.setupPresentMode(VK_PRESENT_MODE_MAILBOX_KHR))
		if (!surface.setupPresentMode(VK_PRESENT_MODE_FIFO_KHR))
			std::cout << "NEcessary present mode not found, standart present mode enabled\n";
	surface.setupExtent();
	surface.setClipped(VK_TRUE);
	surface.setImageCount(surface.getCapabilities()->minImageCount + 1);
	surface.setImageArrayLayers(1);
	surface.setOldSwapChain(VK_NULL_HANDLE);
	surface.setCompositeAlpha(VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR);
	surface.setImageUsage(VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT);
	surface.createSwapchain(device);
	surface.getImages(device);
	surface.setupImageView(device);

	render.getColorAttachmentSettings()->format			= surface.getFormat()->format;
	render.getColorAttachmentSettings()->samples		= VK_SAMPLE_COUNT_1_BIT;
	render.getColorAttachmentSettings()->loadOp			= VK_ATTACHMENT_LOAD_OP_CLEAR;
	render.getColorAttachmentSettings()->storeOp		= VK_ATTACHMENT_STORE_OP_STORE;
	render.getColorAttachmentSettings()->stencilLoadOp	= VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	render.getColorAttachmentSettings()->stencilStoreOp	= VK_ATTACHMENT_STORE_OP_DONT_CARE;
	render.getColorAttachmentSettings()->initialLayout	= VK_IMAGE_LAYOUT_UNDEFINED;
	render.getColorAttachmentSettings()->finalLayout	= VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	vkCreateNewRenderPass();
	vkCreateNewGraphicsPipeline();
	vkCreateNewFrameBuffer();
	vkCreateNewCommandPool();
	vkCreateNewCommandBuffers();
	vkCreateNewSemaphore();
}

/*
** -----------------------------------------------------------------------------------------------------
*/

void Vulkan::vkCreateNewRenderPass()
{
	VkRenderPassCreateInfo	render				= {};
	VkAttachmentDescription	colorAttachment		= {};
	VkAttachmentReference	colorAttachmentRef	= {};
	VkSubpassDescription	subpass				= {};

	colorAttachment.format			= surface.sFormat.format;
	colorAttachment.samples			= VK_SAMPLE_COUNT_1_BIT;
	colorAttachment.loadOp			= VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp			= VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.stencilLoadOp	= VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp	= VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.initialLayout	= VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachment.finalLayout		= VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	colorAttachmentRef.attachment	= 0;
	colorAttachmentRef.layout		= VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	subpass.pipelineBindPoint		= VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount	= 1;
	subpass.pColorAttachments		= &colorAttachmentRef;

	render.sType					= VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	render.flags					= 0;
	render.pNext					= nullptr;
	render.attachmentCount			= 1;
	render.pAttachments				= &colorAttachment;
	render.subpassCount				= 1;
	render.pSubpasses				= &subpass;

	VkSubpassDependency dependency = {};

	dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	dependency.dstSubpass = 0;
	dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.srcAccessMask = 0;
	dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

	render.dependencyCount			= 1;
	render.pDependencies			= &dependency;

	if ((error = vkCreateRenderPass(device(), &render, nullptr, &renderPass)) != VK_SUCCESS)
	{
		std::cout << "Code of error " << error << std::endl;
		throw std::runtime_error("Failed to create render pass");
	}
}

VkShaderModule		Vulkan::vkCreateNewShaderModule(const std::vector<char> &code)
{
	VkShaderModule				shaderModuleObj = {};
	VkShaderModuleCreateInfo	sShaderModuleCreateInfo = {};

	sShaderModuleCreateInfo.sType		= VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	sShaderModuleCreateInfo.flags		= 0;
	sShaderModuleCreateInfo.codeSize	= code.size();
	sShaderModuleCreateInfo.pCode		= reinterpret_cast<const uint32_t *>(code.data());
	sShaderModuleCreateInfo.pNext		= nullptr;

	if ((error = vkCreateShaderModule(device(), &sShaderModuleCreateInfo, nullptr, &shaderModuleObj)) != VK_SUCCESS)
	{
		std::cout << "Code of error" << error << std::endl;
		throw std::runtime_error("Failed to create shader module");
	}
	return (shaderModuleObj);
}

std::vector<char>	Vulkan::vkReadFile(const char *filename)
{
	size_t	fileSize;

	std::ifstream file(filename, std::ios::ate | std::ios::binary);
	if (!file.is_open())
		throw std::runtime_error("Failed to open file!");
	fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);
	file.seekg(0);
	file.read(buffer.data(), fileSize);
	file.close();
	return (buffer);
}

void Vulkan::vkCreateNewGraphicsPipeline()
{
	VkPipelineShaderStageCreateInfo sVertexShaderStageCreateInfo = {};
	VkPipelineShaderStageCreateInfo sFragmentShaderStageCreateInfo = {};

	VkPipelineVertexInputStateCreateInfo sVertexCreateInfo = {};

	VkPipelineInputAssemblyStateCreateInfo sInputAssembly = {};

	VkViewport		viewport = {};

	VkRect2D		scissor = {};

	VkPipelineViewportStateCreateInfo  viewportState = {};

	VkPipelineRasterizationStateCreateInfo rasterizer = {};

	VkPipelineMultisampleStateCreateInfo multisampling = {};

	VkPipelineDepthStencilStateCreateInfo depthStencil = {};

	VkPipelineColorBlendAttachmentState colorBlendAttachment = {};

	VkPipelineColorBlendStateCreateInfo colorBlending = {};

	VkDynamicState dynamicStates[] = {VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_LINE_WIDTH};

	VkPipelineDynamicStateCreateInfo dynamicState = {};

	VkPipelineLayoutCreateInfo	layoutCreateInfo = {};

	VkShaderModule		vertexModule;
	VkShaderModule		fragmentModule;

	std::vector<char>	vertexCode;
	std::vector<char>	fragmentCode;

	VkGraphicsPipelineCreateInfo	pipeline = {};

	vertexCode = this->vkReadFile("../shader_source/vert.spv");
	fragmentCode = this->vkReadFile("../shader_source/frag.spv");
	vertexModule = this->vkCreateNewShaderModule(vertexCode);
	fragmentModule = this->vkCreateNewShaderModule(fragmentCode);

	sVertexShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	sVertexShaderStageCreateInfo.flags = 0;
	sVertexShaderStageCreateInfo.pNext = nullptr;
	sVertexShaderStageCreateInfo.module = vertexModule;
	sVertexShaderStageCreateInfo.pName = "main";
	sVertexShaderStageCreateInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
	sVertexShaderStageCreateInfo.pSpecializationInfo = nullptr;

	sFragmentShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	sFragmentShaderStageCreateInfo.flags = 0;
	sFragmentShaderStageCreateInfo.pNext = nullptr;
	sFragmentShaderStageCreateInfo.module = fragmentModule;
	sFragmentShaderStageCreateInfo.pName = "main";
	sFragmentShaderStageCreateInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	sFragmentShaderStageCreateInfo.pSpecializationInfo = nullptr;

	sVertexCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	sVertexCreateInfo.flags = 0;
	sVertexCreateInfo.pNext = nullptr;
	sVertexCreateInfo.vertexAttributeDescriptionCount = 0;
	sVertexCreateInfo.vertexBindingDescriptionCount = 0;
	sVertexCreateInfo.pVertexAttributeDescriptions = nullptr;
	sVertexCreateInfo.pVertexBindingDescriptions = nullptr;

	sInputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	sInputAssembly.pNext = nullptr;
	sInputAssembly.flags = 0;
	sInputAssembly.primitiveRestartEnable = VK_FALSE;
	sInputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = (float)surface.extent.width;
	viewport.height = (float)surface.extent.height;
	viewport.maxDepth = 1.0f;
	viewport.minDepth = 0.0f;

	scissor.offset = {0, 0};
	scissor.extent = surface.extent;

	viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportState.flags = 0;
	viewportState.pNext = nullptr;
	viewportState.pScissors = &scissor;
	viewportState.pViewports = &viewport;
	viewportState.viewportCount = 1;
	viewportState.scissorCount = 1;

	rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizer.flags = 0;
	rasterizer.pNext = nullptr;
	rasterizer.depthClampEnable = VK_FALSE;
	rasterizer.rasterizerDiscardEnable = VK_FALSE;
	rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
	rasterizer.lineWidth = 0.5f;
	rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
	rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
	rasterizer.depthBiasEnable = VK_FALSE;
	rasterizer.depthBiasClamp = 0.0f;
	rasterizer.depthBiasSlopeFactor = 0.0f;
	rasterizer.depthBiasConstantFactor = 0.0f;

	multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampling.flags = 0;
	multisampling.pNext = nullptr;
	multisampling.sampleShadingEnable = VK_FALSE;
	multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
	multisampling.minSampleShading = 1.0f;
	multisampling.pSampleMask = nullptr;
	multisampling.alphaToCoverageEnable = VK_FALSE;
	multisampling.alphaToOneEnable = VK_FALSE;

	colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	colorBlendAttachment.blendEnable = VK_FALSE;
	colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
	colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
	colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
	colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
	colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
	colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

	colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlending.flags = 0;
	colorBlending.pNext = nullptr;
	colorBlending.logicOpEnable = VK_FALSE;
	colorBlending.logicOp = VK_LOGIC_OP_COPY;
	colorBlending.pAttachments = &colorBlendAttachment;
	colorBlending.attachmentCount = 1;
	colorBlending.blendConstants[0] = 0.0f;
	colorBlending.blendConstants[1] = 0.0f;
	colorBlending.blendConstants[2] = 0.0f;
	colorBlending.blendConstants[3] = 0.0f;

	dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	dynamicState.flags = 0;
	dynamicState.pNext = nullptr;
	dynamicState.dynamicStateCount = 2;
	dynamicState.pDynamicStates = dynamicStates;

	layoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	layoutCreateInfo.flags = 0;
	layoutCreateInfo.pNext = nullptr;
	layoutCreateInfo.setLayoutCount = 0;
	layoutCreateInfo.pSetLayouts = nullptr;
	layoutCreateInfo.pushConstantRangeCount = 0;
	layoutCreateInfo.pPushConstantRanges = nullptr;

	if ((error = vkCreatePipelineLayout(device(), &layoutCreateInfo, nullptr, &layoutObj)) != VK_SUCCESS)
	{
		std::cout << "Code of error" << error << std::endl;
		throw std::runtime_error("Failed to create Pipeline layout");
	}

	VkPipelineShaderStageCreateInfo moduleCreateInfos[2] = {sVertexShaderStageCreateInfo, sFragmentShaderStageCreateInfo};

	pipeline.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipeline.flags = 0;
	pipeline.pNext = nullptr;
	pipeline.stageCount = 2;
	pipeline.pStages = moduleCreateInfos;
	pipeline.pVertexInputState = &sVertexCreateInfo;
	pipeline.pInputAssemblyState = &sInputAssembly;
	pipeline.pViewportState = &viewportState;
	pipeline.pRasterizationState = &rasterizer;
	pipeline.pMultisampleState = &multisampling;
	pipeline.pColorBlendState = &colorBlending;
	pipeline.pDepthStencilState = nullptr;
	pipeline.pDynamicState = &dynamicState;
	pipeline.renderPass = renderPass;
	pipeline.layout = layoutObj;
	pipeline.subpass = 0;
	pipeline.basePipelineHandle = VK_NULL_HANDLE;
	pipeline.basePipelineIndex = -1;
	pipeline.pTessellationState = nullptr;

	if ((error = vkCreateGraphicsPipelines(device(), VK_NULL_HANDLE, 1, &pipeline, nullptr, &pipelineObj)) != VK_SUCCESS)
	{
		std::cout << "Code of error: " << error << std::endl;
		throw std::runtime_error("Failed to create pipeline");
	}
}

void Vulkan::vkCreateNewFrameBuffer()
{
	swapChainFrameBuffers.resize(surface.imagesCount);

	for (int i = 0; i < surface.imagesCount; ++i)
	{
		VkImageView attachments[] = { surface.pImageViewList[i] };
		VkFramebufferCreateInfo	createInfo = {};

		createInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		createInfo.pNext = nullptr;
		createInfo.flags = 0;
		createInfo.renderPass = renderPass;
		createInfo.attachmentCount = 1;
		createInfo.pAttachments = attachments;
		createInfo.height = surface.extent.height;
		createInfo.width = surface.extent.width;
		createInfo.layers = 1;
		if ((error = vkCreateFramebuffer(device(), &createInfo, nullptr, &swapChainFrameBuffers[i])) != VK_SUCCESS)
		{
			std::cout << "Code of error: " << error << std::endl;
			throw std::runtime_error("Failed to create on of your buffers");
		}
	}
}

void Vulkan::vkCreateNewCommandPool()
{
	VkCommandPoolCreateInfo		createInfo = {};

	createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;
	createInfo.queueFamilyIndex = device.pQueues[VK_QUEUE_GRAPHICS_BIT].index;

	if ((error = vkCreateCommandPool(device(), &createInfo, nullptr, &commandPool)))
	{
		std::cout << "Code of error: " << error << std::endl;
		throw std::runtime_error("Failed to create command pool");
	}
}

void Vulkan::vkCreateNewCommandBuffers()
{
	VkCommandBufferAllocateInfo allocInfo = {};

	commandBuffer.resize(swapChainFrameBuffers.size());
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.pNext = nullptr;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandPool = commandPool;
	allocInfo.commandBufferCount = commandBuffer.size();

	if ((error = vkAllocateCommandBuffers(device(), &allocInfo, commandBuffer.data())) != VK_SUCCESS)
	{
		std::cout << "Code of error: " << error << std::endl;
		throw std::runtime_error("Failed to crate command buffers");
	}

	for (int i = 0; i < commandBuffer.size(); ++i)
	{
		VkCommandBufferBeginInfo beginInfo = {};

		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.pNext = nullptr;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
		beginInfo.pInheritanceInfo = nullptr;

		if ((error = vkBeginCommandBuffer(commandBuffer[i], &beginInfo)) != VK_SUCCESS)
		{
			std::cout << "Code of error: " << error << std::endl;
			throw std::runtime_error("Failed to create commandBuffer");
		}
		VkRenderPassBeginInfo renderPassInfo = {};

		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.pNext = nullptr;
		renderPassInfo.renderPass = renderPass;
		renderPassInfo.framebuffer = swapChainFrameBuffers[i];
		renderPassInfo.renderArea.offset = {0, 0};
		renderPassInfo.renderArea.extent = surface.extent;

		VkClearValue	clearColor = {0.0f, 0.0f, 0.0f, 1.0f};

		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;

		vkCmdBeginRenderPass(commandBuffer[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
		vkCmdBindPipeline(commandBuffer[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineObj);
		vkCmdDraw(commandBuffer[i], 3, 1, 0, 0);
		vkCmdEndRenderPass(commandBuffer[i]);

		if ((error = vkEndCommandBuffer(commandBuffer[i])) != VK_SUCCESS)
		{
			std::cout << "Code of error: " << error << std::endl;
			throw std::runtime_error("Failed to end command buffer");
		}
	}
}

void Vulkan::vkCreateNewSemaphore()
{
	VkSemaphoreCreateInfo createInfo = {};

	createInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	createInfo.pNext = nullptr;
	createInfo.flags = 0;

	if ((error = vkCreateSemaphore(device(), &createInfo, nullptr, &renderFinishedSemaphore)) != VK_SUCCESS)
	{
		std::cout << "Code fo error1: " << error << std::endl;
		throw std::runtime_error("Failed to create semaphore");
	}

	if ((error = vkCreateSemaphore(device(), &createInfo, nullptr, &imageAvailableSemaphore)) != VK_SUCCESS)
	{
		std::cout << "Code fo error2: " << error << std::endl;
		throw std::runtime_error("Failed to create semaphore");
	}
}

void Vulkan::vkDrawFrame()
{
	uint32_t imageIndex;

	vkAcquireNextImageKHR(device(), surface.swapchain, std::numeric_limits<uint64_t>::max(), imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);
	VkSubmitInfo submitInfo = {};

	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.pNext = nullptr;

	VkSemaphore waiteSemaphores[] = {imageAvailableSemaphore};
	VkPipelineStageFlags waiteStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};

	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waiteSemaphores;
	submitInfo.pWaitDstStageMask = waiteStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer[imageIndex];

	VkSemaphore signalSemaphore[] = {renderFinishedSemaphore};

	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphore;

	if ((error = vkQueueSubmit(device.pQueues[VK_QUEUE_GRAPHICS_BIT].self, 1, &submitInfo, VK_NULL_HANDLE)) != VK_SUCCESS)
	{
		std::cout << "Code of error: " << error << std::endl;
		throw std::runtime_error("Failed to submit");
	}

	VkPresentInfoKHR present = {};

	present.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	present.pNext = nullptr;
	present.waitSemaphoreCount = 1;
	present.pWaitSemaphores = waiteSemaphores;

	VkSwapchainKHR	swapChains[] = {surface.swapchain};

	present.swapchainCount = 1;
	present.pSwapchains = swapChains;
	present.pImageIndices = &imageIndex;
	present.pResults = nullptr;
	vkQueuePresentKHR(device.pQueues[VK_QUEUE_PRESENT_BIT].self, &present);
}