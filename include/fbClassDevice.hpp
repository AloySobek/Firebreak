/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassDevice.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:34:16 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/15 17:50:37 by Rustam           ###   ########.fr       */
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

		Device();
		Device(Device &anotherDevice) { }

		void setLayers(const char **desiredLayers, uint32_t size);
		void setExtensions(const char **desiredExtensions, uint32_t size);

		VkDevice							getSelf();
		VkPhysicalDevice					getPhysicalSelf();
		VkDeviceCreateInfo					*getCreateInfo();
		VkPhysicalDeviceFeatures			*getFeatures();
		VkPhysicalDeviceProperties			*getProperties();
		VkPhysicalDeviceMemoryProperties	*getMemoryProperties();
		VkLayerProperties					*getAvailableLayers();
		VkExtensionProperties				*getAvailableExtensions();
		VkQueueFamilyProperties				*getQueuesFamiliesProperties();
		FbQueue_t							*getQueuesFamilies();

		void attachPhysicalDevice(int type, VkPhysicalDevice *pPhysicalDevices, uint32_t size);
		bool setQueue(Surface &surface, VkQueueFamilyProperties properties, float priority);
		bool setQueue(VkQueueFamilyProperties properties, float priority);
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

		uint32_t			availableLayersCount = 0;
		VkLayerProperties	*pAvailableLayers;

		uint32_t				availableExtensionsCount = 0;
		VkExtensionProperties	*pAvailableExtensions;

		uint32_t				availableQueuesFamiliesCount = 0;
		VkQueueFamilyProperties	*pAvailableQueuesFamilies;

		uint32_t				queueFamiliesCreateInfoCount = 0;
		VkDeviceQueueCreateInfo	pQueueFamiliesCreateInfos[VK_QUEUE_PROTECTED_BIT];

		bool retrieveDevices	= false;
		bool calledLayers		= false;
		bool calledExtensions	= false;
		bool calledQeueue		= false;
		bool getQueue			= false;
		bool calledMemory		= false;
		int32_t codeOfError		= false;

		bool isLayerSuitable(VkLayerProperties sLayer, const char **desiredLayers, uint32_t size);
		bool isExtensionSuitable(VkExtensionProperties sExtensions, const char **desiredExtensions, uint32_t size);
		bool isPhysicalDeviceSuitable(VkPhysicalDevice device, uint32_t type);
		bool isQueueFamilySuitable(VkQueueFamilyProperties queueProperties, VkQueueFamilyProperties needProperties);
		void fillQueueCreateInfo(VkQueueFamilyProperties properties, float priority, int index);
};

class Device2 : public Device
{
	public:
		void setLayers(const char **desiredLayers, uint32_t size);
		void setExtensions(const char **desiredExtensions, uint32_t size);
		bool setQueue(Surface &surface, VkQueueFamilyProperties properties, float priority);
		bool setQueue(VkQueueFamilyProperties properties, float priority);

	private:
		bool isLayerSuitable(VkLayerProperties sLayer, const char **desiredLayers, uint32_t size);
		bool isExtensionSuitable(VkExtensionProperties sExtensions, const char **desiredExtensions, uint32_t size);
		bool isPhysicalDeviceSuitable(VkPhysicalDevice device, uint32_t type);
		bool isQueueFamilySuitable(VkQueueFamilyProperties queueProperties, VkQueueFamilyProperties needProperties);
		void fillQueueCreateInfo(VkQueueFamilyProperties properties, float priority, int index);
};

#endif