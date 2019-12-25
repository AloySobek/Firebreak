/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassComputePipeline.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 18:51:24 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/25 20:15:43 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firebreak.hpp"

void	ComputePipeline::create(Device &device)
{
	codeOfError = vkCreateComputePipelines(device.getSelf(), cache, 0, pCreateInfo, &sAllocation, pSelf);
}