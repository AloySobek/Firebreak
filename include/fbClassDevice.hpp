/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassDevice.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:34:16 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/04 20:53:13 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_PHYSICAL_DEVICE_HPP
# define FB_CLASS_PHYSICAL_DEVICE_HPP

# include "firebreak.hpp"

#define VK_QUEUE_PRESENT_BIT 10

class Device
{
	public:
		VkDevice			self		 = VK_NULL_HANDLE;
		VkPhysicalDevice	physicalSelf = VK_NULL_HANDLE;

		VkPhysicalDeviceFeatures	sFeatures	= {};
		VkPhysicalDeviceProperties	sProperties	= {};

		u_int32_t			availablePhysicalDeviceCount = 0;
		VkPhysicalDevice	*pAvailablePhysicalDevices;

		u_int32_t			enabledLayerCount	 = 0;
		u_int32_t			availableLayersCount = 0;
		VkLayerProperties	*pAvailableLayers;
		const char			**ppEnabledLayerNames;

		u_int32_t				enabledExtensionCount	 = 0;
		u_int32_t				availableExtensionsCount = 0;
		VkExtensionProperties	*pAvailableExtensions;
		const char				**ppEnabledExtensionNames;

		u_int32_t				availableQueuesFamiliesCount = 0;
		VkQueueFamilyProperties	*pAvailableQueuesFamilies;

		uint32_t				queueFamiliesCreateInfoCount = 0;
		VkDeviceQueueCreateInfo	pQueueFamiliesCreateInfo[VK_QUEUE_PROTECTED_BIT];
		int32_t					pIndexArray[VK_QUEUE_PROTECTED_BIT];
		VkQueue					pQueues[VK_QUEUE_PROTECTED_BIT];

		Device(const void *pNext);
		Device(VkDeviceCreateFlags flags = VK_NULL_HANDLE, const void *pNext = nullptr);

		void init();

		void setupNext(const void *pNext);
		void setupFlags(VkDeviceCreateFlags flags);
		void setupLayers(std::vector<const char *> &desiredLayers);
		void setupExtensions(std::vector<const char *> &desiredExtensions);

		VkDevice					getSelf();
		VkPhysicalDevice			getPhysicalSelf();
		VkDeviceCreateFlags			getFlags();
		const void					*getNext();
		VkPhysicalDevice			*getPhysicalDevices(Instance instance);
		VkPhysicalDeviceFeatures	*getFeatures();
		VkPhysicalDeviceProperties	*getProperties();
		VkLayerProperties			*getLayers();
		VkExtensionProperties		*getExtensions();
		VkQueueFamilyProperties		*getQueueFamilies();

		void attachPhysicalDevice(int deviceType);
		void attachPhysicalDevice(Instance instance, int deviceType);
		bool checkCompatibleWithSurface(Surface surface);
		void setupQueue(int type, float priority, int count);
		uint32_t	*requireIndexArray();

		VkDevice operator()();

	private:
		VkDeviceCreateInfo sCreateInfo = {};

		bool retrieveDevices	= false;
		bool calledLayers		= false;
		bool calledExtensions	= false;
		bool calledQeueue		= false;
		int32_t codeOfError		= false;

		bool isLayerSuitable(VkLayerProperties sLayer, std::vector<const char *> &layers);
		bool isExtensionSuitable(VkExtensionProperties sExtensions, std::vector<const char *> &extensions);
		bool isPhysicalDeviceSuitable(VkPhysicalDevice device, uint32_t type);
		bool isQueueFamilySuitable(VkQueueFamilyProperties queueProperties, uint32_t type, uint32_t count);
};

#endif