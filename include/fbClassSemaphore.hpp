/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassSemaphore.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 17:23:48 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/15 17:38:42 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_SEMAPHORE_HPP
# define FB_CLASS_SEMAPHORE_HPP

#include "firebreak.hpp"

class Semaphore
{
	public:
		Semaphore();
		Semaphore(Semaphore &anotherSemaphore);

		VkSemaphore				getSelf();
		VkSemaphoreCreateInfo	*getCreateInfo();
		VkAllocationCallbacks	*getAllocation();

		void create(Device &device, int mode = VK_NULL_HANDLE);

	private:
		VkSemaphore				self		= VK_NULL_HANDLE;
		VkSemaphoreCreateInfo	sCreateInfo	= {};
		VkAllocationCallbacks	sAllocation	= {};

		int32_t	codeOfError = false;
};

#endif