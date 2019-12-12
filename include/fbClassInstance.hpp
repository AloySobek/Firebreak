/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassInstance.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 16:22:46 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/12 17:43:53 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_INSTANCE_HPP
# define FB_CLASS_INSTANCE_HPP

# include "firebreak.hpp"

class Instance
{
	public:
		Instance();
		Instance(Instance &anotherInstance) { };

		void setLayers(const char **desiredLayers, uint32_t size);
		void setExtensions(const char **desiredExtensions, uint32_t size);

		VkInstance				getSelf();
		VkApplicationInfo		*getAppInfo();
		VkInstanceCreateInfo	*getCreateInfo();
		VkAllocationCallbacks	*getAllocationInfo();
		VkLayerProperties		*getAvailableLayers();
		VkLayerProperties		*getAvailableLayers(uint32_t *size);
		VkExtensionProperties	*getAvailableExtensions();
		VkExtensionProperties	*getAvailableExtensions(uint32_t *size);
		VkPhysicalDevice		*getPhysicalDevices();
		VkPhysicalDevice		*getPhysicalDevices(uint32_t *size);

		void create(int mode = VK_NULL_HANDLE);

		VkInstance operator()(void);

		~Instance() { }

	private:
		VkInstance				self				= VK_NULL_HANDLE;
		VkInstanceCreateInfo	sCreateInfo			= {};
		VkApplicationInfo		sApplicationInfo	= {};
		VkAllocationCallbacks	sAllocation			= {};

		VkPhysicalDevice		*pAvailablePhysicalDevices;
		VkLayerProperties		*pAvailableLayers;
		VkExtensionProperties	*pAvailableExtensions;

		uint32_t availablePhysicalDeviceCount	= 0;
		uint32_t availableLayersCount			= 0;
		uint32_t availableExtensionsCount		= 0;

		bool	calledLayers	 	= false;
		bool	calledExtensions 	= false;
		bool	calledDevices		= false;
		int32_t	codeOfError			= false;

		bool	isLayerSuitable(VkLayerProperties sLayer, const char **desiredLayers, uint32_t size);
		bool	isExtensionSuitable(VkExtensionProperties sExtension, const char **desiredExtensions, uint32_t size);
};

#endif