/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassCache.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 17:11:57 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/27 17:15:04 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_CACHE_HPP
# define FB_CLASS_CACHE_HPP

# include "firebreak.hpp"

class PipelineCache
{
	public:
		PipelineCache			();
		explicit PipelineCache	(std::initializer_list<int> initList);
		PipelineCache			(PipelineCache &anotherPipelineCache);

		VkPipelineCache				&getSelf();
		VkPipelineCacheCreateInfo	&getCreateInfo();
		VkAllocationCallbacks		&getAllocation();
		int32_t						getErrorCode();

		void create();
		void destroy();

		~PipelineCache();

	protected:
		VkPipelineCache				self		= VK_NULL_HANDLE;
		VkPipelineCacheCreateInfo	sCreateInfo	= {};
		VkAllocationCallbacks		sAllocation	= {};

		int32_t						codeOfError	= false;
};

#endif