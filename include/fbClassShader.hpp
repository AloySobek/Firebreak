/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbClassShader.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Rustam <super.rustamm@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 18:51:42 by Rustam            #+#    #+#             */
/*   Updated: 2019/12/25 19:08:11 by Rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FB_CLASS_SHADER_HPP
# define FB_CLASS_SHADER_HPP

# include "firebreak.hpp"

class Shader
{
	public:
		Shader();
		Shader(Shader &anotherShader);

		VkShaderModule				getSelf();
		VkShaderModuleCreateInfo	*getCreateInfo();
		VkAllocationCallbacks		*getAllocation();
		int32_t						getCodeOfError();

		void create(Device &device);
		void destroy(Device &device);

		~Shader();

	protected:
		VkShaderModule				self;
		VkShaderModuleCreateInfo	sCreateInfo = {};
		VkAllocationCallbacks		sAllocation	= {};

		int32_t	codeOfError	= false;
};

#endif