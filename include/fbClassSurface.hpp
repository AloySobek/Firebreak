/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassSurface.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:53:26 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/30 17:05:12 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_SURFACE_HPP
# define FB_CLASS_SURFACE_HPP

# include "firebreak.hpp"

class Surface
{
	public:
		Surface();
		Surface(Surface &anotherSurface);

		VkSurfaceKHR				&getSelf();
		VkAllocationCallbacks		&getAllocation();
		VkSurfaceFormatKHR			&getFormat();
		VkPresentModeKHR			&getPresentMode();

		VkImageViewCreateInfo		*getImageViewCreateInfo();
		VkPresentModeKHR			*getPresentModes(Device2 &device, uint32_t *size = nullptr);
		VkSurfaceCapabilitiesKHR	*getCapabilities(Device2 &device);
		VkExtent2D					*getExtent();
		VkImage						*getSwapchainImages(Device2 &device, uint32_t *size = nullptr);
		VkImageView					*getImageViews();
		uint32_t					*getImagesCount();

		void	provideSurface(VkSurfaceKHR &surface);
		void	setupImageView(Device2 &device);
		void	createSwapchain(Device2 &device);
		void	createImageView(Device2 &device);

		~Surface() { }

	private:
		VkSurfaceKHR				self					= VK_NULL_HANDLE;
		VkImageViewCreateInfo		sImageViewCreateInfo	= {};
		VkAllocationCallbacks		sAllocation				= {};
		VkSurfaceFormatKHR			sFormat					= {};
		VkPresentModeKHR			sPresentMode			= {};
		VkSurfaceCapabilitiesKHR	sCapabilities			= {};
		VkExtent2D					sExtent					= {WIDTH, HEIGHT};


		VkSurfaceFormatKHR	*pFormats		= nullptr;
		VkPresentModeKHR	*pPresentModes	= nullptr;

		VkImage		*pImages			= nullptr;
		VkImageView	*pImageViews		= nullptr;

		uint32_t khrFormatsCount		= 0;
		uint32_t khrPresentModesCount	= 0;
		uint32_t imagesCount			= 0;
		uint32_t imageViewsCount		= 0;

		bool capabilities	= false;
		int32_t codeOfError	= false;
};

class Surface2 : public Surface
{
	public:
		int test;
};

#endif