MAKEFLAGS += --no-print-directory

OBJS = \
	ft_atoi.o \
	philo_launch_philosopher.o \
	philo_main.o \
	philo_manage_action.o \
	philo_utils.o \
	philo_set_action.o \
	philo_status_condition.o \
	philo_close_project.o \
	philo_verify_input.o \

all: philo_bonus

philo_bonus: $(OBJS)
	gcc $^ -g3 -o $@

%.o: %.c \
	gcc -c $< -g3 -Wall -Wextra -Werror -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f philo_bonus

re: fclean all

.PHONY: all clean fclean re