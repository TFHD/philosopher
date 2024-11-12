NAME	:= 	philo

DIR		:=	srcs/

SRCS	:= 	main.c \
			parsing.c \
			utils.c

OBJS	:=	$(patsubst %.c, $(DIR)%.o, $(SRCS))

OBJSB	:=	$(patsubst %.c, $(DIRB)%.o, $(SRCSB))

CC		:= cc

FLAGS 	:= -Wall -Werror -Wextra -I includes

all: ${NAME}

${NAME}: ${OBJS}
	${CC} -o ${NAME} ${OBJS}

${DIR}%.o: ${DIR}%.c
	${CC} ${FLAGS} -o $@ -c $<
	
clean:
	rm -f ${OBJS} ${OBJSB}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: clean fclean re all
