/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassDevice.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:34:16 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/16 17:48:55 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_PHYSICAL_DEVICE_HPP
# define FB_CLASS_PHYSICAL_DEVICE_HPP

# include "firebreak.hpp"

typedef enum	FbQueueTypes
{
	FB_QUEUE_GRAPHIC,
	FB_QUEUE_COMPUTE,
	FB_QUEUE_TRANSFER,
	FB_QUEUE_SPARSE_BINDING,
	FB_QUEUE_PRESENT,
	FB_QUEUE_MAX
}				FbQueueTypes;

typedef struct		FbQueue
{
	VkQueue			self;
	int32_t			index;
}					FbQueue;

class Device
{
	public:
		Device();
		Device(Device &anotherDevice) { }

		VkDevice							getSelf();
		VkPhysicalDevice					getPhysicalSelf();
		VkDeviceCreateInfo					*getCreateInfo();
		VkAllocationCallbacks				*getAllocation();
		VkPhysicalDeviceFeatures			*getFeatures();
		VkPhysicalDeviceProperties			*getProperties();
		VkPhysicalDeviceMemoryProperties	*getMemoryProperties();
		VkLayerProperties					*getLayers(uint32_t *size = nullptr);
		VkExtensionProperties				*getExtensions(uint32_t *size = nullptr);
		VkQueueFamilyProperties				*getQueueFamilyProperties(uint32_t *size = nullptr);
		VkDeviceQueueCreateInfo				*getDeviceQueueCreateInfo();
		FbQueue								*getQueues();

		void attachPhysicalDevice(Instance &instance, uint32_t type);
		void pushQueue(int32_t type);
		void create();
		void retrieveQueues();
		void clear(int mode = VK_NULL_HANDLE);

		friend class Device2;

		~Device();

	private:
		VkDevice				self			= VK_NULL_HANDLE;
		VkPhysicalDevice		physicalSelf	= VK_NULL_HANDLE;
		VkDeviceCreateInfo		sCreateInfo		= {};
		VkAllocationCallbacks	sAllocation		= {};

		VkPhysicalDeviceFeatures			sFeatures			= {};
		VkPhysicalDeviceProperties			sProperties			= {};
		VkPhysicalDeviceMemoryProperties	sMemoryProperties	= {};

		VkLayerProperties		*pAvailableLayers			= nullptr;
		VkExtensionProperties	*pAvailableExtensions		= nullptr;
		VkQueueFamilyProperties	*pAvailableQueuesFamilies	= nullptr;
		FbQueue					pQueues[FB_QUEUE_MAX];

		uint32_t				availableLayersCount			= 0;
		uint32_t				availableExtensionsCount		= 0;
		uint32_t				availableQueuesFamiliesCount	= 0;

		int32_t codeOfError		= false;
};

class Device2 : public Device
{
	public:
		void setLayers(const char **desiredLayers, uint32_t size);
		void setExtensions(const char **desiredExtensions, uint32_t size);

		bool setQueue(uint32_t type, VkExtent3D minImageTransferGranularity, uint32_t timestampValidBits, uint32_t queueCount, float priority);
		bool setPresentQueue(Surface &surface, VkExtent3D minImageTransferGranularity, uint32_t timestampValidBits, uint32_t queueCount, float priority);

		uint32_t *requireIndexArray();

	private:
		bool isLayerSuitable(VkLayerProperties sLayer, const char **desiredLayers, uint32_t size);
		bool isExtensionSuitable(VkExtensionProperties sExtensions, const char **desiredExtensions, uint32_t size);
		bool isQueueFamilySuitable(VkQueueFamilyProperties queueProperties, VkExtent3D minImageTransferGranularity, uint32_t timestampValidBits, uint32_t queueCount);
		bool isPhysicalDeviceSuitable(VkPhysicalDevice device, uint32_t type);
};

#endif