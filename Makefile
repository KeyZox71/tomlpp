# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adjoly <adjoly@student.42angouleme.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/25 16:09:27 by adjoly            #+#    #+#              #
#    Updated: 2025/02/25 11:41:08 by adjoly           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL = bash

NAME = tomlpp.so

CC = c++

INCLUDES = includes/

OBJSDIR = obj/

SRCS = $(shell find src -name '*.cpp')

OBJS = $(addprefix $(OBJSDIR), $(SRCS:.cpp=.o))

CXXFLAGS = -Wall -Werror -Wextra -std=c++98 -MMD -MP -c -fPIC

LDFLAGS = -shared

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[1;33m
PURPLE = \e[0;35m
NC = \033[0m
DELETE = \x1B[2K\r

ifeq ($(VERBOSE),true)
	FLAGS += -D VERBOSE
endif

all: $(NAME)

$(NAME): $(OBJS)
	@printf "$(YELLOW)「✨」 feat($(NAME)): linking $(NAME)\n"
	@$(CC) -shared -o $(NAME) $(LDFLAGS) $(OBJS)
	@printf "$(YELLOW)「✨」 feat($(NAME)): $(NAME) compiled ! :D\n"

$(OBJSDIR)%.o: %.cpp
	@mkdir -p $(@D)
	@$(CC) -I $(INCLUDES) $(CXXFLAGS) -c $< -o $@
	@printf "$(DELETE)$(GREEN)「🔨」 build($<): object compiled\n"

clean:
	@rm -f $(OBJS)
	@printf "$(DELETE)$(RED)「🗑️」 clean($(OBJS)): object deleted\n"

fclean: clean
	@rm -f $(NAME)
	@rm -Rf $(OBJSDIR)
	@printf "$(RED)「🗑️」 fclean($(NAME)): program deleted\n"

re: fclean all

.PHONY: clean fclean all re
