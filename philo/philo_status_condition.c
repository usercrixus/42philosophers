/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status_condition.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:38:56 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/10 21:34:54 by achaisne         ###   ########.fr       */
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

int	is_eating_possible(t_data_philosopher *philos)
{
	t_philosopher	*left;

	if (philos->self->id == 0)
		left = philos->philos[philos->data_shared->data_main.num_of_philo - 1];
	else
		left = philos->philos[philos->self->id - 1];
	if (left->fork.available && left->fork.last_user != philos->self
		&& philos->self->fork.available
		&& philos->self->fork.last_user != philos->self
		&& philos->self->status == THINK)
		return (1);
	return (0);
}

int	is_eat(t_data_philosopher *philosopher)
{
	int		left;

	if (philosopher->data_shared->data_main.num_of_philo == 1)
		return (0);
	left = 0;
	if (philosopher->self->id == 0)
		left = philosopher->data_shared->data_main.num_of_philo - 1;
	else
		left = philosopher->self->id - 1;
	lock_fork(philosopher, left);
	if (is_eating_possible(philosopher))
		return (1);
	unlock_fork(philosopher, left);
	return (0);
}

int	is_sleep(t_data_philosopher *philosopher, long timestamp)
{
	return (philosopher->self->status == EAT
		&& timestamp - philosopher->self->timestamp_last_action
		> philosopher->data_shared->data_main.time_to_eat);
}
