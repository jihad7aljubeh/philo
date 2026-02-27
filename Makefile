NAME        = philo

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -pthread

RM          = rm -f

SRCS        = main.c \
              init.c \
              parsing.c \
              utils.c \
              routine.c \
              monitor.c \
              forks.c \
              cleanup.c

OBJS        = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re