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

.PHONY: all clean fclean re