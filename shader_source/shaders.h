/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.21school.ru>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 12:23:00 by vrichese          #+#    #+#             */
/*   Updated: 2019/08/30 15:08:10 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADERS_H
# define SHADERS_H

#include "../include/glew.h"

namespace Shaders
{
    const GLchar *vertexShader =
	"#version 330 core															\
																				\
	layout (location = 0) in vec3 positionVBO;									\
	layout (location = 1) in vec3 normalVBO;									\
																				\
	out vec3	fragPos;														\
	out	vec3	normalVER;														\
																				\
	uniform mat4 model;															\
	uniform mat4 view;															\
	uniform mat4 projection;													\
																				\
	void main()																	\
	{																			\
		gl_Position		= projection * view * model * vec4(positionVBO, 1.0f);	\
		fragPos			= vec3(model * vec4(positionVBO, 1.0f));				\
		normalVER		= normalVBO;											\
	}																			\
	";

	const GLchar *vertexLightShader =
	"#version 330 core															\
																				\
	layout (location = 0) in vec3 positionVBO;									\
																				\
	uniform mat4 model;															\
	uniform mat4 view;															\
	uniform mat4 projection;													\
																				\
	void main()																	\
	{																			\
		gl_Position		= projection * view * model * vec4(positionVBO, 1.0f);	\
	}																			\
	";

	const GLchar *fragmentShader =
	"#version 330 core															\
																				\
	in vec3				normalVER;												\
	in vec3				fragPos;												\
																				\
	out vec4			colorFra;												\
																				\
	uniform	vec3		objectColor;											\
	uniform vec3		lightColor;												\
	uniform vec3		lightPos;												\
	uniform vec3		eyePos;													\
																				\
	void main()																	\
	{																			\
		float colorConst = 0.15f;												\
		float constReflection = 0.5f;											\
		vec3 norm = normalize(normalVER);										\
		vec3 lightDir = normalize(lightPos - fragPos);							\
		float diff = max(dot(norm, lightDir), 0.0);								\
		vec3 diffuse = diff * lightColor;										\
		vec3 viewDir = normalize(eyePos - fragPos);								\
		vec3 reflectDir = reflect(-lightDir, norm);								\
		float refRate = pow(max(dot(viewDir, reflectDir), 0.0), 64);			\
		vec3 specular = constReflection * refRate * lightColor;					\
		vec3 result = (colorConst + diffuse + specular) * objectColor;			\
		colorFra = vec4(result, 1.0f);											\
	}																			\
	";

	const GLchar *fragmentLightShader =
	"#version 330 core															\
																				\
	out vec4			colorFra;												\
																				\
	uniform vec2		test;													\
																				\
	void main()																	\
	{																			\
		colorFra = vec4(test.x);							\
	}																			\
	";
};

#endif