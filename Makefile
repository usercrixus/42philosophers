MAKEFLAGS += --no-print-directory

OBJS = \
	ft_atoi.o \
	philo_create_philosopher.o \
	philo_main.o \
	philo_manage_action.o \
	philo_utils.o \

all: philo

philo: $(OBJS)
	cc $^ -o $@

%.o: %.c \
	cc -c $< -Wall -Wextra -Werror -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f philo

re: fclean all

.PHONY: all bonus clean fclean re push_swap_tester libft.a submodule