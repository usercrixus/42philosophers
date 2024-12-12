/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create_philosopher.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:43:32 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/12 02:28:06 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*launch_philosopher(void *arg)
{
	t_data_philosopher *data_philosopher = (t_data_philosopher *)arg;
	data_philosopher->self->timestamp_last_action = get_current_time_in_ms();
	data_philosopher->self->timestamp_last_eat = data_philosopher->self->timestamp_last_action;
	pthread_mutex_lock(&(data_philosopher->data_shared->mutex_print));
	printf("%ld %d is thinking\n", data_philosopher->self->timestamp_last_action, data_philosopher->self->id);
	pthread_mutex_unlock(&(data_philosopher->data_shared->mutex_print));
	manage_action(data_philosopher);
	return (NULL);
}

t_philosopher	**get_philosopher(t_data_shared *data_shared)
{
	int	i;
	t_philosopher	**philosophers;

	philosophers = (t_philosopher **)malloc(sizeof(t_philosopher *) * data_shared->data_main.number_of_philosophers);
	i = 0;
	while (i < data_shared->data_main.number_of_philosophers)
	{
		philosophers[i] = (t_philosopher *)malloc(sizeof(t_philosopher) * 1);
		if (!philosophers[i])
			return (0);
		philosophers[i]->id = i;
		philosophers[i]->status = THINK;
		i++;
	}
	return (philosophers);
}

int	manage_launch_philosopher(t_data_shared *data_shared)
{
	int					i;
	t_data_philosopher	*data_philosopher;
	t_philosopher		**philosophers;

	philosophers = get_philosopher(data_shared);
	if (!philosophers)
		return (0);
	i = 0;
	while (i < data_shared->data_main.number_of_philosophers)
	{
		data_philosopher = (t_data_philosopher *)malloc(sizeof(t_data_philosopher) * 1);
		data_philosopher->philosophers = philosophers;
		data_philosopher->data_shared = data_shared;
		data_philosopher->self = philosophers[i];
		pthread_create(&(data_philosopher->self->thread_id), NULL, launch_philosopher, data_philosopher);
		i++;
	}
	i = 0;
	while (i < data_shared->data_main.number_of_philosophers)
	{
		pthread_join(data_philosopher->self->thread_id, NULL);
		i++;
	}
}