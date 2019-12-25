/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassShader.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 18:55:31 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/25 20:13:33 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "firebreak.hpp"

Shader::Shader()
{
	;
}

Shader::Shader(Shader &anotherShader)
{
	;
}

VkShaderModule	Shader::getSelf()
{
	return (self);
}

VkShaderModuleCreateInfo	*Shader::getCreateInfo()
{
	return (&sCreateInfo);
}

VkAllocationCallbacks	*Shader::getAllocation()
{
	return (&sAllocation);
}

int32_t	Shader::getCodeOfError()
{
	return (codeOfError);
}

void	Shader::create(Device &device)
{
	codeOfError = vkCreateShaderModule(device.getSelf(), &sCreateInfo, sAllocation.pfnAllocation ? &sAllocation : nullptr, &self);
	THROW_EXCEPTION("Failed to create shader module");
}
