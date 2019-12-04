/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassSurface.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:53:26 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/04 20:53:29 by Rustam           ###   ########.fr       */
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
		VkImage						*pImages;

		VkSurfaceFormatKHR			*pFormats;
		VkPresentModeKHR			*pPresentModes;

		Surface() { }
		Surface(void *pWindow);

		void setWindow(void *pWindow);

		VkSurfaceCapabilitiesKHR	*getCapabilities	(Device device);
		VkSurfaceFormatKHR			*getFormats			(Device device);
		VkPresentModeKHR			*getPresentModes	(Device device);

		void			operator()();
		VkSurfaceKHR	operator()(Instance &instance);
		VkSurfaceKHR	operator()(Device &device);

		void	checkSwapChainSupporting(Device device);
		void	setupSwapChain();

		~Surface() { }

	private:
		VkSwapchainCreateInfoKHR sSwapchainCreateInfo = {};

		bool calledFormats	= false;
		bool calledPresent	= false;
		bool calledCapabil	= false;

		int32_t codeOfError	= false;
};

#endif