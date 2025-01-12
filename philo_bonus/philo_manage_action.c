/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manage_action.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 23:46:03 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/12 00:03:05 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	manage_action(t_data_philosopher *philos)
{
	unsigned long	timestamp;

	while (philos->data_shared->is_active_simulation)
	{
		timestamp = get_current_time_in_ms();
		if (is_think(philos, timestamp))
			set_think(philos, timestamp);
		else if (is_eat(philos))
			set_eat(philos, timestamp);
		else if (is_sleep(philos, timestamp))
			set_sleep(philos, timestamp);
	}
	if (philos->self->status == EAT)
	{
		sem_post(philos->data_shared->sem_fork);
		sem_post(philos->data_shared->sem_fork);
	}
}
