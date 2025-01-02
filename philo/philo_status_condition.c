/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status_condition.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:38:56 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/17 03:24:52 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_die(t_data_philosopher *philosopher, long timestamp)
{
	return (philosopher->self->status != EAT
		&& timestamp - philosopher->self->time_last_eat
		> philosopher->data_shared->data_main.time_to_die);
}

int	is_think(t_data_philosopher *philosopher, long timestamp)
{
	return (philosopher->self->status == SLEEP
		&& timestamp - philosopher->self->timestamp_last_action
		> philosopher->data_shared->data_main.time_to_sleep);
}

int	is_eating_possible(t_data_philosopher *philos)
{
	t_philosopher	*left;

	if (philos->data_shared->data_main.num_of_philo == 1)
		return (0);
	else if (philos->self->id == 0)
		left = philos->philos[philos->data_shared->data_main.num_of_philo - 1];
	else
		left = philos->philos[philos->self->id - 1];
	if (left->fork.available && left->fork.last_user != philos->self
		&& philos->self->fork.available
		&& philos->self->fork.last_user != philos->self)
		return (1);
	return (0);
}

int	is_eat(t_data_philosopher *philosopher)
{
	return (philosopher->self->status == THINK
		&& is_eating_possible(philosopher));
}

int	is_sleep(t_data_philosopher *philosopher, long timestamp)
{
	return (philosopher->self->status == EAT
		&& timestamp - philosopher->self->timestamp_last_action
		> philosopher->data_shared->data_main.time_to_eat);
}
