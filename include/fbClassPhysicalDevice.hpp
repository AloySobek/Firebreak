/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassPhysicalDevice.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:34:16 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/01 20:22:26 by Rustam           ###   ########.fr       */
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

		friend class Instance;

		void init(std::vector<const char *> layers,
				std::vector<const char *> extensions);

	private:
		std::vector<VkExtensionProperties>	pAvailableExtensions;
		std::vector<VkLayerProperties>		pAvailableLayers;
		std::vector<const char *>			ppSelectedLayers;
		std::vector<const char *>			ppSelectedExtensions;

		void getInfo(void);
		void setupLayers();
		void setupExtensions();
		void queryQueue();
};

#endif