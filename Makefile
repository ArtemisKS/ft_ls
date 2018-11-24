# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akupriia <akupriia@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/28 19:24:02 by vbrazas           #+#    #+#              #
#    Updated: 2018/11/15 20:06:58 by akupriia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ft_ls
LIB		=	ft_printf/
LIB_HDR	=	$(LIB)hdr/
SRC_D	=	sources/
SRC		=	$(SRC_D)ls_main.c \
			$(SRC_D)open_read.c \
			$(SRC_D)sort_hdir.c \
			$(SRC_D)extr_print_sinfo.c \
			$(SRC_D)print_output.c \
			$(SRC_D)assign_al.c \
			$(SRC_D)do_sorting.c \
			$(SRC_D)print_perm.c \
			$(SRC_D)print_lstat.c \
			$(SRC_D)handle_cap_r.c \
			$(SRC_D)utils.c \
			$(SRC_D)handle_xattr.c
OBJ_D	=	obj/
OBJ		=	$(addprefix $(OBJ_D), $(SRC:.c=.o))
LFLAGS	=	-lftprintf -L $(LIB)
IFLAGS	=	-I $(LIB_HDR) -I ./
CFLAGS	=	-Wall -Wextra -Werror


all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIB)
	gcc -o $(NAME) $(CFLAGS) $(LFLAGS) $(OBJ)

$(OBJ): | $(OBJ_D)

$(OBJ_D):
	mkdir -p $(OBJ_D)$(SRC_D)

$(OBJ_D)%.o: %.c
	gcc $(CFLAGS) $(IFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJ)
	make clean -C $(LIB)

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJ_D)
	make fclean -C $(LIB)

re: fclean all

.PHONY: all clean fclean re
