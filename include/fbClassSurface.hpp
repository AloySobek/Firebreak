/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassSurface.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:53:26 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/06 17:09:14 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_SURFACE_HPP
# define FB_CLASS_SURFACE_HPP

# include "firebreak.hpp"

class Surface
{
	public:
		VkSurfaceKHR	self		= VK_NULL_HANDLE;
		VkSwapchainKHR	swapchain	= VK_NULL_HANDLE;

		void	*pWindow = nullptr;

		uint32_t khrFormatsCount		= 0;
		uint32_t khrPresentModesCount	= 0;
		uint32_t imagesCount			= 0;

		VkSurfaceCapabilitiesKHR	sCapabilities	= {};
		VkSurfaceFormatKHR			sFormat			= {};
		VkPresentModeKHR			sPresentMode	= {};
		VkExtent2D					extent			= {WIDTH, HEIGHT};

		VkSurfaceFormatKHR	*pFormats;
		VkPresentModeKHR	*pPresentModes;

		VkImage		*pImages;
		VkImageView	*pImageViewList;

		Surface() { }
		Surface(void *pWindow);

		void setWindow(void *pWindow);
		void setFlags(VkSwapchainCreateFlagsKHR flags);
		void setNext(const void *pNext);
		void setClipped(VkBool32 clipped);
		void setImageCount(uint32_t imagesCount);
		void setImageArrayLayers(uint32_t imageLayers);
		void setImageUsage(int32_t imageUsage);
		void setOldSwapChain(VkSwapchainKHR oldSwapChain);
		void setCompositeAlpha(VkCompositeAlphaFlagBitsKHR composite);
		bool setupFormat(VkFormat format, VkColorSpaceKHR colorSpace);
		bool setupPresentMode(VkPresentModeKHR presentMode);
		bool setupExtent();

		VkSurfaceKHR				getSelf();
		VkSwapchainKHR				getSwapchainSelf();
		VkSwapchainCreateFlagsKHR	getFlags();
		const void					*getNext();
		VkSurfaceCapabilitiesKHR	*getCapabilities	(Device &device);
		VkSurfaceCapabilitiesKHR	*getCapabilities	();
		VkPresentModeKHR			*getPresentModes	(Device &device);
		VkPresentModeKHR			*getPresentMode		();
		VkSurfaceFormatKHR			*getFormats			(Device &device);
		VkSurfaceFormatKHR			*getFormat			();
		VkImage						*getImages			(Device &device);

		void	checkSwapChainSupporting(Device &device);
		void	setupImageView(Device &device);
		void	create(Instance &instance);
		void	create(Instance &instance, void *pWindow);
		void	createSwapchain(Device &device);

		void	operator()(Instance &instance);
		void	operator()(Instance &instance, void *pWindow);
		void	operator()(Device &device);

		~Surface() { }

	private:
		VkSwapchainCreateInfoKHR sSwapchainCreateInfo = {};

		bool calledFormats	= false;
		bool calledPresent	= false;
		bool calledCapabil	= false;
		bool calledImages	= false;

		int32_t codeOfError	= false;
};

#endif