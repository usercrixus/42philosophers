/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manage_action.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 23:46:03 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/12 02:29:41 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_eating_possible(t_data_philosopher *philosopher)
{
	pthread_mutex_lock(&(philosopher->data_shared->mutex_eat));
	if (philosopher->self->id == 0)
	{
		if (philosopher->philosophers[philosopher->data_shared->data_main.number_of_philosophers - 1]->status != EAT
			&& philosopher->philosophers[philosopher->self->id + 1]->status != EAT )
			return (pthread_mutex_unlock(&(philosopher->data_shared->mutex_eat)), 1);
	}
	else if (philosopher->self->id == philosopher->data_shared->data_main.number_of_philosophers - 1)
	{
		if (philosopher->philosophers[philosopher->self->id - 1]->status != EAT
			&& philosopher->philosophers[0]->status != EAT)
			return (pthread_mutex_unlock(&(philosopher->data_shared->mutex_eat)), 1);;
	}
	else
	{
		if (philosopher->philosophers[philosopher->self->id - 1]->status != EAT
			&& philosopher->philosophers[philosopher->self->id + 1]->status != EAT)
			return (pthread_mutex_unlock(&(philosopher->data_shared->mutex_eat)), 1);
	}
	return (pthread_mutex_unlock(&(philosopher->data_shared->mutex_eat)), 0);
}

int	manage_action(t_data_philosopher *philosopher)
{
	long	timestamp;

	while (1)
	{
		timestamp = get_current_time_in_ms();
		if (timestamp - philosopher->self->timestamp_last_eat > philosopher->data_shared->data_main.time_to_die)
		{
			pthread_mutex_lock(&(philosopher->data_shared->mutex_print));
			printf("%ld %d is dead\n", philosopher->self->timestamp_last_action, philosopher->self->id);
			pthread_mutex_unlock(&(philosopher->data_shared->mutex_print));
			exit(1);
		}
		else if (philosopher->self->status == SLEEP && timestamp - philosopher->self->timestamp_last_action > philosopher->data_shared->data_main.time_to_sleep)
		{
			philosopher->self->status = THINK;
			philosopher->self->timestamp_last_action = timestamp;
			pthread_mutex_lock(&(philosopher->data_shared->mutex_print));
			printf("%ld %d is thinking\n", philosopher->self->timestamp_last_action, philosopher->self->id);
			pthread_mutex_unlock(&(philosopher->data_shared->mutex_print));
		}
		else if (philosopher->self->status == THINK && is_eating_possible(philosopher))
		{
			philosopher->self->status = EAT;
			philosopher->self->timestamp_last_action = timestamp;
			pthread_mutex_lock(&(philosopher->data_shared->mutex_print));
			printf("%ld %d is eating\n", philosopher->self->timestamp_last_action, philosopher->self->id);
			pthread_mutex_unlock(&(philosopher->data_shared->mutex_print));
		}
		else if (philosopher->self->status == EAT && timestamp - philosopher->self->timestamp_last_action > philosopher->data_shared->data_main.time_to_eat)
		{
			philosopher->self->status = SLEEP;
			philosopher->self->timestamp_last_action = timestamp;
			philosopher->self->timestamp_last_eat = timestamp;
			pthread_mutex_lock(&(philosopher->data_shared->mutex_print));
			printf("%ld %d is sleeping\n", philosopher->self->timestamp_last_action, philosopher->self->id);
			pthread_mutex_unlock(&(philosopher->data_shared->mutex_print));
		}
	}
	
}