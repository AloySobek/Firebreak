/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vkClassVulkan.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:59:07 by vrichese          #+#    #+#             */
/*   Updated: 2019/12/06 18:13:34 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VK_CLASS_VULKAN_HPP
# define VK_CLASS_VULKAN_HPP

# include "firebreak.hpp"

class Vulkan
{
	public:
		Device		device;
		Surface		surface;
		RenderPass	render;

		VkRenderPass		renderPass = VK_NULL_HANDLE;
		VkPipelineLayout	layoutObj = VK_NULL_HANDLE;
		VkPipeline			pipelineObj = VK_NULL_HANDLE;
		std::vector<VkFramebuffer> swapChainFrameBuffers;
		VkCommandPool		commandPool;
		std::vector<VkCommandBuffer> commandBuffer;
		VkSemaphore		imageAvailableSemaphore;
		VkSemaphore		renderFinishedSemaphore;
		int				error;

		std::vector<char>	vkReadFile(const char *filename);
		VkShaderModule		vkCreateNewShaderModule(const std::vector<char> &code);
		void run(GLFWwindow *pWindow);
		void vkCreateNewRenderPass();
		void vkCreateNewGraphicsPipeline();
		void vkCreateNewFrameBuffer();
		void vkCreateNewCommandPool();
		void vkCreateNewCommandBuffers();
		void vkCreateNewSemaphore();
		void vkDrawFrame();
};

#endif