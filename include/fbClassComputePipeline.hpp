/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassComputePipeline.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 18:46:20 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/26 18:49:34 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_COMPUTE_PIPELINE_HPP
# define FB_CLASS_COMPUTE_PIPELINE_HPP

# include "firebreak.hpp"

class ComputePipeline
{
	public:
		ComputePipeline();
		ComputePipeline(ComputePipeline &anotherComputePipeline);

		VkPipeline					&getSelf(uint32_t index = 0);
		VkComputePipelineCreateInfo	&getCreateInfo(uint32_t index = 0);
		VkAllocationCallbacks		&getAllocation();
		int32_t						getCodeOfError();

		void create(Device &device);
		void setAmount(uint32_t amount);
		void toCache();
		void destroy(Device &device, uint32_t index = 0);

	protected:
		VkPipeline					self			= VK_NULL_HANDLE;
		VkComputePipelineCreateInfo	sCreateInfo		= {};
		VkPipelineCache				cache			= VK_NULL_HANDLE;
		VkAllocationCallbacks		sAllocation		= {};

		VkPipeline					*pSelfs			= nullptr;
		VkComputePipelineCreateInfo	*pCreateInfos	= nullptr;

		int32_t		codeOfError	= false;
		uint32_t	amount		= 1;
};

class ComputePipeline2 : public ComputePipeline
{
	public:
		ComputePipeline2() : ComputePipeline() { }
		ComputePipeline2(ComputePipeline2 &anotherComputePipeline);

		void setCache(VkPipelineCache &cache);

		void create(Device &device, uint32_t count = 1)
		{

		}
};

#endif