/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassInstance.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 16:22:46 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/15 17:22:06 by Rustam           ###   ########.fr       */
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

		VkInstance				getSelf();
		VkApplicationInfo		*getAppInfo();
		VkInstanceCreateInfo	*getCreateInfo();
		VkAllocationCallbacks	*getAllocationInfo();
		VkLayerProperties		*getAvailableLayers(uint32_t *size = nullptr);
		VkExtensionProperties	*getAvailableExtensions(uint32_t *size = nullptr);
		VkPhysicalDevice		*getPhysicalDevices(uint32_t *size = nullptr);

		void create(int mode = VK_NULL_HANDLE);

		~Instance();
		friend class Instance2;

	private:
		VkInstance				self				= VK_NULL_HANDLE;
		VkInstanceCreateInfo	sCreateInfo			= {};
		VkApplicationInfo		sApplicationInfo	= {};
		VkAllocationCallbacks	sAllocation			= {};

		VkLayerProperties		*pAvailableLayers			= nullptr;
		VkExtensionProperties	*pAvailableExtensions		= nullptr;
		VkPhysicalDevice		*pAvailablePhysicalDevices	= nullptr;

		uint32_t availableLayersCount			= 0;
		uint32_t availableExtensionsCount		= 0;
		uint32_t availablePhysicalDeviceCount	= 0;

		int32_t	codeOfError	= false;
};

class Instance2 : public Instance
{
	public:
		void	setLayers(const char **desiredLayers, uint32_t size);
		void	setExtensions(const char **desiredExtensions, uint32_t size);
		void	setAppInfo(const char *pName, uint32_t appVersion, const char *pEngineName, uint32_t engineVersion, uint32_t vulkanVersion = VK_VERSION_1_0);

	public:
		bool	isLayerSuitable(VkLayerProperties sLayer, const char **desiredLayers, uint32_t size);
		bool	isExtensionSuitable(VkExtensionProperties sExtension, const char **desiredExtensions, uint32_t size);
};

#endif