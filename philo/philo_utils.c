/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achaisne <achaisne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 00:13:55 by achaisne          #+#    #+#             */
/*   Updated: 2025/01/10 21:51:32 by achaisne         ###   ########.fr       */
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
	philos->data_shared->is_active_simulation = 0;
	return (1);
}

long	get_current_time_in_ms(void)
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
