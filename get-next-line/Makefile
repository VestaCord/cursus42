SRCS			=	# tester.c  get_next_line.c get_next_line_utils.c

# substituition syntax $(VARIABLE:OLD_PREFIX%OLD_SUFFIX=NEW_PREFIX%NEW_SUFFIX)
# this implicitly compiles as below:
# %.o: %.c: # can also be written .c.o, but partially deprecated
# 	${CC} ${CFLAGS} -c $< -o $@ # here, $@ is also ${<:.c=.o}
OBJS			= $(SRCS:.c=.o)

BONUS			=	tester_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c
BONUS_OBJS		= $(BONUS:.c=.o)

CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -D BUFFER_SIZE=42

NAME			= test

all:			$(NAME)

# s is to archive object files
$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
				$(RM) $(OBJS) $(BONUS_OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

bonus:			$(BONUS_OBJS)
				$(CC) $(CFLAGS) $(SRCS) -o $(NAME) $(BONUS_OBJS)



# dont actually need this because we dont have files of these names
.PHONY:			all clean fclean re bonus allft