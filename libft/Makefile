# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wonyang <wonyang@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/09 03:04:43 by wonyang           #+#    #+#              #
#    Updated: 2022/12/04 14:11:28 by wonyang          ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
HEADER = libft.h

CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror

SRCS = ft_memset.c \
	   ft_bzero.c \
	   ft_memcpy.c \
	   ft_memmove.c \
	   ft_memchr.c \
	   ft_memcmp.c \
	   ft_strlen.c \
	   ft_strlcpy.c \
	   ft_strlcat.c \
	   ft_strchr.c \
	   ft_strrchr.c \
	   ft_strnstr.c \
	   ft_strncmp.c \
	   ft_atoi.c \
	   ft_isalpha.c \
	   ft_isdigit.c \
	   ft_isalnum.c \
	   ft_isascii.c \
	   ft_isprint.c \
	   ft_toupper.c \
	   ft_tolower.c \
	   ft_calloc.c \
	   ft_strdup.c \
	   ft_substr.c \
	   ft_strjoin.c \
	   ft_strtrim.c \
	   ft_split.c \
	   ft_itoa.c \
	   ft_strmapi.c \
	   ft_striteri.c \
	   ft_putchar_fd.c \
	   ft_putstr_fd.c \
	   ft_putendl_fd.c \
	   ft_putnbr_fd.c \

SRCS_BONUS = ft_lstnew.c \
			 ft_lstadd_front.c \
			 ft_lstsize.c \
			 ft_lstlast.c \
			 ft_lstadd_back.c \
			 ft_lstdelone.c \
			 ft_lstclear.c \
			 ft_lstiter.c \
			 ft_lstmap.c \
			 ft_freesplit_bonus.c \
			 ft_strcmp_bonus.c \
			 ft_isinteger_bonus.c \
			 ft_abs_bonus.c \
			 ft_perror_exit_bonus.c \
			 ft_error_exit_bonus.c \
			 ft_open_bonus.c \
			 ft_close_bonus.c \
			 ft_malloc_bonus.c \
			 

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

ifdef WITH_BONUS
	OBJ_FILES = $(OBJS) $(OBJS_BONUS)
else
	OBJ_FILES = $(OBJS)
endif

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME) : $(OBJ_FILES) $(HEADER)
	ar crs $(NAME) $(OBJ_FILES)

bonus :
	@make WITH_BONUS=1 all

clean :
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean :
	make clean
	$(RM) $(NAME)

re :
	make fclean
	make all

.PHONY : bonus all clean fclean re
