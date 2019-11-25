# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/18 20:01:18 by vrichese          #+#    #+#              #
#    Updated: 2019/11/22 19:09:11 by vrichese         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME						:= vulkan

SOURCE_DIR					:= source/
LIBS_DIR					:= libs/
INCLUDE_DIR					:= include/
CLASSES_DIR					:= $(INCLUDE_DIR)classes/
VULKAN_DIR					:= /usr/local/lib/
VULKAN_INCLUDE_DIR			:= /usr/local/include/

GLFW						:= $(LIBS_DIR)libglfw.3.3.dylib

SOURCE						:= main.cpp vkVulkanMethods.cpp

OBJ							:= $(SOURCE:.cpp=.o)

CC							:= g++

FLAGS						:= -g -std=c++14

VULKAN						:= $(VULKAN_DIR)libvulkan.1.1.121.dylib
GLFW						:= $(LIBS_DIR)libglfw.3.3.dylib

vpath %.cpp $(SOURCE_DIR)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -I $(VULKAN_INCLUDE_DIR) -I $(CLASSES_DIR) -I $(INCLUDE_DIR) $(VULKAN) $(GLFW) $^ -o $@

$(OBJ):%.o:%.cpp
	$(CC) $(FLAGS) -I $(VULKAN_INCLUDE_DIR) -I $(CLASSES_DIR) -I $(INCLUDE_DIR) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.SILENT: all $(NAME) $(OBJ) clean fclean re
