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

class Cache
{
	public:
		Cache() { };
		Cache(Cache &anotherCache) { };

		~Cache() { };

	protected:
		VkPipelineCache				self;
		VkPipelineCacheCreateInfo	sCreateInfo = { };
}

#endif