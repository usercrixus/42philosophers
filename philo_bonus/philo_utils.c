/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 00:13:55 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/12 00:29:03 by achaisne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_eat_times(t_data_philosopher *philos)
{
	if (philos->data_shared->data_main.times_each_philosopher_must_eat == -1)
		return (0);
	if (philos->self->number_of_eat
		== philos->data_shared->data_main.times_each_philosopher_must_eat)
	{
		sem_wait(philos->data_shared->sem_sum_eat);
		philos->data_shared->sum_eat++;
		sem_post(philos->data_shared->sem_sum_eat);
		if (philos->data_shared->sum_eat
			>= philos->data_shared->data_main.size_philo)
		{
			sem_wait(philos->data_shared->sem_active_simulation);
			philos->data_shared->is_active_simulation = 0;
			sem_post(philos->data_shared->sem_active_simulation);
			return (1);
		}
	}
	return (0);
}

unsigned long	get_current_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_min(int x, int y)
{
	if (x < y)
		return (x);
	return (y);
}

int	ft_max(int x, int y)
{
	if (x > y)
		return (x);
	return (y);
}
