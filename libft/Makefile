# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abel-mak <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 10:06:32 by abel-mak          #+#    #+#              #
#    Updated: 2020/11/07 12:34:22 by abel-mak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=libft.a

FLAGS=-Wall -Wextra -Werror

SRC=ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	  ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_toupper.c \
	  ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
	  ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	  ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c \
	  ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c \
	  ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c \
	  get_next_line.c get_next_line_utils.c

OBJECT=$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJECT)
	ar rc $(NAME) $(OBJECT)
	ranlib $(NAME)

%.o : %.c
	gcc $(FLAGS) -c $<

clean:
	rm -f $(OBJECT)

fclean: clean
	rm -f $(NAME)

re: fclean all
