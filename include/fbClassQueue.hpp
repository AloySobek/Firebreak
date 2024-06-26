/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassQueue.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 17:01:23 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/30 14:36:35 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_QUEUE_HPP
# define FB_CLASS_QUEUE_HPP

# include "firebreak.hpp"

class Queue
{
	public:
		Queue();

		VkQueue						&getSelf		(uint32_t index = 0);
		VkDeviceQueueCreateInfo		&getCreateInfo	();
		int32_t						getCodeOfError	();

		void retrieve	(Device &device);
		void submitTasks(Device &device, uint32_t index = 0, Fence *pFence = nullptr);

		~Queue();

	private:
		std::vector<VkQueue>	pSelfs;
		VkDeviceQueueCreateInfo	sCreateInfo;

		std::vector<VkSubmitInfo>	pSubmitInfo;

		int32_t	codeOfError;
};

#endif