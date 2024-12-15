/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manage_action.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 23:46:03 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/15 17:53:44 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	manage_action(t_data_philosopher *philosopher)
{
	long	timestamp;

	while (philosopher->data_shared->is_active_simulation)
	{
		pthread_mutex_lock(&(philosopher->data_shared->mutex_status));
		if (!philosopher->data_shared->is_active_simulation)
		{
			pthread_mutex_unlock(&(philosopher->data_shared->mutex_status));
			return (1);
		}
		timestamp = get_current_time_in_ms();
		if (is_die(philosopher, timestamp))
			set_die(philosopher);
		else if (is_think(philosopher, timestamp))
			set_think(philosopher);
		else if (is_eat(philosopher))
			set_eat(philosopher);
		else if (is_sleep(philosopher, timestamp))
			set_sleep(philosopher);
		pthread_mutex_unlock(&(philosopher->data_shared->mutex_status));
	}
	return (1);
}
