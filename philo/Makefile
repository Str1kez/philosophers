FILES	=	actions.c \
			ft_atoi.c \
			init.c \
			main.c \
			threads.c \
			utils.c

HEADS	=	philo.h

GCC     =   gcc
OBJS    =   $(FILES:.c=.o)
FLAGS   =   -Wall -Wextra -Werror
NAME    =   philo
LIB		=	-lpthread

.c.o:
	${GCC} ${FLAGS} -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(HEADS)
	$(GCC) $(FLAGS) $(OBJS) $(LIB) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all, re, clean, $(NAME), fclean
