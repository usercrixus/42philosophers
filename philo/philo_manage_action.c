/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manage_action.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 23:46:03 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/17 03:37:41 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_reach_eat_times(t_data_philosopher *philos)
{
	int	i;

	if (philos->data_shared->data_main.times_each_philosopher_must_eat == -1)
		return (0);
	i = 0;
	while (i < philos->data_shared->data_main.num_of_philo)
	{
		if (philos->philos[i]->number_of_eat
			< philos->data_shared->data_main.times_each_philosopher_must_eat)
			return (0);
		i++;
	}
	return (1);
}

int	manage_action(t_data_philosopher *philos)
{
	long	timestamp;

	while (philos->data_shared->is_active_simulation
		&& !is_reach_eat_times(philos))
	{
		pthread_mutex_lock(&(philos->data_shared->mutex_status));
		if (!philos->data_shared->is_active_simulation)
		{
			pthread_mutex_unlock(&(philos->data_shared->mutex_status));
			return (1);
		}
		timestamp = get_current_time_in_ms();
		if (is_die(philos, timestamp))
			set_die(philos);
		else if (is_think(philos, timestamp))
			set_think(philos);
		else if (is_eat(philos))
			set_eat(philos);
		else if (is_sleep(philos, timestamp))
			set_sleep(philos);
		pthread_mutex_unlock(&(philos->data_shared->mutex_status));
	}
	return (1);
}
