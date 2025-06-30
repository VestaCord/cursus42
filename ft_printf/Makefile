SRCS			=	conversion_char.c conversion_hex.c conversion_int.c conversion_percent.c \
					conversion_ptr.c conversion_str.c conversion_uint.c dispatch.c \
					ft_printf.c 

# substituition syntax $(VARIABLE:OLD_PREFIX%OLD_SUFFIX=NEW_PREFIX%NEW_SUFFIX)
# this implicitly compiles as below:
# %.o: %.c: # can also be written .c.o, but partially deprecated
# 	${CC} ${CFLAGS} -c $< -o $@ # here, $@ is also ${<:.c=.o}
OBJS			= $(SRCS:.c=.o)

BONUS			=	conversion_char.c conversion_hex.c conversion_int.c conversion_percent.c \
					conversion_ptr.c conversion_str.c conversion_uint.c \
					ft_printf_bonus.c dispatch_bonus.c flag_alternate_bonus.c flag_left_bonus.c \
					flag_plus_bonus.c flag_space_bonus.c flag_zero_bonus.c \
					width_and_precision_bonus.c

BONUS_OBJS		= $(BONUS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -Ilibft -Llibft -lft

NAME			= libftprintf.a

all:			$(NAME)

# s is to archive object files
$(NAME):		allft $(OBJS)
				ar rcs $(NAME) $(OBJS)

clean:
				cd libft && make $@
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				cd libft && make $@
				$(RM) $(NAME)

re:				fclean $(NAME)
				cd libft && make $@

bonus:			$(BONUS_OBJS)
				ar rcs $(NAME) $(BONUS_OBJS)

allft:
				cd libft && make all


# dont actually need this because we dont have files of these names
.PHONY:			all clean fclean re bonus allft