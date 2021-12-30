NAME = philo_bonus

SRCS = philo_bonus.c philo_bonus_parser.c philo_bonus_utils.c philo_bonus_utils2.c\
		philo_bonus_routine.c philo_bonus_init.c

HEADER = philo_bonus.h

DIR_OBJS = objs
OBJS = $(patsubst %.c, %.o, $(SRCS))
PATH_OBJS = $(addprefix $(DIR_OBJS)/, $(OBJS))

CC = gcc

FLAGS = -Wall -Werror -Wextra -g -pthread

RM = rm -rf

all:$(NAME)

$(NAME): $(PATH_OBJS)
	$(CC) $(FLAGS) $^ -o $@

$(DIR_OBJS)/%.o: %.c $(HEADER) Makefile
	@mkdir -p $(DIR_OBJS)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(DIR_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re