/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manage_action.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 23:46:03 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/06 18:14:55 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	manage_action(t_data_philosopher *philos)
{
	long	timestamp;

	while (philos->data_shared->is_active_simulation)
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
