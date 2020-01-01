/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassInstance.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 16:22:46 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/29 15:55:27 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_INSTANCE_HPP
# define FB_CLASS_INSTANCE_HPP

# include "firebreak.hpp"

class Instance
{
	public:
		Instance();
		Instance(Instance &anotherInstance);
		Instance(VkInstanceCreateInfo &sInstanceCreateInfo);

		virtual VkInstance				&getSelf();
		virtual VkInstanceCreateInfo	&getCreateInfo();
		virtual VkAllocationCallbacks	&getAllocation();
		virtual int32_t					getErrorCode();

		void	create();
		void	destroy();

		virtual ~Instance();

	protected:
		VkInstance				self;
		VkInstanceCreateInfo	sCreateInfo;
		VkAllocationCallbacks	sAllocation;

		int32_t	codeOfError;
};

class Instance2 : protected Instance
{
	public:
		Instance2();
		Instance2(Instance2 &anotherInstance);
		Instance2(VkInstanceCreateInfo &sInstanceCreateInfo);

		virtual VkInstance		&getSelf() override;
		VkLayerProperties		*getLayers(uint32_t *size = nullptr);
		VkExtensionProperties	*getExtensions(uint32_t *size = nullptr);
		VkPhysicalDevice		*getPhysicalDevices(uint32_t *size = nullptr);

		void	setAppInfo(const char *pName, uint32_t appVersion, const char *pEngineName, uint32_t engineVersion, uint32_t vulkanVersion = VK_VERSION_1_0);
		void	setLayers(const char **desiredLayers, uint32_t size);
		void	setExtensions(const char **desiredExtensions, uint32_t size);

	public:
		VkApplicationInfo		sApplicationInfo			= {};

		VkLayerProperties		*pAvailableLayers			= nullptr;
		VkExtensionProperties	*pAvailableExtensions		= nullptr;
		VkPhysicalDevice		*pAvailablePhysicalDevices	= nullptr;

		uint32_t availableLayersCount			= 0;
		uint32_t availableExtensionsCount		= 0;
		uint32_t availablePhysicalDeviceCount	= 0;

		bool	isLayerSuitable(VkLayerProperties sLayer, const char **desiredLayers, uint32_t size);
};

#endif