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

class FbInstance
{
	public:
		FbInstance(VkInstanceCreateInfo info = {}, VkAllocationCallbacks allocation = {});
		FbInstance(VkAllocationCallbacks allocation) : FbInstance({}, allocation) { }

		VkInstance				&getSelf()			{ assert(self); return (self); }
		VkInstanceCreateInfo	&getCreateInfo()	{ return (sCreateInfo); }
		VkAllocationCallbacks	&getAllocation()	{ return (sAllocation); }
		int32_t					getErrorCode()		{ return (codeOfError); }

		virtual void	create();
		virtual void	destroy();

		virtual ~FbInstance() { destroy(); }

	protected:
		VkInstance				self;
		VkInstanceCreateInfo	sCreateInfo;
		VkAllocationCallbacks	sAllocation;

		int32_t	codeOfError;
};

/*
** This border to the next layer of firebreak framework <><><><><><><><><><><><>
** This border to the next layer of firebreak framework <><><><><><><><><><><><>
** This border to the next layer of firebreak framework <><><><><><><><><><><><>
*/

static std::vector<char *> namesStub{VK_NULL_HANDLE};

class FbInstance2 : protected FbInstance
{
	public:
		FbInstance2(std::vector<char *>	&layers);
		FbInstance2(std::vector<char *>	&extensions = namesStub, std::vector<char *> &layers = namesStub);

		std::vector<VkLayerProperties>		&getLayers();
		std::vector<VkExtensionProperties>	&getExtensions(const char *pLayerName = nullptr);
		std::vector<VkPhysicalDevice>		&getPhysicalDevices();

		void setAppInfo(const char *pName, uint32_t appVersion, const char *pEngineName,
							uint32_t engineVersion, uint32_t vulkanVersion = VK_VERSION_1_1, void *pNext = nullptr);
		void setLayers(std::vector<char *> &desiredLayers);
		void setExtensions(std::vector<char *> &desiredExtensions);
		void setNext(void *pNext) { assert(pNext); sCreateInfo.pNext = pNext; }

		void create(VkInstanceCreateFlags flags = 0);

	public:
		VkApplicationInfo					sApplicationInfo;

		std::vector<VkLayerProperties>		availableLayers;
		std::vector<VkExtensionProperties>	availableExtensions;
		std::vector<VkPhysicalDevice>		availablePhysicalDevices;
		std::vector<char *>					selectedLayers;
		std::vector<char *>					selectedExtensions;
};

#endif