/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manage_action.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 23:46:03 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/15 16:56:13 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_data_philosopher *philosopher, const char *str)
{
	pthread_mutex_lock(&(philosopher->data_shared->mutex_print));
	printf("%ld %d %s\n", philosopher->self->timestamp_last_action, philosopher->self->id + 1, str);
	pthread_mutex_unlock(&(philosopher->data_shared->mutex_print));
}

int	is_eating_possible(t_data_philosopher *philosopher)
{
	t_philosopher *left;
	t_philosopher *right;

	if (philosopher->self->id == 0)
	{
		left = philosopher->philosophers[philosopher->data_shared->data_main.number_of_philosophers - 1];
		right = philosopher->philosophers[philosopher->self->id + 1];
	}
	else if (philosopher->self->id == philosopher->data_shared->data_main.number_of_philosophers - 1)
	{
		left = philosopher->philosophers[philosopher->self->id - 1];
		right = philosopher->philosophers[0];
	}
	else
	{
		left = philosopher->philosophers[philosopher->self->id - 1];
		right = philosopher->philosophers[philosopher->self->id + 1];
	}
	if (left->status != EAT && right->status != EAT && left->timestamp_last_eat > philosopher->self->timestamp_last_eat && right->timestamp_last_eat > philosopher->self->timestamp_last_eat)
		return (1);
	else
		return (0);
}

int	try_to_eat(t_data_philosopher *philosopher)
{
	long	timestamp;

	timestamp = get_current_time_in_ms();
	if (philosopher->self->status == THINK && is_eating_possible(philosopher))
	{
		philosopher->self->status = EAT;
		philosopher->self->timestamp_last_action = timestamp;
		philosopher->self->timestamp_last_eat = timestamp;
		print_action(philosopher, "has taken a fork");
		print_action(philosopher, "has taken a fork");
		print_action(philosopher, "is eating");
		manage_action(philosopher);
	}
}

int	manage_action(t_data_philosopher *philosopher)
{
	long	timestamp;
	while (1)
	{
		pthread_mutex_lock(&(philosopher->data_shared->mutex_status));
		if (!philosopher->data_shared->is_active_simulation)
			return (1);
		timestamp = get_current_time_in_ms();
		if (philosopher->self->status != EAT && timestamp - philosopher->self->timestamp_last_eat > philosopher->data_shared->data_main.time_to_die)
		{
			philosopher->self->timestamp_last_action = timestamp;
			philosopher->self->status = DEAD;
			print_action(philosopher, "died");
			philosopher->data_shared->is_active_simulation = 0;
		}
		else if (philosopher->self->status == SLEEP && timestamp - philosopher->self->timestamp_last_action > philosopher->data_shared->data_main.time_to_sleep)
		{
			philosopher->self->status = THINK;
			philosopher->self->timestamp_last_action = timestamp;
			print_action(philosopher, "is thinking");
			try_to_eat(philosopher);
		}
		else if (philosopher->self->status == EAT && timestamp - philosopher->self->timestamp_last_action > philosopher->data_shared->data_main.time_to_eat)
		{
			philosopher->self->status = SLEEP;
			philosopher->self->timestamp_last_action = timestamp;
			print_action(philosopher, "is sleeping");
		}
		pthread_mutex_unlock(&(philosopher->data_shared->mutex_status));
	}
	return (1);
}