/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_set_action.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:21:11 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/10 16:59:27 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_data_philosopher *philosopher, const char *str)
{
	pthread_mutex_lock(&(philosopher->data_shared->mutex_print));
	if (philosopher->data_shared->is_active_simulation)
		printf("%ld %d %s\n", philosopher->self->timestamp_last_action,
			philosopher->self->id + 1, str);
	pthread_mutex_unlock(&(philosopher->data_shared->mutex_print));
}

void	set_die(t_data_philosopher *philosopher)
{
	long	timestamp;

	timestamp = get_current_time_in_ms();
	philosopher->self->timestamp_last_action = timestamp;
	philosopher->self->status = DEAD;
	pthread_mutex_lock(&(philosopher->data_shared->mutex_print));
	if (philosopher->data_shared->is_active_simulation)
		printf("%ld %d %s\n", philosopher->self->timestamp_last_action,
			philosopher->self->id + 1, "died");
	philosopher->data_shared->is_active_simulation = 0;
	pthread_mutex_unlock(&(philosopher->data_shared->mutex_print));
}

void	set_think(t_data_philosopher *philosopher)
{
	long	timestamp;

	timestamp = get_current_time_in_ms();
	philosopher->self->status = THINK;
	philosopher->self->timestamp_last_action = timestamp;
	print_action(philosopher, "is thinking");
}

void	set_eat(t_data_philosopher *philosopher)
{
	long	timestamp;
	int		left;

	left = 0;
	timestamp = get_current_time_in_ms();
	philosopher->self->status = EAT;
	philosopher->self->timestamp_last_action = timestamp;
	philosopher->self->time_last_eat = timestamp;
	if (philosopher->self->id == 0)
		left = philosopher->data_shared->data_main.num_of_philo - 1;
	else
		left = philosopher->self->id - 1;
	lock_fork(philosopher, left);
	philosopher->self->fork.available = 0;
	philosopher->philos[left]->fork.available = 0;
	unlock_fork(philosopher, left);
	philosopher->self->fork.last_user = philosopher->self;
	philosopher->philos[left]->fork.last_user = philosopher->self;
	print_action(philosopher, "has taken a fork");
	print_action(philosopher, "has taken a fork");
	print_action(philosopher, "is eating");
}

void	set_sleep(t_data_philosopher *philosopher)
{
	long	timestamp;
	int		left;

	philosopher->self->number_of_eat++;
	if (!is_reach_eat_times(philosopher))
	{
		if (philosopher->self->id == 0)
			left = philosopher->data_shared->data_main.num_of_philo - 1;
		else
			left = philosopher->self->id - 1;
		philosopher->self->fork.available = 1;
		philosopher->philos[left]->fork.available = 1;
		timestamp = get_current_time_in_ms();
		philosopher->self->status = SLEEP;
		philosopher->self->timestamp_last_action = timestamp;
		print_action(philosopher, "is sleeping");
	}
}
