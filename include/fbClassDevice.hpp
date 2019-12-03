/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassDevice.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 19:34:16 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/03 20:59:44 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_PHYSICAL_DEVICE_HPP
# define FB_CLASS_PHYSICAL_DEVICE_HPP

# include "vkClassContainer.hpp"

# define GRAPHIC_QUEUE			0
# define COMPUTE_QUEUE			1
# define TRANSFER_QUEUE			2
# define SPARSE_BINDING_QUEUE	3
# define PRESENT_QUEUE

class Device
{
	public:
		VkDevice			self			= VK_NULL_HANDLE;
		VkPhysicalDevice	physicalSelf	= VK_NULL_HANDLE;

		VkPhysicalDeviceFeatures	sFeatures	= {};
		VkPhysicalDeviceProperties	sProperties	= {};

		u_int32_t			availablePhysicalDeviceCount = 0;
		VkPhysicalDevice	*pAvailablePhysicalDevices;

		u_int32_t				enabledLayerCount		= 0;
		u_int32_t				availableLayersCount	= 0;
		VkLayerProperties		*pAvailableLayers;
		const char				**ppEnabledLayerNames;

		u_int32_t				enabledExtensionCount		= 0;
		u_int32_t				availableExtensionsCount	= 0;
		VkExtensionProperties	*pAvailableExtensions;
		const char				**ppEnabledExtensionNames;

		u_int32_t				availableQueuesFamiliesCount = 0;
		VkQueueFamilyProperties	*pAvailableQueuesFamilies;

		uint32_t				queueFamilyCreateInfoCount	= 0;
		VkDeviceQueueCreateInfo	*pQueueFamilies = new VkDeviceQueueCreateInfo[2];

		VkQueue		presentQueueFamily = VK_NULL_HANDLE;
		VkQueue		graphicQueueFamily = VK_NULL_HANDLE;
		int32_t		presentQueueFamilyIndex	= -1;
		int32_t		graphicQueueFamilyIndex	= -1;

		Device();

		void retrievePhysicalDevices(VkInstance instance);
		void attachPhysicalDevice(int deviceType);
		void setupNext(const void *pNext);
		void setupFlags(VkInstanceCreateFlags flags);
		void setupLayers(std::vector<const char *> &desiredLayers);
		void setupExtensions(std::vector<const char *> &desiredExtensions);

		VkLayerProperties		*getLayers();
		VkExtensionProperties	*getExtensions();

		VkDevice getSelf(void);
		VkDevice operator()(void);

		VkQueueFamilyProperties	*getQueueFamilies();
		void	checkCompatibleWithSurface(Surface surface);

		void	setupQueueFamilyCreateInfo(float queuePriority, int queueCount, int queueIndex);
		void	retrieveAllQueus();
		void	setupQueue(int type);

		void	create();
		void	queryQueue();

	private:
		VkDeviceCreateInfo sCreateInfo = {};

		bool retrieveDevices	= false;
		bool calledLayers		= false;
		bool calledExtensions	= false;
		bool calledQeueue		= false;
		int32_t codeOfError		= false;

		bool isLayerSuitable(VkLayerProperties sLayer, std::vector<const char *> &desiredLayers);
		bool isExtensionSuitable(VkExtensionProperties sExtensions, std::vector<const char *> &desiredExtensions);
		bool isPhysicalDeviceSuitable(VkPhysicalDevice testingDevice, int deviceType);
};

#endif