/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_create_philosopher.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:43:32 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/16 21:36:19 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*launch_philosopher(void *arg)
{
	t_data_philosopher	*philosopher;

	philosopher = (t_data_philosopher *)arg;
	philosopher->self->timestamp_last_action = get_current_time_in_ms();
	philosopher->self->time_last_eat = philosopher->self->timestamp_last_action;
	pthread_mutex_lock(&(philosopher->data_shared->mutex_print));
	printf("%ld %d is thinking\n",
		philosopher->self->timestamp_last_action, philosopher->self->id + 1);
	pthread_mutex_unlock(&(philosopher->data_shared->mutex_print));
	manage_action(philosopher);
	return (NULL);
}

t_philosopher	**get_philosopher(t_data_shared *data_shared)
{
	int				i;
	t_philosopher	**philosophers;

	philosophers = malloc(sizeof(t_philosopher *)
			* data_shared->data_main.num_of_philo);
	i = 0;
	while (i < data_shared->data_main.num_of_philo)
	{
		philosophers[i] = (t_philosopher *)malloc(sizeof(t_philosopher) * 1);
		if (!philosophers[i])
			return (0);
		philosophers[i]->id = i;
		philosophers[i]->status = THINK;
		philosophers[i]->thread_id = 0;
		philosophers[i]->time_last_eat = 0;
		philosophers[i]->timestamp_last_action = 0;
		i++;
	}
	return (philosophers);
}

void	destroy_philosophers(t_data_philosopher	*data_philosopher)
{
	int	i;

	i = 0;
	while (i < data_philosopher->data_shared->data_main.num_of_philo)
	{
		free(data_philosopher->philos[i]);
		i++;
	}
	free(data_philosopher->philos);
}

void	destroy_data_philosopher(t_data_philosopher **data_philosopher)
{
	int	i;
	int	size;

	size = data_philosopher[0]->data_shared->data_main.num_of_philo;
	i = 0;
	while (i < size)
	{
		free(data_philosopher[i]);
		i++;
	}
	free(data_philosopher);
}

int	manage_launch_philosopher(t_data_shared *data_shared)
{
	int					i;
	t_data_philosopher	**data_philosopher;
	t_philosopher		**philosophers;

	philosophers = get_philosopher(data_shared);
	if (!philosophers)
		return (0);
	data_philosopher = malloc(sizeof(t_data_philosopher *) * data_shared->data_main.num_of_philo);
	i = 0;
	while (i < data_shared->data_main.num_of_philo)
	{
		data_philosopher[i] = malloc(sizeof(t_data_philosopher));
		data_philosopher[i]->philos = philosophers;
		data_philosopher[i]->data_shared = data_shared;
		data_philosopher[i]->self = philosophers[i];
		pthread_create(&(data_philosopher[i]->self->thread_id), NULL,
			launch_philosopher, data_philosopher[i]);
		i++;
	}
	i = 0;
	while (i < data_shared->data_main.num_of_philo)
	{
		pthread_join(data_philosopher[i]->self->thread_id, NULL);
		i++;
	}
	return(destroy_philosophers(data_philosopher[0]), destroy_data_philosopher(data_philosopher), 1);
}
