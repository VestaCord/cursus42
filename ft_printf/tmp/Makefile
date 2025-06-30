SRCS			=	main.c

# substituition syntax $(VARIABLE:OLD_PREFIX%OLD_SUFFIX=NEW_PREFIX%NEW_SUFFIX)
# this implicitly compiles as below:
# %.o: %.c: # can also be written .c.o, but partially deprecated
# 	${CC} ${CFLAGS} -c $< -o $@ # here, $@ is also ${<:.c=.o}
OBJS			= $(SRCS:.c=.o)
BONUS			=	
BONUS_OBJS		= $(BONUS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -I.. -I../libft
LDFLAGS			= -L.. -L../libft
LDLIBS			= -lftprintf -lft

NAME			= ftprintftester

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all:			$(NAME)

$(NAME):		$(OBJS)
				${CC} ${LDFLAGS} ${OBJS} -o ${NAME} ${LDLIBS}

clean:	
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

# dont actually need this because we dont have files of these names
.PHONY:			all clean fclean re bonus