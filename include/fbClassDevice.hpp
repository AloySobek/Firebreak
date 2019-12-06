/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassDevice.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:34:16 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/06 19:25:14 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_PHYSICAL_DEVICE_HPP
# define FB_CLASS_PHYSICAL_DEVICE_HPP

# include "firebreak.hpp"

#define VK_QUEUE_PRESENT_BIT 10

typedef struct		FbQueue_s
{
	VkQueue			self;
	int32_t			index;
}					FbQueue_t;

class Device
{
	public:
		FbQueue_t	pQueues[VK_QUEUE_PROTECTED_BIT];

		Device(const void *pNext);
		Device(VkDeviceCreateFlags flags = VK_NULL_HANDLE, const void *pNext = nullptr);
		Device(Device &anotherDevice) { }

		void setupNext(const void *pNext);
		void setupFlags(VkDeviceCreateFlags flags);
		void setupLayers(std::vector<const char *> &desiredLayers);
		void setupExtensions(std::vector<const char *> &desiredExtensions);

		VkDevice					getSelf();
		VkPhysicalDevice			getPhysicalSelf();
		VkDeviceCreateFlags			getFlags();
		const void					*getNext();
		VkPhysicalDevice			*getPhysicalDevices(Instance &instance);
		VkPhysicalDeviceFeatures	*getFeatures();
		VkPhysicalDeviceProperties	*getProperties();
		VkPhysicalDeviceMemoryProperties	*getMemoryProperties();
		VkLayerProperties			*getLayers();
		VkExtensionProperties		*getExtensions();
		VkQueueFamilyProperties		*getQueuesFamiliesProperties();
		FbQueue_t					*getQueuesFamilies();
		uint32_t					getLayersAmount();
		uint32_t					getExtensionsAmount();
		uint32_t					getPhysicalDevicesAmount();
		uint32_t					getQueuesFamiliesCount();

		void attachPhysicalDevice(int deviceType);
		void attachPhysicalDevice(Instance &instance, int deviceType);
		bool checkCompatibleWithSurface(Surface &surface);
		void setupQueue(int type, float priority, int count);
		void create();

		uint32_t	*requireIndexArray();

		VkDevice			operator()();
		VkPhysicalDevice	operator!();

	private:
		VkDevice			self			= VK_NULL_HANDLE;
		VkPhysicalDevice	physicalSelf	= VK_NULL_HANDLE;
		VkDeviceCreateInfo	sCreateInfo		= {};

		VkPhysicalDeviceFeatures			sFeatures			= {};
		VkPhysicalDeviceProperties			sProperties			= {};
		VkPhysicalDeviceMemoryProperties	sMemoryProperties	= {};

		uint32_t			availablePhysicalDeviceCount = 0;
		VkPhysicalDevice	*pAvailablePhysicalDevices;

		uint32_t			enabledLayerCount	 = 0;
		uint32_t			availableLayersCount = 0;
		VkLayerProperties	*pAvailableLayers;
		const char			**ppEnabledLayerNames;

		uint32_t				enabledExtensionCount	 = 0;
		uint32_t				availableExtensionsCount = 0;
		VkExtensionProperties	*pAvailableExtensions;
		const char				**ppEnabledExtensionNames;

		uint32_t				availableQueuesFamiliesCount = 0;
		VkQueueFamilyProperties	*pAvailableQueuesFamilies;

		uint32_t				queueFamiliesCreateInfoCount = 0;
		VkDeviceQueueCreateInfo	pQueueFamiliesCreateInfo[VK_QUEUE_PROTECTED_BIT];

		bool retrieveDevices	= false;
		bool calledLayers		= false;
		bool calledExtensions	= false;
		bool calledQeueue		= false;
		bool getQueue			= false;
		bool calledMemory		= false;
		int32_t codeOfError		= false;

		bool isLayerSuitable(VkLayerProperties sLayer, std::vector<const char *> &layers);
		bool isExtensionSuitable(VkExtensionProperties sExtensions, std::vector<const char *> &extensions);
		bool isPhysicalDeviceSuitable(VkPhysicalDevice device, uint32_t type);
		bool isQueueFamilySuitable(VkQueueFamilyProperties queueProperties, uint32_t type, uint32_t count);
};

#endif