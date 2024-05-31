# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rvandepu <rvandepu@student.42lehavre.fr>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/06 16:11:02 by rvandepu          #+#    #+#              #
#    Updated: 2024/05/31 19:33:09 by rvandepu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COMMON_FILES := init.c \
				lst_utils.c \
				oplist.c \
				swap.c \
				push.c \
				rot.c \
				rrot.c \

NAME  := push_swap
FILES := $(NAME).c \
		 $(COMMON_FILES) \
		 algo.c \
		 turk.c \
		 squash.c \

BONUS_NAME  := checker
BONUS_FILES := $(BONUS_NAME).c \
			   $(COMMON_FILES) \

OBJ := $(FILES:%.c=%.o)
BONUS_OBJ := $(BONUS_FILES:%.c=%.o)

CFLAGS += -Wall -Wextra -Werror

# https://github.com/remty5/libft
LIBFT_DIR	:= libft
LIBFT		:= libft.a
LIBFT_PATH	:= $(LIBFT_DIR)/$(LIBFT)
CPPFLAGS	+= -I$(LIBFT_DIR)
LDFLAGS		+= -L$(LIBFT_DIR)
LDLIBS		+= -lft

.PHONY: all clean fclean re bonus test

all: $(NAME)
bonus: $(BONUS_NAME)

clean:
	$(MAKE) -s -C $(LIBFT_DIR) fclean
	$(RM) $(OBJ) $(BONUS_OBJ)

fclean: clean
	$(RM) $(NAME) $(BONUS_NAME)

re: fclean all

test: CFLAGS += -g
test: re bonus

$(LIBFT_PATH):
	$(MAKE) -s -C $(LIBFT_DIR) $(LIBFT) -j $$(nproc)

$(NAME): $(OBJ) | $(LIBFT_PATH)
$(BONUS_NAME): $(BONUS_OBJ) | $(LIBFT_PATH)
