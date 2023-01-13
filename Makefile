# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/28 21:52:18 by wonyang           #+#    #+#              #
#    Updated: 2023/01/13 15:29:35 by wonyang          ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

# define compile options
NAME		= minishell
LIBFT		= libft
LIBFT_HEADER = libft.h
LIBFT_LIB	= $(LIBFT)/libft.a
RDLINE_DIR	= $(shell brew --prefix readline)

HEADERS		= -I$(LIBFT) \
			  -Iincludes \
			  -I$(RDLINE_DIR)/include/ \

LIBS		= -lft -L$(LIBFT) \
			  -L$(RDLINE_DIR)/lib/ -lreadline\

CFLAGS		= -Wall -Werror -Wextra -g3 -fsanitize=address

# builtin source files
BTN_DIR		= builtin/

_BTN_SRCS	= cd.c \
			  echo.c \
			  pwd.c \
			  env.c \
			  unset.c \
			  exit.c \
			  export.c \
			  print_export.c \

BTN_SRCS	= $(addprefix $(BTN_DIR), $(_BTN_SRCS))

# ds_tree source files
TREE_DIR	= ds_tree/

_TREE_SRCS	= add.c \
			  delete.c \
			  init.c \
			  search.c \

TREE_SRCS	= $(addprefix $(TREE_DIR), $(_TREE_SRCS))

# ds_envp source files
ENVP_DIR	= ds_envp/

_ENVP_SRCS	= cast_arr.c \
			  cast_list.c \
			  delete.c \
			  init.c \
			  search.c \
			  set.c \

ENVP_SRCS	= $(addprefix $(ENVP_DIR), $(_ENVP_SRCS))

# parsing part source files
PARSING_DIR		= parsing/

_PARSING_SRCS	= token.c \
				  arr.c \
				  check_syntax.c \
				  check_tnode.c \
				  check_type.c \
				  make_node.c \
				  make_tree.c

PARSING_SRCS	= $(addprefix $(PARSING_DIR), $(_PARSING_SRCS))

# execute part source files
EXE_DIR			= execute/

_EXE_SRCS		= argv.c \
				  path.c \
				  redirection.c \
				  util.c \
				  heredoc.c \
				  heredoc_util.c \
				  execute.c \
				  child.c \
				  preprocess.c \

EXE_SRCS		= $(addprefix $(EXE_DIR), $(_EXE_SRCS))

# main source files
SRCS		= main.c \
			  terminal.c \

OBJS		= $(BTN_SRCS:%.c=%.o) \
			  $(TREE_SRCS:%.c=%.o) \
			  $(ENVP_SRCS:%.c=%.o) \
			  $(PARSING_SRCS:%.c=%.o) \
			  $(EXE_SRCS:%.c=%.o) \
			  $(SRCS:%.c=%.o) \

# define compile commands
$(NAME) : 	$(OBJS) $(LIBFT_LIB)
			cc $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

all	:		$(NAME)

$(LIBFT_LIB):
			make bonus -C $(LIBFT)/

%.o	: 		%.c
			cc $(CFLAGS) -c $^ $(HEADERS) -o $@

clean	:
			rm -f $(OBJS)
			make clean -C $(LIBFT)

fclean	:	
			make clean
			rm -f $(NAME)
			make fclean -C $(LIBFT)

re	:		
			make fclean
			make all

.PHONY	:	all clean fclean re
