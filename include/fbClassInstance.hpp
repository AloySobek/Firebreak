/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassInstance.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 16:22:46 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/16 18:23:08 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_INSTANCE_HPP
# define FB_CLASS_INSTANCE_HPP

# include "firebreak.hpp"

# ifdef NDEBUG
	#define safeCall(x) try { x() } catch (const std::exception &error){ std::cerr << error.what() << std::endl; exit(FAILURE_EXIT) }
# else
	#define safeCall(x) x()
# endif


class Instance
{
	public:
		Instance();
		Instance(Instance &anotherInstance) { };

		VkInstance				getSelf();
		VkApplicationInfo		*getAppInfo();
		VkInstanceCreateInfo	*getCreateInfo();
		VkAllocationCallbacks	*getAllocationInfo();
		VkLayerProperties		*getLayers(uint32_t *size = nullptr);
		VkExtensionProperties	*getExtensions(uint32_t *size = nullptr);
		VkPhysicalDevice		*getPhysicalDevices(uint32_t *size = nullptr);
		int32_t					getErrorCode();

		void	create();
		void	clear(uint32_t mode = VK_NULL_HANDLE);

		friend class Instance2;

		~Instance();

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
		void	setAppInfo(const char *pName, uint32_t appVersion, const char *pEngineName, uint32_t engineVersion, uint32_t vulkanVersion = VK_VERSION_1_0);
		void	setLayers(const char **desiredLayers, uint32_t size);
		void	setExtensions(const char **desiredExtensions, uint32_t size);

	public:
		bool	isLayerSuitable(VkLayerProperties sLayer, const char **desiredLayers, uint32_t size);
		bool	isExtensionSuitable(VkExtensionProperties sExtension, const char **desiredExtensions, uint32_t size);
};

#endif