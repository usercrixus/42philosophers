/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_set_action.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:21:11 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/15 17:54:17 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_data_philosopher *philosopher, const char *str)
{
	pthread_mutex_lock(&(philosopher->data_shared->mutex_print));
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
	print_action(philosopher, "died");
	philosopher->data_shared->is_active_simulation = 0;
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

	timestamp = get_current_time_in_ms();
	philosopher->self->status = EAT;
	philosopher->self->timestamp_last_action = timestamp;
	philosopher->self->time_last_eat = timestamp;
	print_action(philosopher, "has taken a fork");
	print_action(philosopher, "has taken a fork");
	print_action(philosopher, "is eating");
}

void	set_sleep(t_data_philosopher *philosopher)
{
	long	timestamp;

	timestamp = get_current_time_in_ms();
	philosopher->self->status = SLEEP;
	philosopher->self->timestamp_last_action = timestamp;
	print_action(philosopher, "is sleeping");
}
