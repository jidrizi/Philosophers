
CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

NAME = philosophers

DEPS = philosophers.h

SRCS = main.c error_stuff.c misc.c check.c ft_calloc.c inits.c  philozophize.c \
		make_threads.c

OBJS = $(SRCS:%.c=bin/%.o)

all: $(NAME)

bin :
	@mkdir -p bin

bin/%.o : %.c $(DEPS) | bin
	$(CC) -c -o $@ $< $(CFLAGS)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

clean :
	@rm -rf bin
	@echo "Object files removed"

fclean : clean
	@rm -f $(NAME)
	@echo "$(NAME) removed"

re: fclean all

.PHONY: all clean fclean re