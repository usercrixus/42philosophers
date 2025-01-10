/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_launch_philosopher.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:43:32 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/10 16:59:25 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*launch_philosophers(void *arg)
{
	t_data_philosopher	*philosopher;

	philosopher = (t_data_philosopher *)arg;
	philosopher->self->timestamp_last_action = get_current_time_in_ms();
	philosopher->self->time_last_eat = philosopher->self->timestamp_last_action;
	print_action(philosopher, "is thinking");
	manage_action(philosopher);
	return (NULL);
}

void	manage_launch_philosopher(t_data_philosopher **data_philos)
{
	int	i;

	i = 0;
	while (i < data_philos[0]->data_shared->data_main.num_of_philo)
	{
		pthread_create(&(data_philos[i]->self->thread_id), NULL,
			launch_philosophers, data_philos[i]);
		i++;
	}
	i = 0;
	while (i < data_philos[0]->data_shared->data_main.num_of_philo)
	{
		pthread_join(data_philos[i]->self->thread_id, NULL);
		i++;
	}
}
