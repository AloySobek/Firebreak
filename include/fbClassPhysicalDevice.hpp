/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassPhysicalDevice.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:34:16 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/02 18:46:42 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_PHYSICAL_DEVICE_HPP
# define FB_CLASS_PHYSICAL_DEVICE_HPP

# include "vkClassContainer.hpp"

class PhysicalDevice
{
	public:
		VkPhysicalDevice	self = VK_NULL_HANDLE;

		VkPhysicalDeviceFeatures	sFeatures	= {};
		VkPhysicalDeviceProperties	sProperties	= {};

		u_int32_t	availableLayersCount		= 0;
		u_int32_t	selectedLayersCount			= 0;
		u_int32_t	selectedExtensionsCount		= 0;
		u_int32_t	availableExtensionsCount	= 0;
		u_int32_t	availableQueuesFamilies		= 0;
		int32_t		presentQueueFamilyIndex		= -1;
		int32_t		graphicQueueFamilyIndex		= -1;

		void	setupLayers		(std::vector<const char *> &desiredLayers);
		void	setupExtensions	(std::vector<const char *> &desiredExtensions);

		std::vector<VkLayerProperties>			getLayers();
		std::vector<VkExtensionProperties>		getExtensions();
		std::vector<VkQueueFamilyProperties>	getQueueFamilies();

		void	checkSurfaceSupportAndSetupPresentQueue(Surface surface);

		void	setupQueue(int type);

		friend class Instance;
		friend class Device;

	private:
		std::vector<VkQueueFamilyProperties> 	pAvailableQueuesFamilies;
		std::vector<VkExtensionProperties>		pAvailableExtensions;
		std::vector<VkLayerProperties>			pAvailableLayers;
		std::vector<const char *>				ppSelectedLayers;
		std::vector<const char *>				ppSelectedExtensions;

		bool	calledLayers			= false;
		bool	calledExtensions		= false;
		bool	calledQeueueFamilies 	= false;

		void getInfo(void);
		bool isLayerSuitable(VkLayerProperties sLayer, std::vector<const char *> &desiredLayers);
		bool isExtensionSuitable(VkExtensionProperties sExtensions, std::vector<const char *> &desiredExtensions);
		void queryQueue();
};

#endif