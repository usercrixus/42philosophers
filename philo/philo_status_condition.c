/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status_condition.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:38:56 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/13 05:18:44 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_die(t_data_philosopher *philosopher, long timestamp)
{
	return (timestamp - philosopher->self->time_last_eat
		> philosopher->data_shared->data_main.time_to_die);
}

int	is_think(t_data_philosopher *philosopher, long timestamp)
{
	return (philosopher->self->status == SLEEP
		&& timestamp - philosopher->self->timestamp_last_action
		> philosopher->data_shared->data_main.time_to_sleep);
}

int	is_eat(t_data_philosopher *philos)
{
	if (philos->data_shared->data_main.size_philo == 1)
		return (0);
	if (philos->self->status == THINK)
		return (1);
	return (0);
}

int	is_sleep(t_data_philosopher *philosopher, long timestamp)
{
	return (philosopher->self->status == EAT
		&& timestamp - philosopher->self->timestamp_last_action
		> philosopher->data_shared->data_main.time_to_eat);
}
