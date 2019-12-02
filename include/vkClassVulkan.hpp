/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vkClassVulkan.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:59:07 by vrichese          #+#    #+#             */
/*   Updated: 2019/12/02 17:44:08 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VK_CLASS_VULKAN_HPP
# define VK_CLASS_VULKAN_HPP

typedef struct	surfaceInfo_s
{
	;
}				surfaceInfo_t;

class Vulkan
{
	public:
		Instance	instance;
		/*
		** Create Image view and setup it
		*/
		VkImageView	*pImageViewList	= nullptr;

		VkRenderPass		renderPass = VK_NULL_HANDLE;

		VkPipelineLayout	layoutObj = VK_NULL_HANDLE;

		VkPipeline			pipelineObj = VK_NULL_HANDLE;

		std::vector<VkFramebuffer> swapChainFrameBuffers;

		VkCommandPool		commandPool;

		std::vector<VkCommandBuffer> commandBuffer;

		VkSemaphore		imageAvailableSemaphore;
		VkSemaphore		renderFinishedSemaphore;

		int				error;

		Vulkan(): error(false) {}
		void run(GLFWwindow *pWindow);

		void vkSetupDeviceQueueCreateInfo	(float queuePriority);
		void vkSetupDeviceCreateInfo		();
		void vkCreateNewDevice				();

		void vkSetupSwapChain			();
		void vkSetupSwapChainCreateInfo	();
		void vkCreateSwapChain			();

		VkImageViewCreateInfo 	vkSetupImageViewCreateInfo	(VkImage image);
		void 					vkCreateNewImageView			();

		void	vkCreateNewRenderPass();

		void 				vkCreateNewGraphicsPipeline();
		std::vector<char> 	vkReadFile				(const char *filename);
		VkShaderModule		vkCreateNewShaderModule	(const std::vector<char> &code);

		void 				vkCreateNewFrameBuffer();

		void				vkCreateNewCommandPool();

		void				vkCreateNewCommandBuffers();

		void 				vkCreateNewSemaphore();

		void				vkDrawFrame();

		void				fbCleanUp();
};

#endif