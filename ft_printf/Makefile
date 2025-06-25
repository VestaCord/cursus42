SRCS			=	ft_printf.c dispatch.c dispatch_cspdi.c dispatch_uxX.c

# substituition syntax $(VARIABLE:OLD_PREFIX%OLD_SUFFIX=NEW_PREFIX%NEW_SUFFIX)
# this implicitly compiles as below:
# %.o: %.c: # can also be written .c.o, but partially deprecated
# 	${CC} ${CFLAGS} -c $< -o $@ # here, $@ is also ${<:.c=.o}
OBJS			= $(SRCS:.c=.o)

BONUS			=	dispatch_%.123456789\#_bonus.c dispatch_-0+_bonus.c
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

bonus:			$(OBJS) $(BONUS_OBJS)
				ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

allft:
				cd libft && make all


# dont actually need this because we dont have files of these names
.PHONY:			all clean fclean re bonus allft