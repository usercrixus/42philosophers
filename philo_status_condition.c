/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_status_condition.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:38:56 by achaisne          #+#    #+#             */
/*   Updated: 2024/12/15 17:52:52 by achaisne         ###   ########.fr       */
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

int	is_eating_possible(t_data_philosopher *philo)
{
	t_philosopher	*left;
	t_philosopher	*right;

	if (philo->data_shared->data_main.num_of_philo == 1)
		return (0);
	else if (philo->self->id == 0)
	{
		left = philo->philos[philo->data_shared->data_main.num_of_philo - 1];
		right = philo->philos[philo->self->id + 1];
	}
	else if (philo->self->id == philo->data_shared->data_main.num_of_philo - 1)
	{
		left = philo->philos[philo->self->id - 1];
		right = philo->philos[0];
	}
	else
	{
		left = philo->philos[philo->self->id - 1];
		right = philo->philos[philo->self->id + 1];
	}
	if (left->status != EAT && right->status != EAT
		&& left->time_last_eat >= philo->self->time_last_eat
		&& right->time_last_eat >= philo->self->time_last_eat)
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
