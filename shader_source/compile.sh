# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    compile.sh                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/22 16:26:07 by vrichese          #+#    #+#              #
#    Updated: 2019/11/22 16:27:06 by vrichese         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

/usr/local/bin/glslangValidator -V ./vertexShader.vert
/usr/local/bin/glslangValidator -V ./fragmentShader.frag
