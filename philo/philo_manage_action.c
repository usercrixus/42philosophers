/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manage_action.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 23:46:03 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/11 03:18:09 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	manage_action(t_data_philosopher *philos)
{
	long	timestamp;

	while (philos->data_shared->is_active_simulation)
	{
		timestamp = get_current_time_in_ms();
		if (is_die(philos, timestamp))
			set_die(philos, timestamp);
		else if (is_think(philos, timestamp))
			set_think(philos, timestamp);
		else if (is_eat(philos))
			set_eat(philos, timestamp);
		else if (is_sleep(philos, timestamp))
			set_sleep(philos, timestamp);
	}
	return (1);
}
